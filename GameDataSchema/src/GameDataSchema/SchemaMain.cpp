#include <fstream>
#include <unordered_set>

#include "Schema/GameSchema.h"
#include "Schema/SchemaTypes.h"
#include "Schema/OutputSchema.h"
#include "Schema/ModuleWriter.h"
#include "Schema/PacketSchema.h"

#include <PacketProcessing/PacketParser.h>
#include <ParserUtils/DataStream.h>
#include <ParserUtils/PacketParsing.h>
#include <PacketProcessing/Handlers/SniffHandler/SniffHandler.h>

namespace fs = std::filesystem;

fs::path ms2Root = "B:/Files/Maplstory 2 Client/appdata";
fs::path ms2RootExtracted = "B:/Files/ms2export/export/";
//fs::path kms2Root = "B:/Files/ms2export/kms2export";
fs::path kms2Root = "B:/Files/ms2export/kms2export_new_xml";
const fs::path schemaDir = "./schema";
const fs::path packetSchemaDir = "./packetSchema";
Archive::ArchiveReader gms2Reader;
Archive::ArchiveReader kms2Reader;

const std::unordered_set<unsigned short> ignoreClientPacketUnknownValues = {
	0x20
};

const std::unordered_set<unsigned short> ignoreServerPacketUnknownValues = {
	
};

Networking::Packets::Metadata gms2Data;
Networking::Packets::Metadata kms2Data;

namespace ParserUtils
{
	namespace Packets
	{
		template <typename Type>
		void read(std::ifstream& in, Type& data)
		{
			in.read(reinterpret_cast<char*>(&data), sizeof(data));
		}

		template <>
		void read<std::string>(std::ifstream& in, std::string& data)
		{
			unsigned char length;
			read(in, length);

			for (int i = 0; i < length; ++i)
			{
				char character;
				read(in, character);

				data.push_back(character);
			}
		}

		struct OpcodeVersion
		{
			unsigned short Version = 0;
			unsigned short Opcode = 0;
		};

		std::unordered_set<unsigned short> printedAlready;
		std::unordered_set<unsigned long long> printedPacketAlready;

		struct VersionSuccesses
		{
			std::unordered_set<unsigned short> ClientPackets;
			std::unordered_set<unsigned short> ServerPackets;
		};

		std::unordered_map<unsigned short, VersionSuccesses> successfulPackets;
		std::unordered_map<unsigned short, VersionSuccesses> seenPackets;
		std::unordered_map<unsigned short, VersionSuccesses> unparsedPackets;

		std::string printTimeStamp(long long timeStamp)
		{
			if (timeStamp == 0)
			{
				return "";
			}

			long long epoch = 0x089f7ff5f7b58000;
			timeStamp -= epoch;
			long long ns = timeStamp % 10000000;
			timeStamp /= 10000000;

			std::time_t time(timeStamp);

			const int buffSize = 32;
			char buffer[buffSize] = { 0 };

			auto err = ctime_s(buffer, buffSize, &time);

			for (int i = 0; i < buffSize; ++i)
				if (buffer[i] == '\n' || buffer[i] == '\r')
					buffer[i] = 0;

			int size = 0;

			while (buffer[size])
				++size;

			buffer[std::max(0, size - 5)] = 0;

			int ms = (int)(ns / 10000);

			std::stringstream out;
			out << "[" << buffer << "." << ms;

			if ((ms % 100) == 0)
			{
				out << "00";
			}
			else if ((ms % 10) == 0)
			{
				out << "0";
			}

			out << " " << (buffer + size - 4) << "] ";

			return out.str();
		}

		unsigned short parseMsb(const fs::path& path)
		{
			Networking::Packets::SniffHandler handler;

			size_t readPackets = 0;

			std::ifstream file(path, std::ios::binary);

			unsigned short version = 0;
			unsigned short localPort = 0;
			unsigned short locale = 0;
			unsigned int build = 0;
			std::string endPoint;
			std::string remoteEndPoint;
			unsigned short remotePort = 0;

			read(file, version);

			bool hasPrintedFile = false;

			if (version < 0x2000)
			{
				read(file, localPort);
			}
			else
			{
				if (version == 0x2012)
				{
					unsigned short sbuild;

					read(file, locale);
					read(file, sbuild);
					build = sbuild;
					read(file, localPort);
				}
				else if (version == 0x2014)
				{
					unsigned short sbuild;

					read(file, endPoint);
					read(file, localPort);
					read(file, remoteEndPoint);
					read(file, remotePort);
					read(file, locale);
					read(file, sbuild);
					build = sbuild;
				}
				else if (version == 0x2015 || version >= 0x2020)
				{
					unsigned char slocale;

					read(file, endPoint);
					read(file, localPort);
					read(file, remoteEndPoint);
					read(file, remotePort);
					read(file, slocale);
					locale = slocale;
					read(file, build);
				}
			}

			handler.Data = build == 12 ? &gms2Data : &kms2Data;
			handler.Version = build;
			handler.MsbPath = path.string();

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				if (!hasPrintedFile)
				{
					hasPrintedFile = true;

					std::cout << "parsing [" << build;

					if (handler.Feature)
					{
						std::cout << ", Feature: " << handler.Feature << "; " << handler.Locale;
					}

					std::cout << "] " << path.string() << std::endl;
				}
			}

