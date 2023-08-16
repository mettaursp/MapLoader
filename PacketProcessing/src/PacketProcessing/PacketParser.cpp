#include "PacketParser.h"

#include <vector>

#include <ParserUtils/PacketParsing.h>

#include "PacketOutput.h"

namespace Networking
{
	namespace Packets
	{
		void ParsePacket(ParserUtils::DataStream& stream, unsigned short version, bool isServer, unsigned short opcode)
		{
			static const std::vector<size_t> versionIndices = {
				1, 2
			};
			static const std::vector<PacketVersionData> versions = {
				{
					0x1d, 0x1,
					{
						{ "UserChat", &ParsePacket<12, ServerPacket, 0x1d> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Buff", &ParsePacket<12, ServerPacket, 0x48> }
					},
					{
						{ "ResponseVersion", &ParsePacket<12, ClientPacket, 0x1> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "ResponseKey", &ParsePacket<12, ClientPacket, 0x4> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "ResponseHeartbeat", &ParsePacket<12, ClientPacket, 0xa> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestQuit", &ParsePacket<12, ClientPacket, 0xd> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Skill", &ParsePacket<12, ClientPacket, 0x20> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "SystemInfo", &ParsePacket<12, ClientPacket, 0xb7> }
					}
				},
				{
					0x1d, 0x1,
					{
						{ "UserChat", &ParsePacket<12, ServerPacket, 0x1d> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Buff", &ParsePacket<13, ServerPacket, 0x47> }
					},
					{
						{ "ResponseVersion", &ParsePacket<12, ClientPacket, 0x1> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "ResponseKey", &ParsePacket<12, ClientPacket, 0x4> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "ResponseHeartbeat", &ParsePacket<12, ClientPacket, 0xa> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestQuit", &ParsePacket<12, ClientPacket, 0xd> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Skill", &ParsePacket<12, ClientPacket, 0x20> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "SystemInfo", &ParsePacket<12, ClientPacket, 0xb7> }
					}
				},
				{
					0x1d, 0x1,
					{
						{ "UserChat", &ParsePacket<12, ServerPacket, 0x1d> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Buff", &ParsePacket<13, ServerPacket, 0x47> }
					},
					{
						{ "ResponseVersion", &ParsePacket<12, ClientPacket, 0x1> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "ResponseKey", &ParsePacket<12, ClientPacket, 0x4> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "ResponseHeartbeat", &ParsePacket<12, ClientPacket, 0xa> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestQuit", &ParsePacket<12, ClientPacket, 0xd> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Skill", &ParsePacket<2503, ClientPacket, 0x20> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "SystemInfo", &ParsePacket<12, ClientPacket, 0xb7> }
					}
				}
			};

			size_t versionIndex = version == 12 ? 0 : versionIndices[std::min(1, std::max(version, (unsigned short)2502) - 2502)];
			const PacketVersionData& versionData = versions[versionIndex];

			size_t minOpcode = isServer ? versionData.MinServerOpcode : versionData.MinClientOpcode;

			const auto& opcodes = isServer ? versionData.ServerCallbacks : versionData.ClientCallbacks;

			if (opcode < minOpcode || opcode - minOpcode >= opcodes.size())
			{
				return;
			}

			if constexpr (ParserUtils::Packets::PrintOutput)
			{
				std::cout << "[" << version << "] Packet Opcode 0x" << std::hex << opcode << std::dec << ": " << opcodes[opcode - minOpcode].Name << std::endl;
			}

			opcodes[opcode - minOpcode].Callback(stream);
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::ResponseVersionPacket output0;

			Read<unsigned int>("version", stream, output0.Version, "\t");

			unsigned short unknown_var1 = 0;
			Read<unsigned short>("unknown", stream, unknown_var1, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var1, (unsigned short)48, (unsigned short)74, (unsigned short)90);

			unsigned short locale_var2 = 0;
			Read<unsigned short>("locale", stream, locale_var2, "\t");

			if (stream.Succeeded())
			{
				PacketParsed<Client::ResponseVersionPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x4>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::ResponseKeyPacket output0;

			long long accountId_var0 = 0;
			Read<long long>("accountId", stream, accountId_var0, "\t");

			output0.AccountId = (long long)accountId_var0;

			if (accountId_var0 != 0)
			{
				Read<int>("tokenA", stream, output0.TokenA, "\t\t");
				Read<int>("tokenB", stream, output0.TokenB, "\t\t");

				unsigned long long machineHigh_var3 = 0;
				Read<unsigned long long>("machineHigh", stream, machineHigh_var3, "\t\t");

				unsigned long long machineLow_var4 = 0;
				Read<unsigned long long>("machineLow", stream, machineLow_var4, "\t\t");
			}

			if (stream.Succeeded())
			{
				PacketParsed<Client::ResponseKeyPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xa>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::ResponseHeartbeatPacket output0;

			Read<int>("serverTick", stream, output0.ServerTick, "\t");
			Read<int>("clientTick", stream, output0.ClientTick, "\t");

			if (stream.Succeeded())
			{
				PacketParsed<Client::ResponseHeartbeatPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xd>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::RequestQuitPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1);

			output0.Mode = (Client::RequestQuitPacket::ModeEnum)mode_var0;

			if (stream.Succeeded())
			{
				PacketParsed<Client::RequestQuitPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x20>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Client::SkillCastPacket output0;

				Read<long long>("skillSn", stream, output0.SkillSn, "\t\t");
				Read<int>("serverTick", stream, output0.ServerTick, "\t\t");
				Read<int>("skillId", stream, output0.SkillId, "\t\t");
				Read<short>("skillLevel", stream, output0.SkillLevel, "\t\t");
				Read<unsigned char>("attackPoint", stream, output0.AttackPoint, "\t\t");
				Read<Vector3S>("position", stream, output0.Position, "\t\t");
				Read<Vector3S>("direction", stream, output0.Direction, "\t\t");
				Read<Vector3S>("rotation", stream, output0.Rotation, "\t\t");

				float unknown_var9 = 0;
				Read<float>("unknown", stream, unknown_var9, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var9, (float)0);

				Read<int>("clientTick", stream, output0.ClientTick, "\t\t");

				bool unknown_var11 = false;
				Read<bool>("unknown", stream, unknown_var11, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", stream, unknown_var12, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var12, (long long)0);

				bool flag_var13 = false;
				Read<bool>("flag", stream, flag_var13, "\t\t");

				ValidateValues(stream, "flag", "\t\t", flag_var13, (bool)0, (bool)1);

				output0.Flag = (bool)flag_var13;

				if (flag_var13)
				{
					int unknown_var14 = 0;
					Read<int>("unknown", stream, unknown_var14, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var14, (int)0);

					std::string unknown_var15;
					Read<std::string>("unknown", stream, unknown_var15, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillCastPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				unsigned char damageMode_var16 = 0;
				Read<unsigned char>("damageMode", stream, damageMode_var16, "\t\t");

				ValidateValues(stream, "damageMode", "\t\t", damageMode_var16, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var16 == 0)
				{
					Client::SkillSyncDamagePacket output1;

					Read<long long>("skillSn", stream, output1.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output1.AttackPoint, "\t\t\t");
					Read<Vector3S>("position", stream, output1.Position, "\t\t\t");
					Read<Vector3S>("rotation", stream, output1.Rotation, "\t\t\t");

					unsigned char count_var21 = 0;
					Read<unsigned char>("count", stream, count_var21, "\t\t\t");

					int unknown_var22 = 0;
					Read<int>("unknown", stream, unknown_var22, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var22, (int)0);

					output1.Projectiles.resize(count_var21);

					for (unsigned char i = 0; i < count_var21; ++i)
					{
						auto& projectile_array0 = output1.Projectiles[i];

						Read<int>("attackCount", stream, projectile_array0.AttackCount, "\t\t\t\t");
						Read<int>("sourceId", stream, projectile_array0.SourceId, "\t\t\t\t");
						Read<int>("targetId", stream, projectile_array0.TargetId, "\t\t\t\t");
						Read<unsigned char>("index", stream, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var27 = false;
						Read<bool>("moreTargets", stream, moreTargets_var27, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var27, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var27)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							Read<int>("attackCount", stream, nextTarget_array1.AttackCount, "\t\t\t\t\t");
							Read<int>("sourceId", stream, nextTarget_array1.SourceId, "\t\t\t\t\t");
							Read<int>("targetId", stream, nextTarget_array1.TargetId, "\t\t\t\t\t");
							Read<unsigned char>("index", stream, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var32 = 0;
							Read<unsigned char>("unknown", stream, unknown_var32, "\t\t\t\t\t");

							Read<bool>("moreTargets", stream, moreTargets_var27, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var27, (bool)0, (bool)1);

							++j;
						}
					}

					if (stream.Succeeded())
					{
						PacketParsed<Client::SkillSyncDamagePacket>(output1);

						return;
					}
				}

				if (damageMode_var16 == 1)
				{
					Client::SkillDamagePacket output2;

					Read<long long>("skillSn", stream, output2.SkillSn, "\t\t\t");
					Read<int>("attackCounter", stream, output2.AttackCounter, "\t\t\t");
					Read<int>("sourceId", stream, output2.SourceId, "\t\t\t");
					Read<Vector3S>("position", stream, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", stream, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", stream, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output2.AttackPoint, "\t\t\t");

					unsigned char count_var40 = 0;
					Read<unsigned char>("count", stream, count_var40, "\t\t\t");

					int unknown_var41 = 0;
					Read<int>("unknown", stream, unknown_var41, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var41, (int)0);

					output2.Hits.resize(count_var40);

					for (unsigned char i = 0; i < count_var40; ++i)
					{
						auto& hitActor_array2 = output2.Hits[i];

						Read<int>("entityId", stream, hitActor_array2.EntityId, "\t\t\t\t");

						unsigned char unknown_var43 = 0;
						Read<unsigned char>("unknown", stream, unknown_var43, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var43, (unsigned char)0);
					}

					if (stream.Succeeded())
					{
						PacketParsed<Client::SkillDamagePacket>(output2);

						return;
					}
				}

				if (damageMode_var16 == 2)
				{
					Client::SkillRegionSkillPacket output3;

					Read<long long>("skillSn", stream, output3.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output3.AttackPoint, "\t\t\t");

					int unknown_var46 = 0;
					Read<int>("unknown", stream, unknown_var46, "\t\t\t");
					Read<int>("attackCounter", stream, output3.AttackCounter, "\t\t\t");
					Read<Vector3S>("position", stream, output3.Position, "\t\t\t");
					Read<Vector3S>("rotation", stream, output3.Rotation, "\t\t\t");

					if (stream.Succeeded())
					{
						PacketParsed<Client::SkillRegionSkillPacket>(output3);

						return;
					}
				}
			}

			if (mode_var0 == 2)
			{
				Client::SkillSyncPacket output4;

				Read<long long>("skillSn", stream, output4.SkillSn, "\t\t");
				Read<int>("skillId", stream, output4.SkillId, "\t\t");
				Read<short>("skillLevel", stream, output4.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", stream, output4.MotionPoint, "\t\t");
				Read<Vector3S>("position", stream, output4.Position, "\t\t");

				Vector3S unknown_var55;
				Read<Vector3S>("unknown", stream, unknown_var55, "\t\t");
				Read<Vector3S>("rotation", stream, output4.Rotation, "\t\t");

				Vector3S unknown_var57;
				Read<Vector3S>("unknown", stream, unknown_var57, "\t\t");

				bool unknown_var58 = false;
				Read<bool>("unknown", stream, unknown_var58, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var58, (bool)0, (bool)1);

				int unknown_var59 = 0;
				Read<int>("unknown", stream, unknown_var59, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var59, (int)0);

				unsigned char unknown_var60 = 0;
				Read<unsigned char>("unknown", stream, unknown_var60, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var60, (unsigned char)0);

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillSyncPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", stream, output5.SkillSn, "\t\t");
				Read<int>("serverTick", stream, output5.ServerTick, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillSyncTickPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", stream, output6.SkillSn, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xb7>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::SystemInfoPacket output0;

			Read<std::wstring>("info", stream, output0.Info, "\t");

			if (stream.Succeeded())
			{
				PacketParsed<Client::SystemInfoPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Server::UserChatPacket output0;

			Read<long long>("accountId", stream, output0.AccountId, "\t");
			Read<long long>("characterId", stream, output0.CharacterId, "\t");
			Read<std::wstring>("characterName", stream, output0.CharacterName, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", stream, unknown_var3, "\t");
			Read<std::wstring>("message", stream, output0.Message, "\t");

			int type_var5 = 0;
			Read<int>("type", stream, type_var5, "\t");

			ValidateValues(stream, "type", "\t", type_var5, (int)8, (int)0, (int)3, (int)4, (int)5, (int)6, (int)7, (int)9, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)18, (int)19, (int)20, (int)23);

			output0.Type = (Server::UserChatPacket::TypeEnum)type_var5;

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", stream, unknown_var6, "\t");
			Read<int>("channelId", stream, output0.ChannelId, "\t");

			if (type_var5 == 3)
			{
				std::wstring unknown_var8;
				Read<std::wstring>("unknown", stream, unknown_var8, "\t\t");
			}

			if (type_var5 == 16)
			{
				Read<int>("superChatId", stream, output0.SuperChatId, "\t\t");
			}

			if (type_var5 == 20)
			{
				Read<long long>("clubId", stream, output0.ClubId, "\t\t");
			}

			unsigned char unknown_var11 = 0;
			Read<unsigned char>("unknown", stream, unknown_var11, "\t");

			if (stream.Succeeded())
			{
				PacketParsed<Server::UserChatPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Server::BuffPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			output0.Mode = (Server::BuffPacket::ModeEnum)mode_var0;

			Read<int>("targetActor", stream, output0.TargetActor, "\t");

			int instanceId_var2 = 0;
			Read<int>("instanceId", stream, instanceId_var2, "\t");

			output0.InstanceId = (int)instanceId_var2;

			int sourceActor_var3 = 0;
			Read<int>("sourceActor", stream, sourceActor_var3, "\t");

			if (instanceId_var2 != 0)
			{
				if (mode_var0 == 0)
				{
					Read<int>("startTime", stream, output0.StartTime, "\t\t\t");
					Read<int>("endTime", stream, output0.EndTime, "\t\t\t");
					Read<int>("effectId", stream, output0.EffectId, "\t\t\t");
					Read<short>("effectLevel", stream, output0.EffectLevel, "\t\t\t");
					Read<int>("stacks", stream, output0.Stacks, "\t\t\t");
					Read<bool>("hasShield", stream, output0.UpdateShield, "\t\t\t");

					ValidateValues(stream, "hasShield", "\t\t\t", output0.UpdateShield, (bool)0, (bool)1);

					Read<long long>("shieldHealth", stream, output0.ShieldHealth, "\t\t\t");
				}

				if (mode_var0 == 2)
				{
					int flags_var11 = 0;
					Read<int>("flags", stream, flags_var11, "\t\t\t");

					output0.UpdateEffect = GetBit(flags_var11, 0);
					output0.UpdateShield = GetBit(flags_var11, 1);

					if (GetBit(flags_var11, 0) == 1)
					{
						Read<int>("startTime", stream, output0.StartTime, "\t\t\t\t");
						Read<int>("endTime", stream, output0.EndTime, "\t\t\t\t");
						Read<int>("effectId", stream, output0.EffectId, "\t\t\t\t");
						Read<short>("effectLevel", stream, output0.EffectLevel, "\t\t\t\t");
						Read<int>("stacks", stream, output0.Stacks, "\t\t\t\t");
						Read<bool>("enabled", stream, output0.Enabled, "\t\t\t\t");

						ValidateValues(stream, "enabled", "\t\t\t\t", output0.Enabled, (bool)0, (bool)1);
					}

					if (GetBit(flags_var11, 1) == 1)
					{
						Read<long long>("shieldHealth", stream, output0.ShieldHealth, "\t\t\t\t");
					}
				}
			}

			if (stream.Succeeded())
			{
				PacketParsed<Server::BuffPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<13, ServerPacket, 0x47>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Server::BuffPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			output0.Mode = (Server::BuffPacket::ModeEnum)mode_var0;

			Read<int>("targetActor", stream, output0.TargetActor, "\t");

			int instanceId_var2 = 0;
			Read<int>("instanceId", stream, instanceId_var2, "\t");

			output0.InstanceId = (int)instanceId_var2;

			int sourceActor_var3 = 0;
			Read<int>("sourceActor", stream, sourceActor_var3, "\t");

			if (mode_var0 == 0)
			{
				Read<int>("startTime", stream, output0.StartTime, "\t\t");
				Read<int>("endTime", stream, output0.EndTime, "\t\t");
				Read<int>("effectId", stream, output0.EffectId, "\t\t");
				Read<short>("effectLevel", stream, output0.EffectLevel, "\t\t");
				Read<int>("stacks", stream, output0.Stacks, "\t\t");
				Read<bool>("hasShield", stream, output0.UpdateShield, "\t\t");

				ValidateValues(stream, "hasShield", "\t\t", output0.UpdateShield, (bool)0, (bool)1);

				Read<long long>("shieldHealth", stream, output0.ShieldHealth, "\t\t");
			}

			if (mode_var0 == 2)
			{
				int flags_var11 = 0;
				Read<int>("flags", stream, flags_var11, "\t\t");

				output0.UpdateEffect = GetBit(flags_var11, 0);
				output0.UpdateShield = GetBit(flags_var11, 1);

				if (GetBit(flags_var11, 0) == 1)
				{
					Read<int>("startTime", stream, output0.StartTime, "\t\t\t");
					Read<int>("endTime", stream, output0.EndTime, "\t\t\t");
					Read<int>("effectId", stream, output0.EffectId, "\t\t\t");
					Read<short>("effectLevel", stream, output0.EffectLevel, "\t\t\t");
					Read<int>("stacks", stream, output0.Stacks, "\t\t\t");
					Read<bool>("enabled", stream, output0.Enabled, "\t\t\t");

					ValidateValues(stream, "enabled", "\t\t\t", output0.Enabled, (bool)0, (bool)1);
				}

				if (GetBit(flags_var11, 1) == 1)
				{
					Read<long long>("shieldHealth", stream, output0.ShieldHealth, "\t\t\t");
				}
			}

			if (instanceId_var2 == 0)
			{
				int unknown_var19 = 0;
				Read<int>("unknown", stream, unknown_var19, "\t\t");
			}

			if (stream.Succeeded())
			{
				PacketParsed<Server::BuffPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<2503, ClientPacket, 0x20>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Client::SkillCastPacket output0;

				Read<long long>("skillSn", stream, output0.SkillSn, "\t\t");
				Read<int>("serverTick", stream, output0.ServerTick, "\t\t");
				Read<int>("skillId", stream, output0.SkillId, "\t\t");
				Read<short>("skillLevel", stream, output0.SkillLevel, "\t\t");
				Read<unsigned char>("attackPoint", stream, output0.AttackPoint, "\t\t");
				Read<Vector3S>("position", stream, output0.Position, "\t\t");
				Read<Vector3S>("direction", stream, output0.Direction, "\t\t");
				Read<Vector3S>("rotation", stream, output0.Rotation, "\t\t");

				float unknown_var9 = 0;
				Read<float>("unknown", stream, unknown_var9, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var9, (float)0);

				Read<int>("clientTick", stream, output0.ClientTick, "\t\t");

				bool unknown_var11 = false;
				Read<bool>("unknown", stream, unknown_var11, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", stream, unknown_var12, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var12, (long long)0);

				long long unknown_var13 = 0;
				Read<long long>("unknown", stream, unknown_var13, "\t\t");

				bool flag_var14 = false;
				Read<bool>("flag", stream, flag_var14, "\t\t");

				ValidateValues(stream, "flag", "\t\t", flag_var14, (bool)0, (bool)1);

				output0.Flag = (bool)flag_var14;

				if (flag_var14)
				{
					int unknown_var15 = 0;
					Read<int>("unknown", stream, unknown_var15, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var15, (int)0);

					std::string unknown_var16;
					Read<std::string>("unknown", stream, unknown_var16, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillCastPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				unsigned char damageMode_var17 = 0;
				Read<unsigned char>("damageMode", stream, damageMode_var17, "\t\t");

				ValidateValues(stream, "damageMode", "\t\t", damageMode_var17, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var17 == 0)
				{
					Client::SkillSyncDamagePacket output1;

					Read<long long>("skillSn", stream, output1.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output1.AttackPoint, "\t\t\t");
					Read<Vector3S>("position", stream, output1.Position, "\t\t\t");
					Read<Vector3S>("rotation", stream, output1.Rotation, "\t\t\t");

					unsigned char count_var22 = 0;
					Read<unsigned char>("count", stream, count_var22, "\t\t\t");

					int unknown_var23 = 0;
					Read<int>("unknown", stream, unknown_var23, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var23, (int)0);

					output1.Projectiles.resize(count_var22);

					for (unsigned char i = 0; i < count_var22; ++i)
					{
						auto& projectile_array0 = output1.Projectiles[i];

						Read<int>("attackCount", stream, projectile_array0.AttackCount, "\t\t\t\t");
						Read<int>("sourceId", stream, projectile_array0.SourceId, "\t\t\t\t");
						Read<int>("targetId", stream, projectile_array0.TargetId, "\t\t\t\t");
						Read<unsigned char>("index", stream, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var28 = false;
						Read<bool>("moreTargets", stream, moreTargets_var28, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var28, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var28)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							Read<int>("attackCount", stream, nextTarget_array1.AttackCount, "\t\t\t\t\t");
							Read<int>("sourceId", stream, nextTarget_array1.SourceId, "\t\t\t\t\t");
							Read<int>("targetId", stream, nextTarget_array1.TargetId, "\t\t\t\t\t");
							Read<unsigned char>("index", stream, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var33 = 0;
							Read<unsigned char>("unknown", stream, unknown_var33, "\t\t\t\t\t");

							Read<bool>("moreTargets", stream, moreTargets_var28, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var28, (bool)0, (bool)1);

							++j;
						}
					}

					if (stream.Succeeded())
					{
						PacketParsed<Client::SkillSyncDamagePacket>(output1);

						return;
					}
				}

				if (damageMode_var17 == 1)
				{
					Client::SkillDamagePacket output2;

					Read<long long>("skillSn", stream, output2.SkillSn, "\t\t\t");
					Read<int>("attackCounter", stream, output2.AttackCounter, "\t\t\t");
					Read<int>("sourceId", stream, output2.SourceId, "\t\t\t");
					Read<Vector3S>("position", stream, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", stream, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", stream, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output2.AttackPoint, "\t\t\t");

					unsigned char count_var41 = 0;
					Read<unsigned char>("count", stream, count_var41, "\t\t\t");

					int unknown_var42 = 0;
					Read<int>("unknown", stream, unknown_var42, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var42, (int)0);

					output2.Hits.resize(count_var41);

					for (unsigned char i = 0; i < count_var41; ++i)
					{
						auto& hitActor_array2 = output2.Hits[i];

						Read<int>("entityId", stream, hitActor_array2.EntityId, "\t\t\t\t");

						unsigned char unknown_var44 = 0;
						Read<unsigned char>("unknown", stream, unknown_var44, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var44, (unsigned char)0);
					}

					if (stream.Succeeded())
					{
						PacketParsed<Client::SkillDamagePacket>(output2);

						return;
					}
				}

				if (damageMode_var17 == 2)
				{
					Client::SkillRegionSkillPacket output3;

					Read<long long>("skillSn", stream, output3.SkillSn, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output3.AttackPoint, "\t\t\t");

					int unknown_var47 = 0;
					Read<int>("unknown", stream, unknown_var47, "\t\t\t");
					Read<int>("attackCounter", stream, output3.AttackCounter, "\t\t\t");
					Read<Vector3S>("position", stream, output3.Position, "\t\t\t");
					Read<Vector3S>("rotation", stream, output3.Rotation, "\t\t\t");

					if (stream.Succeeded())
					{
						PacketParsed<Client::SkillRegionSkillPacket>(output3);

						return;
					}
				}
			}

			if (mode_var0 == 2)
			{
				Client::SkillSyncPacket output4;

				Read<long long>("skillSn", stream, output4.SkillSn, "\t\t");
				Read<int>("skillId", stream, output4.SkillId, "\t\t");
				Read<short>("skillLevel", stream, output4.SkillLevel, "\t\t");
				Read<unsigned char>("motionPoint", stream, output4.MotionPoint, "\t\t");
				Read<Vector3S>("position", stream, output4.Position, "\t\t");

				Vector3S unknown_var56;
				Read<Vector3S>("unknown", stream, unknown_var56, "\t\t");
				Read<Vector3S>("rotation", stream, output4.Rotation, "\t\t");

				Vector3S unknown_var58;
				Read<Vector3S>("unknown", stream, unknown_var58, "\t\t");

				bool unknown_var59 = false;
				Read<bool>("unknown", stream, unknown_var59, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var59, (bool)0, (bool)1);

				int unknown_var60 = 0;
				Read<int>("unknown", stream, unknown_var60, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var60, (int)0);

				unsigned char unknown_var61 = 0;
				Read<unsigned char>("unknown", stream, unknown_var61, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var61, (unsigned char)0);

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillSyncPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				Read<long long>("skillSn", stream, output5.SkillSn, "\t\t");
				Read<int>("serverTick", stream, output5.ServerTick, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillSyncTickPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				Read<long long>("skillSn", stream, output6.SkillSn, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

	}
}
