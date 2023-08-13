#include <fstream>

#include "Schema/GameSchema.h"
#include "Schema/SchemaTypes.h"
#include "Schema/OutputSchema.h"
#include "Schema/ModuleWriter.h"
#include "Schema/PacketScheam.h"

#include <PacketProcessing/PacketParser.h>
#include <ParserUtils/DataStream.h>

namespace fs = std::filesystem;

fs::path ms2Root = "B:/Files/Maplstory 2 Client/appdata";
fs::path ms2RootExtracted = "B:/Files/ms2export/export/";
fs::path kms2Root = "B:/Files/ms2export/kms2export";
const fs::path schemaDir = "./schema";
const fs::path packetSchemaDir = "./packetSchema";
Archive::ArchiveReader gms2Reader;
Archive::ArchiveReader kms2Reader;

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

		void parseMsb(const fs::path& path)
		{
			std::ifstream file(path, std::ios::binary);

			unsigned short version;
			unsigned short localPort;
			unsigned short locale;
			unsigned int build;
			std::string endPoint;
			std::string remoteEndPoint;
			unsigned short remotePort;

			read(file, version);

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

				ParserUtils::DataStream stream{ { reinterpret_cast<char*>(buffer.data()), buffer.size() } };

				Networking::Packets::ParsePacket(stream, build, !outbound, opcode);
			}
		}
	}
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

	//GameSchema::readSchemas(schemaDir / "gms2", true);
	//GameSchema::readSchemas(schemaDir / "kms2", false);
	//GameSchema::validateSchemas(gms2Reader, true, validateGms2Dirs);
	//GameSchema::validateSchemas(kms2Reader, false, validateKms2Dirs);
	//
	//OutputSchema::readSchemas(schemaDir / "output");
	PacketSchema::readSchemas(packetSchemaDir / "versions");
	PacketSchema::generateParsers();
	//OutputSchema::generateGameData();

	ParserUtils::Packets::parseMsb("A:/trevo/Downloads/SmitingAuraSniffVid.msb");


	return 0;
}