			while (!file.eof())
			{
				long long timeStamp;

				read(file, timeStamp);

				int size;

				if (version < 0x2027)
				{
					unsigned short ssize;
					read(file, ssize);
					size = ssize;
				}
				else
					read(file, size);

				unsigned short opcode;

				read(file, opcode);

				bool outbound;

				if (version >= 0x2020)
					read(file, outbound);
				else
				{
					outbound = (size & 0x8000) != 0;
					size = size & 0x7FFF;
				}

				std::vector<unsigned char> buffer;

				buffer.resize(size);

				file.read(reinterpret_cast<char*>(buffer.data()), size);

				if (version >= 0x2025 && version < 0x2030)
				{
					unsigned int val;
					read(file, val);
					read(file, val);
				}

				handler.ResetPacketStream() = ParserUtils::DataStream{{reinterpret_cast<char*>(buffer.data()), buffer.size()}};
				handler.FoundValues = {};
				handler.ReportPackets = true;
				handler.TimeStamp = printTimeStamp(timeStamp);

				unsigned long long opcodeVersion = ((((unsigned long long)opcode << 16) | (unsigned long long)build) << 32) | buffer.size();

				{
					ParserUtils::DataStream& stream = handler.PacketStream();

					std::cout << std::dec;

					stream.IgnoreUnknownValues = (!outbound ? ignoreServerPacketUnknownValues : ignoreClientPacketUnknownValues).contains(opcode);
					stream.SuppressErrors = printedPacketAlready.contains(opcodeVersion);
				}

				Networking::Packets::ParsePacket(handler, build, !outbound, opcode);

				ParserUtils::DataStream& stream = handler.PacketStream();

				++readPackets;

				if (outbound == false && opcode == 0x7A && build == 12)
				{
					opcode += 0;
				}

				if (stream.DiscardErrors)
				{
					continue;
				}

				if (stream.Index && !stream.HasRecentlyFailed && stream.Index == stream.Data.size())
				{
					auto& versionSuccesses = successfulPackets[build];
					auto & packetSet = !outbound ? versionSuccesses.ServerPackets : versionSuccesses.ClientPackets;

					if (!packetSet.contains(opcode))
					{
						packetSet.insert(opcode);
					}
				}
				else if (!stream.HasRecentlyFailed && stream.Index == 0)
				{
					auto& unparsed = unparsedPackets[build];
					auto& packetSet = !outbound ? unparsed.ServerPackets : unparsed.ClientPackets;

					if (!packetSet.contains(opcode))
					{
						packetSet.insert(opcode);
					}
				}

				{
					auto& seen = seenPackets[build];
					auto& packetSet = !outbound ? seen.ServerPackets : seen.ClientPackets;

					if (!packetSet.contains(opcode))
					{
						packetSet.insert(opcode);
					}
				}

				if (stream.Index == 0 || (!ParserUtils::Packets::PrintErrors && !ParserUtils::Packets::PrintUnknownValues) || stream.SuppressErrors || printedAlready.contains(build))
				{
					continue;
				}

				if (stream.HasRecentlyFailed || stream.Index < stream.Data.size() || stream.FoundUnknownValue)
				{
					std::cout << std::dec;

					if (!hasPrintedFile && (stream.HasRecentlyFailed || stream.Index < stream.Data.size() || stream.FoundUnknownValue))
					{
						hasPrintedFile = true;

						std::cout << "parsing [" << build;

						if (handler.Feature)
						{
							std::cout << ", Feature: " << handler.Feature << "; " << handler.Locale;
						}

						std::cout << "] " << path.string() << std::endl;
					}

					if (stream.HasRecentlyFailed)
					{
						std::cout << "failed while parsing packet" << std::endl;
					}
					
					if (stream.Index < stream.Data.size())
					{
						std::cout << "packet parsing had leftover data. parsed " << stream.Index << " bytes" << std::endl;
					}

					if (stream.FoundUnknownValue)
					{
						std::cout << "found unknown value in packet" << std::endl;
					}

					std::cout << path.string() << std::endl;
					std::cout << "Version: " << build << "; Packet length: " << stream.Data.size() << "; Opcode: 0x" << std::hex << opcode << '\n';
					
					size_t size = stream.Data.size();
					size_t printCount = 16 * ((size / 16) + (size % 16 ? 1 : 0));

					for (size_t i = 0; i <= printCount; ++i)
					{
						if (i && (i % 16) == 0)
						{
							std::cout << " |  " << std::dec;

							for (size_t j = 0; j < 16 && i - 16 + j < size; ++j)
								std::cout << (buffer[i - 16 + j] >= 32 && buffer[i - 16 + j] <= 126 ? (char)buffer[i - 16 + j] : '.');

							std::cout << "\n" << std::hex;
						}

						if (i < size)
						{
							std::cout << std::setw(2) << std::setfill('0') << (int)buffer[i] << " ";
						}
						else if (i < printCount)
						{
							std::cout << "   ";
						}
					}

					std::cout << std::dec << std::endl;

					if (stream.HasRecentlyFailed || stream.Index < stream.Data.size() || stream.FoundUnknownValue)
					{
						//printedAlready.insert(build);
						if (stream.HasRecentlyFailed || stream.Index < stream.Data.size())
						{
							printedPacketAlready.insert(opcodeVersion);
						}

						handler.ResetPacketStream() = ParserUtils::DataStream{{reinterpret_cast<char*>(buffer.data()), buffer.size()}};
						handler.FoundValues = {};
						handler.ReportPackets = false;

						handler.PacketStream().IgnoreUnknownValues = (!outbound ? ignoreServerPacketUnknownValues : ignoreClientPacketUnknownValues).contains(opcode);
						handler.PacketStream().PrintOutput = true;

						Networking::Packets::ParsePacket(handler, build, !outbound, opcode);

						std::string values = handler.FoundValues.str();

						if (values.size() && !ParserUtils::Packets::PrintOutput)
						{
							std::cout << values << std::endl;
						}

						if (stream.Index < stream.Data.size() && !stream.HasRecentlyFailed)
						{
							std::cout << "remaining: \n" << std::hex;

							size_t printAmount = size - stream.Index;
							size_t printCount = 16 * ((printAmount / 16) + (printAmount % 16 ? 1 : 0));
						
							for (size_t i = 0; i <= printCount; ++i)
							{
								size_t index = stream.Index + i;

								if (i && (i % 16) == 0)
								{
									std::cout << " |  " << std::dec;

									for (size_t j = 0; j < 16 && index - 16 + j < size; ++j)
										std::cout << (buffer[index - 16 + j] >= 32 && buffer[index - 16 + j] <= 126 ? (char)buffer[index - 16 + j] : '.');

									std::cout << "\n" << std::hex;
								}

								if (index < size)
								{
									std::cout << std::setw(2) << std::setfill('0') << (unsigned int)buffer[index] << " ";
								}
								else if (i < printCount)
								{
									std::cout << "   ";
								}
							}
						}
					}

					std::cout << "\n----------------\n";
				}
			}

