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
fs::path kms2Root = "B:/Files/ms2export/kms2export";
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

				handler.PacketStream =  ParserUtils::DataStream { { reinterpret_cast<char*>(buffer.data()), buffer.size() } };
				handler.FoundValues = {};

				ParserUtils::DataStream& stream = handler.PacketStream;

				std::cout << std::dec;

				unsigned long long opcodeVersion = ((((unsigned long long)opcode << 16) | (unsigned long long)build) << 32) | buffer.size();

				stream.IgnoreUnknownValues = (!outbound ? ignoreServerPacketUnknownValues : ignoreClientPacketUnknownValues).contains(opcode);
				stream.SuppressErrors = printedPacketAlready.contains(opcodeVersion);

				Networking::Packets::ParsePacket(handler, build, !outbound, opcode);

				++readPackets;

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

						std::cout << "parsing [" << build << "] " << path.string() << std::endl;
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

					std::string values = handler.FoundValues.str();

					if (values.size())
					{
						std::cout << values << std::endl;
					}

					std::cout << std::dec << std::endl;

					if (stream.HasRecentlyFailed || stream.Index < stream.Data.size())
					{
						//printedAlready.insert(build);
						printedPacketAlready.insert(opcodeVersion);

						handler.PacketStream = ParserUtils::DataStream{ { reinterpret_cast<char*>(buffer.data()), buffer.size() } };
						handler.FoundValues = {};

						handler.PacketStream.IgnoreUnknownValues = (!outbound ? ignoreServerPacketUnknownValues : ignoreClientPacketUnknownValues).contains(opcode);

						Networking::Packets::ParsePacket(handler, build, !outbound, opcode);
					}
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
		unsigned int id = atoi(path.GetPath().filename().stem().string().c_str());

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

			unsigned int id = atoi(idAttribute->Value());

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

	bool regenerate = !true;

	if (!regenerate)
	{
		Archive::ForEachFile(gms2Reader.GetPath("Xml/npc", true), true, visit1);
		Archive::ForEachFile(kms2Reader.GetPath("Xml/npcdata", true), true, visit2);

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

				unsigned int id = atoi(idAttribute->Value());
				
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

				unsigned int id = atoi(idAttribute->Value());

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

				unsigned int id = atoi(idAttribute->Value());

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

				unsigned int id = atoi(idAttribute->Value());

				kms2Data.Maps[id].Name = nameAttribute->Value();
			}
		}
	}

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

	fs::path msbDir = "B:/Files/ms2sniffs";

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

	std::cout << std::endl;

	return 0;
}