			return build;
		}
	}
}

unsigned int parseMsb(const fs::path& path)
{
	std::ifstream file(path, std::ios::binary);

	unsigned short version = 0;
	unsigned short localPort = 0;
	unsigned short locale = 0;
	unsigned int build = 0;
	std::string endPoint;
	std::string remoteEndPoint;
	unsigned short remotePort = 0;

	ParserUtils::Packets::read(file, version);

	if (version < 0x2000)
	{
		ParserUtils::Packets::read(file, localPort);
	}
	else
	{
		if (version == 0x2012)
		{
			unsigned short sbuild;

			ParserUtils::Packets::read(file, locale);
			ParserUtils::Packets::read(file, sbuild);
			build = sbuild;
			ParserUtils::Packets::read(file, localPort);
		}
		else if (version == 0x2014)
		{
			unsigned short sbuild;

			ParserUtils::Packets::read(file, endPoint);
			ParserUtils::Packets::read(file, localPort);
			ParserUtils::Packets::read(file, remoteEndPoint);
			ParserUtils::Packets::read(file, remotePort);
			ParserUtils::Packets::read(file, locale);
			ParserUtils::Packets::read(file, sbuild);
			build = sbuild;
		}
		else if (version == 0x2015 || version >= 0x2020)
		{
			unsigned char slocale;

			ParserUtils::Packets::read(file, endPoint);
			ParserUtils::Packets::read(file, localPort);
			ParserUtils::Packets::read(file, remoteEndPoint);
			ParserUtils::Packets::read(file, remotePort);
			ParserUtils::Packets::read(file, slocale);
			locale = slocale;
			ParserUtils::Packets::read(file, build);
		}
	}

	return build;
}

int main(int argc, char** argv)
{
	std::vector<std::string> validateGms2Dirs;
	std::vector<std::string> validateKms2Dirs;

	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "--root") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2Root = argv[i];
		}

		if (strcmp(argv[i], "--rootExtracted") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find extracted root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2RootExtracted = argv[i];
		}

		if (strcmp(argv[i], "--validate") == 0 && ++i + 1 < argc)
		{
			if (strcmp(argv[i], "gms2") == 0)
			{
				validateGms2Dirs.push_back(argv[++i]);
			}
			else if (strcmp(argv[i], "kms2") == 0)
			{
				validateKms2Dirs.push_back(argv[++i]);
			}
		}
	}

	if (!fs::exists(ms2Root)) return -1;
	if (!fs::exists(schemaDir)) return -1;

	gms2Reader.Load(ms2Root / "Data", false);
	kms2Reader.Load(kms2Root / "Data", false);

	std::string output;

	const auto visit1 = [&output](const Archive::ArchivePath& path)
	{
		Enum::NpcId id = (Enum::NpcId)atoi(path.GetPath().filename().stem().string().c_str());

		Networking::Packets::NpcData& npc = gms2Data.Npcs[id];

		output.clear();

		path.Read(output);

		if (output.size() == 0)
		{
			std::cout << "failed to read " << path.GetPath() << std::endl;

			return false;
		}

		tinyxml2::XMLDocument document;

		document.Parse(output.data(), output.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		if (!rootElement) return false;

		tinyxml2::XMLElement* environmentElement = rootElement->FirstChildElement("environment");

		if (!environmentElement) return false;

		tinyxml2::XMLElement* basicElement = environmentElement->FirstChildElement("basic");

		if (!basicElement) return false;

		const tinyxml2::XMLAttribute* classAttribute = basicElement->FindAttribute("class");
		const tinyxml2::XMLAttribute* friendlyAttribute = basicElement->FindAttribute("friendly");

		if (classAttribute)
		{
			npc.Class = atoi(classAttribute->Value());
		}

		if (friendlyAttribute)
		{
			npc.NpcType = atoi(friendlyAttribute->Value());
		}

		tinyxml2::XMLElement* statElement = environmentElement->FirstChildElement("stat");

		if (!statElement) return false;

		npc.HasHiddenHp |= statElement->FindAttribute("hiddenhpadd") != nullptr;
		//npc.HasHiddenHp |= statElement->FindAttribute("hiddenhpadd01") != nullptr;
		//npc.HasHiddenHp |= statElement->FindAttribute("hiddenhpadd02") != nullptr;
		//npc.HasHiddenHp |= statElement->FindAttribute("hiddenhpadd03") != nullptr;
		//npc.HasHiddenHp |= statElement->FindAttribute("hiddenhpadd04") != nullptr;

		return false;
	};

	const auto visit2 = [&output](const Archive::ArchivePath& path)
	{
		output.clear();

		path.Read(output);

		if (output.size() == 0)
		{
			std::cout << "failed to read " << path.GetPath() << std::endl;

			return false;
		}

		tinyxml2::XMLDocument document;

		document.Parse(output.data(), output.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		if (!rootElement) return false;

		for (tinyxml2::XMLElement* npcElement = rootElement->FirstChildElement(); npcElement; npcElement = npcElement->NextSiblingElement())
		{
			const tinyxml2::XMLAttribute* idAttribute = npcElement->FindAttribute("id");

			if (!idAttribute) continue;

			Enum::NpcId id = (Enum::NpcId)atoi(idAttribute->Value());

			Networking::Packets::NpcData& npc = kms2Data.Npcs[id];

			tinyxml2::XMLElement* environmentElement = npcElement->FirstChildElement("environment");

			if (!environmentElement) continue;

			const tinyxml2::XMLAttribute* classAttribute = environmentElement->FindAttribute("class");
			const tinyxml2::XMLAttribute* friendlyAttribute = environmentElement->FindAttribute("friendly");

			if (classAttribute)
			{
				npc.Class = atoi(classAttribute->Value());
			}

			if (friendlyAttribute)
			{
				npc.NpcType = atoi(friendlyAttribute->Value());
			}

			tinyxml2::XMLElement* statElement = environmentElement->FirstChildElement("stat");

			if (!statElement) continue;

			npc.HasHiddenHp |= statElement->FindAttribute("hiddenhpadd") != nullptr;
		}

		return false;
	};

	const auto visit3 = [&output](const Archive::ArchivePath& path)
	{
		output.clear();

		path.Read(output);

		if (output.size() == 0)
		{
			std::cout << "failed to read " << path.GetPath() << std::endl;

			return false;
		}

		tinyxml2::XMLDocument document;

		document.Parse(output.data(), output.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		if (!rootElement) return false;

		Enum::ItemId id = (Enum::ItemId)atoi(path.GetPath().filename().stem().string().c_str());

		Networking::Packets::ItemData& item = gms2Data.Items[id];

		for (tinyxml2::XMLElement* environmentElement = rootElement->FirstChildElement(); environmentElement; environmentElement = environmentElement->NextSiblingElement())
		{
			tinyxml2::XMLElement* gemElement = environmentElement->FirstChildElement("gem");

			if (gemElement)
			{
				const tinyxml2::XMLAttribute* systemAttribute = gemElement->FindAttribute("system");

				if (systemAttribute)
				{
					item.BadgeType = (unsigned char)atoi(systemAttribute->Value());
					item.IsBadge = item.BadgeType != 0;
				}
			}

			tinyxml2::XMLElement* uccElement = environmentElement->FirstChildElement("ucc");

			if (uccElement)
			{
				const tinyxml2::XMLAttribute* meshAttribute = uccElement->FindAttribute("mesh");

				if (meshAttribute)
				{
					item.HasTemplate = strcmp(meshAttribute->Value(), "") != 0;
				}
			}

			tinyxml2::XMLElement* propertyElement = environmentElement->FirstChildElement("property");

			if (propertyElement)
			{
				const tinyxml2::XMLAttribute* typeAttribute = propertyElement->FindAttribute("type");

				if (typeAttribute)
				{
					unsigned char type = (unsigned char)atoi(typeAttribute->Value());

					item.HasBlueprint = type == 22;
				}
			}

			tinyxml2::XMLElement* petElement = environmentElement->FirstChildElement("pet");

			if (petElement)
			{
				const tinyxml2::XMLAttribute* petIDAttribute = petElement->FindAttribute("petID");

				if (petIDAttribute)
				{
					item.PetId = (unsigned int)atoi(petIDAttribute->Value());
				}
			}

			tinyxml2::XMLElement* scoreElement = environmentElement->FirstChildElement("MusicScore");

			if (scoreElement)
			{
				const tinyxml2::XMLAttribute* customAttribute = scoreElement->FindAttribute("isCustomNote");

				if (customAttribute)
				{
					item.IsMusicScore = strcmp(customAttribute->Value(), "true") == 0;
					item.IsCustomNote = strcmp(customAttribute->Value(), "true") == 0;
				}
			}
		}

		return false;
	};

	const auto visit4 = [&output](const Archive::ArchivePath& path)
	{
		output.clear();

		path.Read(output);

		if (output.size() == 0)
		{
			std::cout << "failed to read " << path.GetPath() << std::endl;

			return false;
		}

		tinyxml2::XMLDocument document;

		document.Parse(output.data(), output.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		if (!rootElement) return false;

		for (tinyxml2::XMLElement* itemElement = rootElement->FirstChildElement(); itemElement; itemElement = itemElement->NextSiblingElement())
		{
			const tinyxml2::XMLAttribute* idAttribute = itemElement->FindAttribute("id");

			if (!idAttribute) continue;

			Enum::ItemId id = (Enum::ItemId)atoi(idAttribute->Value());

			Networking::Packets::ItemData& item = kms2Data.Items[id];

			for (tinyxml2::XMLElement* environmentElement = itemElement->FirstChildElement(); environmentElement; environmentElement = environmentElement->NextSiblingElement())
			{
				tinyxml2::XMLElement* uccElement = environmentElement->FirstChildElement("ucc");

				if (uccElement)
				{
					const tinyxml2::XMLAttribute* meshAttribute = uccElement->FindAttribute("mesh");

					if (meshAttribute)
					{
						item.HasTemplate = strcmp(meshAttribute->Value(), "") != 0;
					}
				}

				tinyxml2::XMLElement* propertyElement = environmentElement->FirstChildElement("property");

				if (propertyElement)
				{
					const tinyxml2::XMLAttribute* typeAttribute = propertyElement->FindAttribute("type");
					const tinyxml2::XMLAttribute* categoryAttribute = propertyElement->FindAttribute("category");
					const tinyxml2::XMLAttribute* param1Attribute = propertyElement->FindAttribute("param1");

					if (typeAttribute)
					{
						unsigned char type = (unsigned char)atoi(typeAttribute->Value());

						item.HasBlueprint = type == 22;
					}

					if (categoryAttribute)
					{
						if (param1Attribute && strcmp(categoryAttribute->Value(), "Pet") == 0)
						{
							item.PetId = (unsigned int)atoi(param1Attribute->Value());
						}

						if (strcmp(categoryAttribute->Value(), "SYSTEM") == 0)
						{
							if (param1Attribute)
							{
								item.BadgeId = (unsigned int)atoi(param1Attribute->Value());
							}

							item.IsBadge = true;
						}
					}

					if (categoryAttribute)
					{
						item.IsMusicScore = strcmp(categoryAttribute->Value(), "ugcScore") == 0;
						item.IsCustomNote = strcmp(categoryAttribute->Value(), "ugcScore") == 0;
					}
				}
			}
		}

		return false;
	};

	bool regenerate = !true;
	bool showSuccesses = !false;
	bool showSeen = false;
	bool showUnparsed = !false;
	bool showUnused = false;
	bool printBaseStats = false;

	fs::path msbDir = "B:/Files/ms2sniffs/";

	if (!regenerate)
	{
		Archive::ForEachFile(gms2Reader.GetPath("Xml/npc", true), true, visit1);
		Archive::ForEachFile(gms2Reader.GetPath("Xml/item", true), true, visit3);
		Archive::ForEachFile(kms2Reader.GetPath("Xml/npcdata", true), true, visit2);
		Archive::ForEachFile(kms2Reader.GetPath("Xml/itemdata", true), true, visit4);

		{
			Archive::ArchivePath path = gms2Reader.GetPath("Xml/string/en/npcname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

				if (!idAttribute || !nameAttribute) continue;

				Enum::NpcId id = (Enum::NpcId)atoi(idAttribute->Value());
				
				gms2Data.Npcs[id].Name = nameAttribute->Value();
			}
		}
		{
			Archive::ArchivePath path = kms2Reader.GetPath("Xml/string/en/npcname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

				if (!idAttribute || !nameAttribute) continue;

				Enum::NpcId id = (Enum::NpcId)atoi(idAttribute->Value());

				kms2Data.Npcs[id].Name = nameAttribute->Value();
			}
		}
		{
			Archive::ArchivePath path = gms2Reader.GetPath("Xml/string/en/petname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

				if (!idAttribute || !nameAttribute) continue;

				Enum::NpcId id = (Enum::NpcId)atoi(idAttribute->Value());
				
				gms2Data.Npcs[id].Name = nameAttribute->Value();
			}
		}
		{
			Archive::ArchivePath path = kms2Reader.GetPath("Xml/string/en/petname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

				if (!idAttribute || !nameAttribute) continue;

				Enum::NpcId id = (Enum::NpcId)atoi(idAttribute->Value());

				kms2Data.Npcs[id].Name = nameAttribute->Value();
			}
		}
		{
			Archive::ArchivePath path = gms2Reader.GetPath("Xml/string/en/mapname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

				if (!idAttribute || !nameAttribute) continue;

				Enum::MapId id = (Enum::MapId)atoi(idAttribute->Value());

				gms2Data.Maps[id].Name = nameAttribute->Value();
			}
		}
		{
			Archive::ArchivePath path = kms2Reader.GetPath("Xml/string/en/mapname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

				if (!idAttribute || !nameAttribute) continue;

				Enum::MapId id = (Enum::MapId)atoi(idAttribute->Value());

				kms2Data.Maps[id].Name = nameAttribute->Value();
			}
		}
		{
			Archive::ArchivePath path = gms2Reader.GetPath("Xml/string/en/itemname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");
				const tinyxml2::XMLAttribute* classAttribute = keyElement->FindAttribute("class");

				if (!idAttribute || !nameAttribute) continue;

				Enum::ItemId id = (Enum::ItemId)atoi(idAttribute->Value());

				gms2Data.Items[id].Name = nameAttribute->Value();

				if (classAttribute)
				{
					gms2Data.Items[id].Class = classAttribute->Value();
				}
			}
		}
		{
			Archive::ArchivePath path = kms2Reader.GetPath("Xml/string/en/itemname.xml", true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");
				const tinyxml2::XMLAttribute* classAttribute = keyElement->FindAttribute("class");

				if (!idAttribute || !nameAttribute) continue;

				Enum::ItemId id = (Enum::ItemId)atoi(idAttribute->Value());

				kms2Data.Items[id].Name = nameAttribute->Value();

				if (classAttribute)
				{
					kms2Data.Items[id].Class = classAttribute->Value();
				}
			}
		}
	}
	{
		const char* paths[] = {
			"Xml/string/en/koradditionaldescription.xml",
			"Xml/string/en/koradditionaldescription_1.xml",
			"Xml/string/en/koradditionaldescription_10.xml",
			"Xml/string/en/koradditionaldescription_20.xml",
			"Xml/string/en/koradditionaldescription_30.xml",
			"Xml/string/en/koradditionaldescription_40.xml",
			"Xml/string/en/koradditionaldescription_50.xml",
			"Xml/string/en/koradditionaldescription_60.xml",
			"Xml/string/en/koradditionaldescription_70.xml",
			"Xml/string/en/koradditionaldescription_80.xml",
			"Xml/string/en/koradditionaldescription_90.xml",
			"Xml/string/en/koradditionaldescription_100.xml",
			"Xml/string/en/koradditionaldescription_110.xml"
		};
		
		for (const char* current : paths)
		{
			Archive::ArchivePath path = gms2Reader.GetPath(current, true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");
				const tinyxml2::XMLAttribute* levelAttribute = keyElement->FindAttribute("level");

				if (!idAttribute || !nameAttribute || !levelAttribute) continue;

				Enum::EffectId id = (Enum::EffectId)atoi(idAttribute->Value());
				Enum::EffectLevel level = (Enum::EffectLevel)atoi(levelAttribute->Value());

				auto& effect = gms2Data.Effects[id];

				effect.Name = nameAttribute->Value();
				effect.Names[level] = nameAttribute->Value();
			}
		}
	}
	{
		const char* paths[] = {
			"Xml/string/en/koradditionaldescription.xml",
			"Xml/string/en/koradditionaldescription_1.xml",
			"Xml/string/en/koradditionaldescription_10.xml",
			"Xml/string/en/koradditionaldescription_20.xml",
			"Xml/string/en/koradditionaldescription_30.xml",
			"Xml/string/en/koradditionaldescription_40.xml",
			"Xml/string/en/koradditionaldescription_50.xml",
			"Xml/string/en/koradditionaldescription_60.xml",
			"Xml/string/en/koradditionaldescription_70.xml",
			"Xml/string/en/koradditionaldescription_80.xml",
			"Xml/string/en/koradditionaldescription_90.xml",
			"Xml/string/en/koradditionaldescription_100.xml",
			"Xml/string/en/koradditionaldescription_110.xml"
		};

		for (const char* current : paths)
		{
			Archive::ArchivePath path = kms2Reader.GetPath(current, true);

			output.clear();

			path.Read(output);

			if (output.size() == 0)
			{
				std::cout << "failed to read " << path.GetPath() << std::endl;

				return false;
			}

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
				const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");
				const tinyxml2::XMLAttribute* levelAttribute = keyElement->FindAttribute("level");

				if (!idAttribute || !nameAttribute || !levelAttribute) continue;

				Enum::EffectId id = (Enum::EffectId)atoi(idAttribute->Value());
				Enum::EffectLevel level = (Enum::EffectLevel)atoi(levelAttribute->Value());

				auto& effect = kms2Data.Effects[id];

				effect.Name = nameAttribute->Value();
				effect.Names[level] = nameAttribute->Value();
			}
		}
	}
	{
		Archive::ArchivePath path = gms2Reader.GetPath("Xml/string/en/skillname.xml", true);

		output.clear();

		path.Read(output);

		if (output.size() == 0)
		{
			std::cout << "failed to read " << path.GetPath() << std::endl;

			return false;
		}

		tinyxml2::XMLDocument document;

		document.Parse(output.data(), output.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
		{
			const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
			const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

			if (!idAttribute || !nameAttribute) continue;

			Enum::SkillId id = (Enum::SkillId)atoi(idAttribute->Value());

			gms2Data.Skills[id].Name = nameAttribute->Value();
		}
	}
	{
		Archive::ArchivePath path = kms2Reader.GetPath("Xml/string/en/skillname.xml", true);

		output.clear();

		path.Read(output);

		if (output.size() == 0)
		{
			std::cout << "failed to read " << path.GetPath() << std::endl;

			return false;
		}

		tinyxml2::XMLDocument document;

		document.Parse(output.data(), output.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		for (tinyxml2::XMLElement* keyElement = rootElement ? rootElement->FirstChildElement() : nullptr; keyElement; keyElement = keyElement->NextSiblingElement())
		{
			const tinyxml2::XMLAttribute* idAttribute = keyElement->FindAttribute("id");
			const tinyxml2::XMLAttribute* nameAttribute = keyElement->FindAttribute("name");

			if (!idAttribute || !nameAttribute) continue;

			Enum::SkillId id = (Enum::SkillId)atoi(idAttribute->Value());

			kms2Data.Skills[id].Name = nameAttribute->Value();
		}
	}

	printBaseStats |= ParserUtils::Packets::PrintPacketOutput;

	showSuccesses &= !regenerate;
	showSeen &= !regenerate;
	showUnparsed &= !regenerate;
	showUnused &= !regenerate;
	printBaseStats &= !regenerate;

	OutputSchema::readSchemas(schemaDir / "shared");
	GameSchema::readSchemas(schemaDir / "gms2", true);
	GameSchema::readSchemas(schemaDir / "kms2", false);
	//GameSchema::validateSchemas(gms2Reader, true, validateGms2Dirs);
	//GameSchema::validateSchemas(kms2Reader, false, validateKms2Dirs);
	//
	//OutputSchema::readSchemas(schemaDir / "output");
	OutputSchema::readSchemas(packetSchemaDir / "output");
	PacketSchema::readSchemas(packetSchemaDir / "versions");


	if (regenerate)
	{
		PacketSchema::generateParsers();
		PacketSchema::generateHandlers("SniffHandler");
		OutputSchema::generateGameData();
	}
	else
	{
		ParserUtils::Packets::parseMsb("A:/trevo/Downloads/SmitingAuraSniffVid.msb");
	}

	std::unordered_set<unsigned int> versions;

	for (const auto& entry : fs::recursive_directory_iterator(msbDir))
	{
		if (regenerate)
		{
			break;
		}

		fs::path extension = entry.path().extension();

		if (extension != ".msb")
		{
			continue;
		}

		//parseMsb(entry.path());
		//
		//std::cout << "parsing [" << version << "] " << entry.path().string() << std::endl;

		unsigned int version = ParserUtils::Packets::parseMsb(entry.path());

		if (!versions.contains(version))
		{
			versions.insert(version);

			//std::cout << version << std::endl;
		}
	}

	std::vector<unsigned long long> versions2;

	for (unsigned long long version : ParserUtils::Packets::printedPacketAlready)
	{
		versions2.push_back(version);
	}

	std::sort(versions2.begin(), versions2.end());

	unsigned short lastOp = 0xFFFF;

	for (unsigned long long versionLenDat : versions2)
	{
		unsigned int versionDat = (unsigned int)(versionLenDat >> 32);
		unsigned short version = (unsigned short)(versionDat & 0xFFFF);
		unsigned short opcode = (unsigned short)((versionDat >> 16) & 0xFFFF);
		unsigned int length = (unsigned int)(versionLenDat & 0xFFFFFFFF);

		if (lastOp != opcode)
			std::cout << std::endl << std::hex << "0x" << opcode << ": " << std::dec;

		lastOp = opcode;

		std::cout << version << "[" << length << "]" << ", ";
	}

	std::cout << std::endl << std::endl;

	if (printBaseStats)
	{
		const auto printStats = [](const decltype(Networking::Packets::Gms2JobBaseStats)& data, const char* text)
		{
			if (!data.size()) return;

			std::cout << text << std::endl;

			typedef std::unordered_map<unsigned short, Networking::Packets::ActorStats> ActorVec;

			std::vector<unsigned int> jobEntries;
			std::vector<const ActorVec*> jobData;

			for (const auto& jobEntry : data)
			{
				jobEntries.push_back((((unsigned int)jobEntry.first) << 16) | (unsigned int)jobData.size());
				jobData.push_back(&jobEntry.second);
			}

			std::sort(jobEntries.begin(), jobEntries.end());

			for (unsigned int index : jobEntries)
			{
				Enum::JobCode code = (Enum::JobCode)(index >> 16);
				const auto& jobEntry = *jobData[index & 0xFFFF];

				std::cout << "\t" << Networking::Packets::JobNames.find((unsigned short)code)->second << ":" << std::endl;

				std::vector<unsigned int> levelEntries;
				std::vector<const Networking::Packets::ActorStats*> levelData;

				for (const auto& levelEntry : jobEntry)
				{
					levelEntries.push_back((((unsigned int)levelEntry.first) << 16) | (unsigned int)levelData.size());
					levelData.push_back(&levelEntry.second);
				}

				std::sort(levelEntries.begin(), levelEntries.end());

				for (unsigned int index : levelEntries)
				{
					unsigned short level = (unsigned short)(index >> 16);
					const auto&  levelEntry = *levelData[index & 0xFFFF];

					std::cout << "\t\t" << level << ":" << std::endl;

					for (const auto& stat : levelEntry.Basic)
					{
						std::cout << "\t\t\t" << Networking::Packets::StatNames.find(stat.first)->second << ": " << stat.second.Base << std::endl;

						if (stat.first == Enum::StatAttributeBasic::SpRegen || stat.first == Enum::StatAttributeBasic::SpRegenInterval)
						{
							std::cout << "\t\t\t" << Networking::Packets::StatNames.find(stat.first)->second << " Max: " << stat.second.Max << std::endl;
							std::cout << "\t\t\t" << Networking::Packets::StatNames.find(stat.first)->second << " Current: " << stat.second.Current << std::endl;
						}
					}
				}
			}
		};

		printStats(Networking::Packets::Gms2JobBaseStats, "\ngms2:");
		printStats(Networking::Packets::Kms2JobBaseStats, "\nkms2:");
	}

	if (regenerate || (!showSuccesses && !showSeen))
	{
		return 0;
	}

	if (showSuccesses)
	{
		std::vector<unsigned int> successVersions;
		std::vector<const ParserUtils::Packets::VersionSuccesses*> successes;

		for (const auto& successEntry : ParserUtils::Packets::successfulPackets)
		{
			unsigned int index = (unsigned int)successes.size();
			successVersions.push_back(index | ((unsigned int)successEntry.first << 16));
			successes.push_back(&successEntry.second);
		}

		std::sort(successVersions.begin(), successVersions.end());

		std::cout << "successful parsed opcodes:" << std::endl;

		for (unsigned int entry : successVersions)
		{
			unsigned short version = (unsigned short)(entry >> 16);
			unsigned int index = entry & 0xFFFF;

			std::cout << std::dec << "\t" << version << std::hex << ":\n\t\tClient: ";

			std::vector<unsigned short> opcodes;

			for (unsigned short opcode : successes[index]->ServerPackets)
			{
				opcodes.push_back(opcode | 0x8000);
			}

			for (unsigned short opcode : successes[index]->ClientPackets)
			{
				opcodes.push_back(opcode);
			}

			std::sort(opcodes.begin(), opcodes.end());

			bool lastWasServer = false;

			for (unsigned short opcode : opcodes)
			{
				bool isServer = (opcode & 0x8000) != 0;

				opcode &= 0x7FFF;

				if (lastWasServer != isServer)
				{
					std::cout << "\n\t\tServer: ";
				}

				lastWasServer = isServer;

				std::cout << "0x" << opcode << ", ";
			}

			std::cout << std::dec << std::endl;
		}
	}

	if (showSeen)
	{
		std::vector<unsigned int> seenVersions;
		std::vector<const ParserUtils::Packets::VersionSuccesses*> seen;

		for (const auto& seenEntry : ParserUtils::Packets::seenPackets)
		{
			unsigned int index = (unsigned int)seen.size();
			seenVersions.push_back(index | ((unsigned int)seenEntry.first << 16));
			seen.push_back(&seenEntry.second);
		}

		std::sort(seenVersions.begin(), seenVersions.end());

		std::cout << "seen opcodes:" << std::endl;

		for (unsigned int entry : seenVersions)
		{
			unsigned short version = (unsigned short)(entry >> 16);
			unsigned int index = entry & 0xFFFF;

			std::cout << std::dec << "\t" << version << std::hex << ":\n\t\tClient: ";

			std::vector<unsigned short> opcodes;

			for (unsigned short opcode : seen[index]->ServerPackets)
			{
				opcodes.push_back(opcode | 0x8000);
			}

			for (unsigned short opcode : seen[index]->ClientPackets)
			{
				opcodes.push_back(opcode);
			}

			std::sort(opcodes.begin(), opcodes.end());

			bool lastWasServer = false;

			for (unsigned short opcode : opcodes)
			{
				bool isServer = (opcode & 0x8000) != 0;

				opcode &= 0x7FFF;

				if (lastWasServer != isServer)
				{
					std::cout << "\n\t\tServer: ";
				}

				lastWasServer = isServer;

				std::cout << "0x" << opcode << ", ";
			}

			std::cout << std::dec << std::endl;
		}
	}

	if (showUnparsed)
	{
		std::vector<unsigned int> unparsedVersions;
		std::vector<const ParserUtils::Packets::VersionSuccesses*> unparsed;

		for (const auto& unparsedEntry : ParserUtils::Packets::unparsedPackets)
		{
			unsigned int index = (unsigned int)unparsed.size();
			unparsedVersions.push_back(index | ((unsigned int)unparsedEntry.first << 16));
			unparsed.push_back(&unparsedEntry.second);
		}

		std::sort(unparsedVersions.begin(), unparsedVersions.end());

		std::cout << "unparsed opcodes:" << std::endl;

		for (unsigned int entry : unparsedVersions)
		{
			unsigned short version = (unsigned short)(entry >> 16);
			unsigned int index = entry & 0xFFFF;

			std::cout << std::dec << "\t" << version << std::hex << ":\n\t\tClient: ";

			std::vector<unsigned short> opcodes;

			for (unsigned short opcode : unparsed[index]->ServerPackets)
			{
				opcodes.push_back(opcode | 0x8000);
			}

			for (unsigned short opcode : unparsed[index]->ClientPackets)
			{
				opcodes.push_back(opcode);
			}

			std::sort(opcodes.begin(), opcodes.end());

			bool lastWasServer = false;

			for (unsigned short opcode : opcodes)
			{
				bool isServer = (opcode & 0x8000) != 0;

				opcode &= 0x7FFF;

				if (lastWasServer != isServer)
				{
					std::cout << "\n\t\tServer: ";
				}

				lastWasServer = isServer;

				std::cout << "0x" << opcode << ", ";
			}

			std::cout << std::dec << std::endl;
		}
	}

	return 0;
}