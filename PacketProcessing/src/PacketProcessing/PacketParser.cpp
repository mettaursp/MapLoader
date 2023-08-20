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
				1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3
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
						{ "SkillDamage", &ParsePacket<12, ServerPacket, 0x3e> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Buff", &ParsePacket<12, ServerPacket, 0x48> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "Trophy", &ParsePacket<12, ServerPacket, 0x5f> }
					},
					{
						{ "ResponseVersion", &ParsePacket<12, ClientPacket, 0x1> },
						{ "Handshake", &ParsePacket<12, ClientPacket, 0x2> },
						{ "LogIn", &ParsePacket<12, ClientPacket, 0x3> },
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
						{ "StateSkill", &ParsePacket<12, ClientPacket, 0x21> },
						{ "NpcTalk", &ParsePacket<12, ClientPacket, 0x22> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "SkillDamage", &ParsePacket<12, ServerPacket, 0x3e> },
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
						{ "Handshake", &ParsePacket<12, ClientPacket, 0x2> },
						{ "LogIn", &ParsePacket<13, ClientPacket, 0x3> },
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
						{ "StateSkill", &ParsePacket<12, ClientPacket, 0x21> },
						{ "NpcTalk", &ParsePacket<12, ClientPacket, 0x22> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "SkillDamage", &ParsePacket<2486, ServerPacket, 0x3d> },
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
						{ "Handshake", &ParsePacket<12, ClientPacket, 0x2> },
						{ "LogIn", &ParsePacket<13, ClientPacket, 0x3> },
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
						{ "StateSkill", &ParsePacket<12, ClientPacket, 0x21> },
						{ "NpcTalk", &ParsePacket<12, ClientPacket, 0x22> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "SkillDamage", &ParsePacket<2503, ServerPacket, 0x3d> },
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
						{ "Handshake", &ParsePacket<12, ClientPacket, 0x2> },
						{ "LogIn", &ParsePacket<13, ClientPacket, 0x3> },
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
						{ "StateSkill", &ParsePacket<12, ClientPacket, 0x21> },
						{ "NpcTalk", &ParsePacket<12, ClientPacket, 0x22> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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

			size_t versionIndex = version == 12 ? 0 : versionIndices[std::min(18, std::max(version, (unsigned short)2485) - 2485)];
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
		void ParsePacket<12, ClientPacket, 0x21>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0);

			if (mode_var0 == 0)
			{
				Client::StateSkillPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", stream, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				Read<unsigned int>("serverTick", stream, output0.ServerTick, "\t\t");

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", stream, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				unsigned short skillLevel_var4 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var4, "\t\t");

				ValidateValues(stream, "skillLevel", "\t\t", skillLevel_var4, (unsigned short)1);

				output0.SkillLevel = (Enum::SkillLevel)skillLevel_var4;

				Read<int>("animation", stream, output0.Animation, "\t\t");
				Read<int>("clientTick", stream, output0.ClientTick, "\t\t");

				long long unknown_var7 = 0;
				Read<long long>("unknown", stream, unknown_var7, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::StateSkillPacket>(output0);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::ResponseVersionPacket output0;

			Read<unsigned int>("version", stream, output0.Version, "\t");

			unsigned short feature_var1 = 0;
			Read<unsigned short>("feature", stream, feature_var1, "\t");

			unsigned short locale_var2 = 0;
			Read<unsigned short>("locale", stream, locale_var2, "\t");

			if (stream.Succeeded())
			{
				PacketParsed<Client::ResponseVersionPacket>(output0);

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
		void ParsePacket<12, ClientPacket, 0x2>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::HandshakePacket output0;

			Read<unsigned char>("function", stream, output0.Function, "\t");

			int count_var1 = 0;
			Read<int>("count", stream, count_var1, "\t");

			output0.Data.resize(count_var1);

			for (int i = 0; i < count_var1; ++i)
			{
				Read<std::wstring>("unknown", stream, output0.Data[i].String, "\t\t");

				long long unknown_var3 = 0;
				Read<long long>("unknown", stream, unknown_var3, "\t\t");
			}

			if (stream.Succeeded())
			{
				PacketParsed<Client::HandshakePacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x3>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			if (mode_var0 == 0)
			{
				Client::LogInPacket output0;

				Read<std::wstring>("username", stream, output0.Username, "\t\t");
				Read<std::wstring>("password", stream, output0.Password, "\t\t");

				short unknown_var3 = 0;
				Read<short>("unknown", stream, unknown_var3, "\t\t");
				Read<unsigned long long>("machineLow", stream, output0.MachineLow, "\t\t");
				Read<unsigned long long>("machineHigh", stream, output0.MachineHigh, "\t\t");

				int unknownMachineIdPtr_var6 = 0;
				Read<int>("unknownMachineIdPtr", stream, unknownMachineIdPtr_var6, "\t\t");
				Read<int>("sessionKey", stream, output0.SessionKey, "\t\t");
				Read<std::string>("locale", stream, output0.Locale, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::LogInPacket>(output0);

					return;
				}
			}

			if (mode_var0 != 0)
			{
				Client::LogInAuthTokenPacket output1;

				long long unknown_var9 = 0;
				Read<long long>("unknown", stream, unknown_var9, "\t\t");

				std::string authToken_var10;
				Read<std::string>("authToken", stream, authToken_var10, "\t\t");

				short unknown_var11 = 0;
				Read<short>("unknown", stream, unknown_var11, "\t\t");

				int unknown_var12 = 0;
				Read<int>("unknown", stream, unknown_var12, "\t\t");
				Read<unsigned long long>("machineLow", stream, output1.MachineLow, "\t\t");
				Read<unsigned long long>("machineHigh", stream, output1.MachineHigh, "\t\t");

				int unknown_var15 = 0;
				Read<int>("unknown", stream, unknown_var15, "\t\t");

				int unknown_var16 = 0;
				Read<int>("unknown", stream, unknown_var16, "\t\t");
				Read<std::string>("locale", stream, output1.Locale, "\t\t");

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", stream, unknown_var18, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::LogInAuthTokenPacket>(output1);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x4>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			Client::ResponseKeyPacket output0;

			long long accountId_var0 = 0;
			Read<long long>("accountId", stream, accountId_var0, "\t");

			output0.AccountId = (Enum::AccountId)accountId_var0;

			if (accountId_var0 != 0)
			{
				Read<int>("tokenA", stream, output0.TokenA, "\t\t");
				Read<int>("tokenB", stream, output0.TokenB, "\t\t");
				Read<unsigned long long>("machineHigh", stream, output0.MachineHigh, "\t\t");
				Read<unsigned long long>("machineLow", stream, output0.MachineLow, "\t\t");
			}

			if (stream.Succeeded())
			{
				PacketParsed<Client::ResponseKeyPacket>(output0);

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

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", stream, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				Read<int>("serverTick", stream, output0.ServerTick, "\t\t");

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", stream, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				unsigned short skillLevel_var4 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var4, "\t\t");

				output0.SkillLevel = (Enum::SkillLevel)skillLevel_var4;

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

					long long skillSn_var17 = 0;
					Read<long long>("skillSn", stream, skillSn_var17, "\t\t\t");

					output1.SkillSn = (Enum::SkillSn)skillSn_var17;

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

						long long skillAttack_var23 = 0;
						Read<long long>("skillAttack", stream, skillAttack_var23, "\t\t\t\t");

						projectile_array0.SkillAttack = (Enum::SkillAttackId)skillAttack_var23;

						int targetId_var24 = 0;
						Read<int>("targetId", stream, targetId_var24, "\t\t\t\t");

						projectile_array0.TargetId = (Enum::ActorId)targetId_var24;

						Read<unsigned char>("index", stream, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var26 = false;
						Read<bool>("moreTargets", stream, moreTargets_var26, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var26)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							long long skillAttack_var27 = 0;
							Read<long long>("skillAttack", stream, skillAttack_var27, "\t\t\t\t\t");

							nextTarget_array1.SkillAttack = (Enum::SkillAttackId)skillAttack_var27;

							int targetId_var28 = 0;
							Read<int>("targetId", stream, targetId_var28, "\t\t\t\t\t");

							nextTarget_array1.TargetId = (Enum::ActorId)targetId_var28;

							Read<unsigned char>("index", stream, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var30 = 0;
							Read<unsigned char>("unknown", stream, unknown_var30, "\t\t\t\t\t");

							Read<bool>("moreTargets", stream, moreTargets_var26, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

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

					long long skillSn_var31 = 0;
					Read<long long>("skillSn", stream, skillSn_var31, "\t\t\t");

					output2.SkillSn = (Enum::SkillSn)skillSn_var31;

					long long skillAttack_var32 = 0;
					Read<long long>("skillAttack", stream, skillAttack_var32, "\t\t\t");

					output2.SkillAttack = (Enum::SkillAttackId)skillAttack_var32;

					Read<Vector3S>("position", stream, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", stream, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", stream, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output2.AttackPoint, "\t\t\t");

					unsigned char count_var37 = 0;
					Read<unsigned char>("count", stream, count_var37, "\t\t\t");

					int unknown_var38 = 0;
					Read<int>("unknown", stream, unknown_var38, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var38, (int)0);

					output2.Hits.resize(count_var37);

					for (unsigned char i = 0; i < count_var37; ++i)
					{
						auto& hitActor_array2 = output2.Hits[i];

						int entityId_var39 = 0;
						Read<int>("entityId", stream, entityId_var39, "\t\t\t\t");

						hitActor_array2.EntityId = (Enum::ActorId)entityId_var39;

						unsigned char unknown_var40 = 0;
						Read<unsigned char>("unknown", stream, unknown_var40, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var40, (unsigned char)0);
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

					long long skillSn_var41 = 0;
					Read<long long>("skillSn", stream, skillSn_var41, "\t\t\t");

					output3.SkillSn = (Enum::SkillSn)skillSn_var41;

					Read<unsigned char>("attackPoint", stream, output3.AttackPoint, "\t\t\t");

					int unknown_var43 = 0;
					Read<int>("unknown", stream, unknown_var43, "\t\t\t");
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

				long long skillSn_var47 = 0;
				Read<long long>("skillSn", stream, skillSn_var47, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var47;

				unsigned int skillId_var48 = 0;
				Read<unsigned int>("skillId", stream, skillId_var48, "\t\t");

				output4.SkillId = (Enum::SkillId)skillId_var48;

				unsigned short skillLevel_var49 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var49, "\t\t");

				output4.SkillLevel = (Enum::SkillLevel)skillLevel_var49;

				Read<unsigned char>("motionPoint", stream, output4.MotionPoint, "\t\t");
				Read<Vector3S>("position", stream, output4.Position, "\t\t");

				Vector3S unknown_var52;
				Read<Vector3S>("unknown", stream, unknown_var52, "\t\t");
				Read<Vector3S>("rotation", stream, output4.Rotation, "\t\t");

				Vector3S unknown_var54;
				Read<Vector3S>("unknown", stream, unknown_var54, "\t\t");

				bool unknown_var55 = false;
				Read<bool>("unknown", stream, unknown_var55, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var55, (bool)0, (bool)1);

				int unknown_var56 = 0;
				Read<int>("unknown", stream, unknown_var56, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var56, (int)0);

				unsigned char unknown_var57 = 0;
				Read<unsigned char>("unknown", stream, unknown_var57, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var57, (unsigned char)0);

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillSyncPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				long long skillSn_var58 = 0;
				Read<long long>("skillSn", stream, skillSn_var58, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var58;

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

				long long skillSn_var60 = 0;
				Read<long long>("skillSn", stream, skillSn_var60, "\t\t");

				output6.SkillSn = (Enum::SkillSn)skillSn_var60;

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x22>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				Client::NpcTalkClosePacket output0;

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkClosePacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Client::NpcTalkBeginPacket output1;

				int objectId_var1 = 0;
				Read<int>("objectId", stream, objectId_var1, "\t\t");

				output1.ObjectId = (Enum::ActorId)objectId_var1;

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkBeginPacket>(output1);

					return;
				}
			}

			if (mode_var0 == 2)
			{
				Client::NpcTalkContinuePacket output2;

				Read<int>("index", stream, output2.Index, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkContinuePacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::NpcTalkEnchantUnknownPacket output3;

				short unknown_var3 = 0;
				Read<short>("unknown", stream, unknown_var3, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkEnchantUnknownPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Client::NpcTalkEnchantPacket output4;

				int npcId_var4 = 0;
				Read<int>("npcId", stream, npcId_var4, "\t\t");

				output4.NpcId = (Enum::NpcId)npcId_var4;

				int scriptId_var5 = 0;
				Read<int>("scriptId", stream, scriptId_var5, "\t\t");

				output4.ScriptId = (Enum::ScriptId)scriptId_var5;

				short eventType_var6 = 0;
				Read<short>("eventType", stream, eventType_var6, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", eventType_var6, (short)1, (short)202, (short)2, (short)3);

				output4.EventType = (Client::NpcTalkEnchantPacket::EventTypeEnum)eventType_var6;

				if (eventType_var6 == 1)
				{
					long long itemInstanceId_var7 = 0;
					Read<long long>("itemInstanceId", stream, itemInstanceId_var7, "\t\t\t");

					output4.ItemInstanceId = (Enum::ItemInstanceId)itemInstanceId_var7;
				}

				if (eventType_var6 == 202)
				{
					short unknown_var8 = 0;
					Read<short>("unknown", stream, unknown_var8, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkEnchantPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				Client::NpcTalkNextQuestPacket output5;

				int questId_var9 = 0;
				Read<int>("questId", stream, questId_var9, "\t\t");

				output5.QuestId = (Enum::QuestId)questId_var9;

				short eventType_var10 = 0;
				Read<short>("eventType", stream, eventType_var10, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", eventType_var10, (short)0, (short)2);

				output5.EventType = (Client::NpcTalkNextQuestPacket::EventTypeEnum)eventType_var10;

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkNextQuestPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 8)
			{
				Client::NpcTalkAllianceQuestAcceptPacket output6;

				Read<int>("index", stream, output6.Index, "\t\t");

				short eventType_var12 = 0;
				Read<short>("eventType", stream, eventType_var12, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", eventType_var12, (short)0, (short)2);

				output6.EventType = (Client::NpcTalkAllianceQuestAcceptPacket::EventTypeEnum)eventType_var12;

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(output6);

					return;
				}
			}

			if (mode_var0 == 9)
			{
				Client::NpcTalkAllianceQuestTalkPacket output7;

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(output7);

					return;
				}
			}

			if (mode_var0 == 11)
			{
				Client::NpcTalkCinematicPacket output8;

				Read<int>("objectId", stream, output8.Index, "\t\t");
				Read<int>("index", stream, output8.Index, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Client::NpcTalkCinematicPacket>(output8);

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

			long long accountId_var0 = 0;
			Read<long long>("accountId", stream, accountId_var0, "\t");

			output0.AccountId = (Enum::AccountId)accountId_var0;

			long long characterId_var1 = 0;
			Read<long long>("characterId", stream, characterId_var1, "\t");

			output0.CharacterId = (Enum::CharacterId)characterId_var1;

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

			int channelId_var7 = 0;
			Read<int>("channelId", stream, channelId_var7, "\t");

			output0.ChannelId = (Enum::ChannelId)channelId_var7;

			if (type_var5 == 3)
			{
				std::wstring unknown_var8;
				Read<std::wstring>("unknown", stream, unknown_var8, "\t\t");
			}

			if (type_var5 == 16)
			{
				int superChatId_var9 = 0;
				Read<int>("superChatId", stream, superChatId_var9, "\t\t");

				output0.SuperChatId = (Enum::SuperChatId)superChatId_var9;
			}

			if (type_var5 == 20)
			{
				long long clubId_var10 = 0;
				Read<long long>("clubId", stream, clubId_var10, "\t\t");

				output0.ClubId = (Enum::ClubId)clubId_var10;
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
		void ParsePacket<12, ServerPacket, 0x3e>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", stream, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				int casterId_var2 = 0;
				Read<int>("casterId", stream, casterId_var2, "\t\t");

				output0.CasterId = (Enum::ActorId)casterId_var2;

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", stream, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				if (skillId_var3 == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", stream, unknown_var4, "\t\t\t");
				}

				if (skillId_var3 != 0)
				{
					unsigned short skillLevel_var5 = 0;
					Read<unsigned short>("skillLevel", stream, skillLevel_var5, "\t\t\t");

					output0.SkillLevel = (Enum::SkillLevel)skillLevel_var5;

					Read<unsigned char>("motionPoint", stream, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output0.AttackPoint, "\t\t\t");

					Vector3Short position_var8;
					Read<Vector3Short>("position", stream, position_var8, "\t\t\t");

					output0.Position = (Vector3S)position_var8;

					Read<Vector3S>("direction", stream, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", stream, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					int serverTick_var11 = 0;
					Read<int>("serverTick", stream, serverTick_var11, "\t\t\t");

					unsigned char count_var12 = 0;
					Read<unsigned char>("count", stream, count_var12, "\t\t\t");

					output0.Hits.resize(count_var12);

					for (unsigned char i = 0; i < count_var12; ++i)
					{
						long long unknown_var13 = 0;
						Read<long long>("unknown", stream, unknown_var13, "\t\t\t\t");

						long long skillAttack_var14 = 0;
						Read<long long>("skillAttack", stream, skillAttack_var14, "\t\t\t\t");

						output0.Hits[i].SkillAttack = (Enum::SkillAttackId)skillAttack_var14;

						int targetId_var15 = 0;
						Read<int>("targetId", stream, targetId_var15, "\t\t\t\t");

						output0.Hits[i].TargetId = (Enum::ActorId)targetId_var15;

						Read<short>("animation", stream, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				long long skillSn_var17 = 0;
				Read<long long>("skillSn", stream, skillSn_var17, "\t\t");

				output1.SkillSn = (Enum::SkillSn)skillSn_var17;

				long long skillAttack_var18 = 0;
				Read<long long>("skillAttack", stream, skillAttack_var18, "\t\t");

				output1.SkillAttack = (Enum::SkillAttackId)skillAttack_var18;

				int casterId_var19 = 0;
				Read<int>("casterId", stream, casterId_var19, "\t\t");

				output1.CasterId = (Enum::ActorId)casterId_var19;

				unsigned int skillId_var20 = 0;
				Read<unsigned int>("skillId", stream, skillId_var20, "\t\t");

				output1.SkillId = (Enum::SkillId)skillId_var20;

				unsigned short skillLevel_var21 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var21, "\t\t");

				output1.SkillLevel = (Enum::SkillLevel)skillLevel_var21;

				Read<unsigned char>("motionPoint", stream, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", stream, output1.AttackPoint, "\t\t");

				Vector3Short position_var24;
				Read<Vector3Short>("position", stream, position_var24, "\t\t");

				output1.Position = (Vector3S)position_var24;

				Vector3Short direction_var25;
				Read<Vector3Short>("direction", stream, direction_var25, "\t\t");

				output1.Direction = (Vector3S)direction_var25;

				unsigned char count_var26 = 0;
				Read<unsigned char>("count", stream, count_var26, "\t\t");

				output1.DamagedTargets.resize(count_var26);

				for (unsigned char i = 0; i < count_var26; ++i)
				{
					int targetId_var27 = 0;
					Read<int>("targetId", stream, targetId_var27, "\t\t\t");

					output1.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var27;

					unsigned char damageCount_var28 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var28, "\t\t\t");

					output1.DamagedTargets[i].Damages.resize(damageCount_var28);

					for (unsigned char j = 0; j < damageCount_var28; ++j)
					{
						unsigned char hitType_var29 = 0;
						Read<unsigned char>("hitType", stream, hitType_var29, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var29, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output1.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var29;

						Read<long long>("damage", stream, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				int casterId_var31 = 0;
				Read<int>("casterId", stream, casterId_var31, "\t\t");

				output2.CasterId = (Enum::ActorId)casterId_var31;

				int targetId_var32 = 0;
				Read<int>("targetId", stream, targetId_var32, "\t\t");

				output2.TargetId = (Enum::ActorId)targetId_var32;

				Read<int>("serverTick", stream, output2.ServerTick, "\t\t");

				unsigned char hitType_var34 = 0;
				Read<unsigned char>("hitType", stream, hitType_var34, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", hitType_var34, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				output2.HitType = (Enum::HitType)hitType_var34;

				int damage_var35 = 0;
				Read<int>("damage", stream, damage_var35, "\t\t");

				output2.Damage = (long long)damage_var35;

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				int casterId_var36 = 0;
				Read<int>("casterId", stream, casterId_var36, "\t\t");

				output3.CasterId = (Enum::ActorId)casterId_var36;

				int targetId_var37 = 0;
				Read<int>("targetId", stream, targetId_var37, "\t\t");

				output3.TargetId = (Enum::ActorId)targetId_var37;

				Read<int>("serverTick", stream, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", stream, output3.HpAmount, "\t\t");
				Read<int>("spAmount", stream, output3.SpAmount, "\t\t");
				Read<int>("epAmount", stream, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", stream, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				long long skillSn_var43 = 0;
				Read<long long>("skillSn", stream, skillSn_var43, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var43;

				int casterId_var44 = 0;
				Read<int>("casterId", stream, casterId_var44, "\t\t");

				output4.CasterId = (Enum::ActorId)casterId_var44;

				int regionSkillObjectId_var45 = 0;
				Read<int>("regionSkillObjectId", stream, regionSkillObjectId_var45, "\t\t");

				output4.RegionSkillObjectId = (Enum::ActorId)regionSkillObjectId_var45;

				Read<unsigned char>("attackPoint", stream, output4.AttackPoint, "\t\t");

				unsigned char count_var47 = 0;
				Read<unsigned char>("count", stream, count_var47, "\t\t");

				output4.DamagedTargets.resize(count_var47);

				for (unsigned char i = 0; i < count_var47; ++i)
				{
					int targetId_var48 = 0;
					Read<int>("targetId", stream, targetId_var48, "\t\t\t");

					output4.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var48;

					unsigned char damageCount_var49 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var49, "\t\t\t");

					Vector3Short position_var50;
					Read<Vector3Short>("position", stream, position_var50, "\t\t\t");

					output4.DamagedTargets[i].Position = (Vector3S)position_var50;

					Read<Vector3S>("direction", stream, output4.DamagedTargets[i].Direction, "\t\t\t");

					output4.DamagedTargets[i].Damages.resize(damageCount_var49);

					for (unsigned char j = 0; j < damageCount_var49; ++j)
					{
						unsigned char hitType_var52 = 0;
						Read<unsigned char>("hitType", stream, hitType_var52, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var52, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output4.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var52;

						Read<long long>("damage", stream, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				long long skillSn_var54 = 0;
				Read<long long>("skillSn", stream, skillSn_var54, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var54;

				unsigned int skillId_var55 = 0;
				Read<unsigned int>("skillId", stream, skillId_var55, "\t\t");

				output5.SkillId = (Enum::SkillId)skillId_var55;

				unsigned short skillLevel_var56 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var56, "\t\t");

				output5.SkillLevel = (Enum::SkillLevel)skillLevel_var56;

				unsigned char count_var57 = 0;
				Read<unsigned char>("count", stream, count_var57, "\t\t");

				output5.DamagedTargets.resize(count_var57);

				for (unsigned char i = 0; i < count_var57; ++i)
				{
					int targetId_var58 = 0;
					Read<int>("targetId", stream, targetId_var58, "\t\t\t");

					output5.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var58;

					unsigned char damageCount_var59 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var59, "\t\t\t");

					Vector3Short position_var60;
					Read<Vector3Short>("position", stream, position_var60, "\t\t\t");

					output5.DamagedTargets[i].Position = (Vector3S)position_var60;

					Read<Vector3S>("direction", stream, output5.DamagedTargets[i].Direction, "\t\t\t");

					output5.DamagedTargets[i].Damages.resize(damageCount_var59);

					for (unsigned char j = 0; j < damageCount_var59; ++j)
					{
						unsigned char hitType_var62 = 0;
						Read<unsigned char>("hitType", stream, hitType_var62, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var62, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output5.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var62;

						Read<long long>("damage", stream, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var64 = 0;
				Read<int>("unknown", stream, unknown_var64, "\t\t");

				int count_var65 = 0;
				Read<int>("count", stream, count_var65, "\t\t");

				for (int i = 0; i < count_var65; ++i)
				{
					int unknown_var66 = 0;
					Read<int>("unknown", stream, unknown_var66, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var67 = 0;
				Read<long long>("skillSn", stream, skillSn_var67, "\t\t");

				bool hasTarget_var68 = false;
				Read<bool>("hasTarget", stream, hasTarget_var68, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var68, (bool)0, (bool)1);

				if (hasTarget_var68)
				{
					unsigned int skillId_var69 = 0;
					Read<unsigned int>("skillId", stream, skillId_var69, "\t\t\t");

					unsigned short skillLevel_var70 = 0;
					Read<unsigned short>("skillLevel", stream, skillLevel_var70, "\t\t\t");

					int unknown_var71 = 0;
					Read<int>("unknown", stream, unknown_var71, "\t\t\t");

					int npcId_var72 = 0;
					Read<int>("npcId", stream, npcId_var72, "\t\t\t");
				}
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

			int targetId_var1 = 0;
			Read<int>("targetId", stream, targetId_var1, "\t");

			output0.TargetId = (Enum::ActorId)targetId_var1;

			int instanceId_var2 = 0;
			Read<int>("instanceId", stream, instanceId_var2, "\t");

			output0.InstanceId = (Enum::EffectInstanceId)instanceId_var2;

			int sourceId_var3 = 0;
			Read<int>("sourceId", stream, sourceId_var3, "\t");

			output0.SourceId = (Enum::ActorId)sourceId_var3;

			if (instanceId_var2 != 0)
			{
				if (mode_var0 == 0)
				{
					Read<int>("startTime", stream, output0.StartTime, "\t\t\t");
					Read<int>("endTime", stream, output0.EndTime, "\t\t\t");

					int effectId_var6 = 0;
					Read<int>("effectId", stream, effectId_var6, "\t\t\t");

					output0.EffectId = (Enum::EffectId)effectId_var6;

					short effectLevel_var7 = 0;
					Read<short>("effectLevel", stream, effectLevel_var7, "\t\t\t");

					output0.EffectLevel = (Enum::EffectLevel)effectLevel_var7;

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

						int effectId_var14 = 0;
						Read<int>("effectId", stream, effectId_var14, "\t\t\t\t");

						output0.EffectId = (Enum::EffectId)effectId_var14;

						short effectLevel_var15 = 0;
						Read<short>("effectLevel", stream, effectLevel_var15, "\t\t\t\t");

						output0.EffectLevel = (Enum::EffectLevel)effectLevel_var15;

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
		void ParsePacket<12, ServerPacket, 0x5f>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::TrophyStartPacket output0;

				if (stream.Succeeded())
				{
					PacketParsed<Server::TrophyStartPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::TrophyContentPacket output1;

				int count_var1 = 0;
				Read<int>("count", stream, count_var1, "\t\t");

				output1.Trophies.resize(count_var1);

				for (int i = 0; i < count_var1; ++i)
				{
					int trophyId_var2 = 0;
					Read<int>("trophyId", stream, trophyId_var2, "\t\t\t");

					output1.Trophies[i].TrophyId = (Enum::TrophyId)trophyId_var2;

					int unknown_var3 = 0;
					Read<int>("unknown", stream, unknown_var3, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var3, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)9);

					unsigned char status_var4 = 0;
					Read<unsigned char>("status", stream, status_var4, "\t\t\t");

					ValidateValues(stream, "status", "\t\t\t", status_var4, (unsigned char)2, (unsigned char)3);

					output1.Trophies[i].Status = (Server::TrophyContentPacket::StatusEnum)status_var4;

					int isDone_var5 = 0;
					Read<int>("isDone", stream, isDone_var5, "\t\t\t");

					output1.Trophies[i].IsDone = (bool)isDone_var5;

					Read<int>("nextGrade", stream, output1.Trophies[i].NextGrade, "\t\t\t");
					Read<int>("lastReward", stream, output1.Trophies[i].LastReward, "\t\t\t");
					Read<bool>("isFavorited", stream, output1.Trophies[i].IsFavorited, "\t\t\t");

					ValidateValues(stream, "isFavorited", "\t\t\t", output1.Trophies[i].IsFavorited, (bool)0, (bool)1);

					long long counter_var9 = 0;
					Read<long long>("counter", stream, counter_var9, "\t\t\t");

					output1.Trophies[i].Counter = (int)counter_var9;

					int timestampsCount_var10 = 0;
					Read<int>("timestampsCount", stream, timestampsCount_var10, "\t\t\t");

					output1.Trophies[i].Timestamps.resize(timestampsCount_var10);

					for (int j = 0; j < timestampsCount_var10; ++j)
					{
						Read<int>("index", stream, output1.Trophies[i].Timestamps[j].Index, "\t\t\t\t");
						Read<long long>("timestamp", stream, output1.Trophies[i].Timestamps[j].Time, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::TrophyContentPacket>(output1);

					return;
				}
			}

			if (mode_var0 == 2)
			{
				Server::TrophyUpdatePacket output2;

				int trophyId_var13 = 0;
				Read<int>("trophyId", stream, trophyId_var13, "\t\t");

				output2.TrophyId = (Enum::TrophyId)trophyId_var13;

				unsigned char status_var14 = 0;
				Read<unsigned char>("status", stream, status_var14, "\t\t");

				ValidateValues(stream, "status", "\t\t", status_var14, (unsigned char)2, (unsigned char)3);

				output2.Status = (Server::TrophyUpdatePacket::StatusEnum)status_var14;

				int isDone_var15 = 0;
				Read<int>("isDone", stream, isDone_var15, "\t\t");

				output2.IsDone = (bool)isDone_var15;

				Read<int>("nextGrade", stream, output2.NextGrade, "\t\t");
				Read<int>("lastReward", stream, output2.LastReward, "\t\t");
				Read<bool>("isFavorited", stream, output2.IsFavorited, "\t\t");

				ValidateValues(stream, "isFavorited", "\t\t", output2.IsFavorited, (bool)0, (bool)1);

				long long counter_var19 = 0;
				Read<long long>("counter", stream, counter_var19, "\t\t");

				output2.Counter = (int)counter_var19;

				int timestampsCount_var20 = 0;
				Read<int>("timestampsCount", stream, timestampsCount_var20, "\t\t");

				output2.Timestamps.resize(timestampsCount_var20);

				for (int i = 0; i < timestampsCount_var20; ++i)
				{
					Read<int>("index", stream, output2.Timestamps[i].Index, "\t\t\t");
					Read<long long>("timestamp", stream, output2.Timestamps[i].Time, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::TrophyUpdatePacket>(output2);

					return;
				}
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x3d>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", stream, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				int casterId_var2 = 0;
				Read<int>("casterId", stream, casterId_var2, "\t\t");

				output0.CasterId = (Enum::ActorId)casterId_var2;

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", stream, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				if (skillId_var3 == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", stream, unknown_var4, "\t\t\t");
				}

				if (skillId_var3 != 0)
				{
					unsigned short skillLevel_var5 = 0;
					Read<unsigned short>("skillLevel", stream, skillLevel_var5, "\t\t\t");

					output0.SkillLevel = (Enum::SkillLevel)skillLevel_var5;

					Read<unsigned char>("motionPoint", stream, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output0.AttackPoint, "\t\t\t");

					short posX_var8 = 0;
					Read<short>("posX", stream, posX_var8, "\t\t\t");

					short posY_var9 = 0;
					Read<short>("posY", stream, posY_var9, "\t\t\t");

					short posZ_var10 = 0;
					Read<short>("posZ", stream, posZ_var10, "\t\t\t");
					Read<Vector3S>("direction", stream, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", stream, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					unsigned char count_var13 = 0;
					Read<unsigned char>("count", stream, count_var13, "\t\t\t");

					output0.Hits.resize(count_var13);

					for (unsigned char i = 0; i < count_var13; ++i)
					{
						long long hitId_var14 = 0;
						Read<long long>("hitId", stream, hitId_var14, "\t\t\t\t");

						int attackCount_var15 = 0;
						Read<int>("attackCount", stream, attackCount_var15, "\t\t\t\t");

						int casterId_var16 = 0;
						Read<int>("casterId", stream, casterId_var16, "\t\t\t\t");

						int targetId_var17 = 0;
						Read<int>("targetId", stream, targetId_var17, "\t\t\t\t");

						output0.Hits[i].TargetId = (Enum::ActorId)targetId_var17;

						Read<short>("animation", stream, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				long long skillSn_var19 = 0;
				Read<long long>("skillSn", stream, skillSn_var19, "\t\t");

				output1.SkillSn = (Enum::SkillSn)skillSn_var19;

				long long hitId_var20 = 0;
				Read<long long>("hitId", stream, hitId_var20, "\t\t");

				int casterId_var21 = 0;
				Read<int>("casterId", stream, casterId_var21, "\t\t");

				output1.CasterId = (Enum::ActorId)casterId_var21;

				unsigned int skillId_var22 = 0;
				Read<unsigned int>("skillId", stream, skillId_var22, "\t\t");

				output1.SkillId = (Enum::SkillId)skillId_var22;

				unsigned short skillLevel_var23 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var23, "\t\t");

				output1.SkillLevel = (Enum::SkillLevel)skillLevel_var23;

				Read<unsigned char>("motionPoint", stream, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", stream, output1.AttackPoint, "\t\t");

				short posX_var26 = 0;
				Read<short>("posX", stream, posX_var26, "\t\t");

				short posY_var27 = 0;
				Read<short>("posY", stream, posY_var27, "\t\t");

				short posZ_var28 = 0;
				Read<short>("posZ", stream, posZ_var28, "\t\t");

				short dirX_var29 = 0;
				Read<short>("dirX", stream, dirX_var29, "\t\t");

				short dirY_var30 = 0;
				Read<short>("dirY", stream, dirY_var30, "\t\t");

				short dirZ_var31 = 0;
				Read<short>("dirZ", stream, dirZ_var31, "\t\t");

				unsigned char count_var32 = 0;
				Read<unsigned char>("count", stream, count_var32, "\t\t");

				output1.DamagedTargets.resize(count_var32);

				for (unsigned char i = 0; i < count_var32; ++i)
				{
					int targetId_var33 = 0;
					Read<int>("targetId", stream, targetId_var33, "\t\t\t");

					output1.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var33;

					unsigned char damageCount_var34 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var34, "\t\t\t");

					output1.DamagedTargets[i].Damages.resize(damageCount_var34);

					for (unsigned char j = 0; j < damageCount_var34; ++j)
					{
						unsigned char hitType_var35 = 0;
						Read<unsigned char>("hitType", stream, hitType_var35, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var35, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output1.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var35;

						Read<long long>("damage", stream, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				int casterId_var37 = 0;
				Read<int>("casterId", stream, casterId_var37, "\t\t");

				output2.CasterId = (Enum::ActorId)casterId_var37;

				int targetId_var38 = 0;
				Read<int>("targetId", stream, targetId_var38, "\t\t");

				output2.TargetId = (Enum::ActorId)targetId_var38;

				Read<int>("serverTick", stream, output2.ServerTick, "\t\t");

				unsigned char hitType_var40 = 0;
				Read<unsigned char>("hitType", stream, hitType_var40, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", hitType_var40, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				output2.HitType = (Enum::HitType)hitType_var40;

				int damage_var41 = 0;
				Read<int>("damage", stream, damage_var41, "\t\t");

				output2.Damage = (long long)damage_var41;

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				int casterId_var42 = 0;
				Read<int>("casterId", stream, casterId_var42, "\t\t");

				output3.CasterId = (Enum::ActorId)casterId_var42;

				int targetId_var43 = 0;
				Read<int>("targetId", stream, targetId_var43, "\t\t");

				output3.TargetId = (Enum::ActorId)targetId_var43;

				Read<int>("serverTick", stream, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", stream, output3.HpAmount, "\t\t");
				Read<int>("spAmount", stream, output3.SpAmount, "\t\t");
				Read<int>("epAmount", stream, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", stream, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				long long skillSn_var49 = 0;
				Read<long long>("skillSn", stream, skillSn_var49, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var49;

				int casterId_var50 = 0;
				Read<int>("casterId", stream, casterId_var50, "\t\t");

				output4.CasterId = (Enum::ActorId)casterId_var50;

				int regionSkillObjectId_var51 = 0;
				Read<int>("regionSkillObjectId", stream, regionSkillObjectId_var51, "\t\t");

				output4.RegionSkillObjectId = (Enum::ActorId)regionSkillObjectId_var51;

				Read<unsigned char>("attackPoint", stream, output4.AttackPoint, "\t\t");

				unsigned char count_var53 = 0;
				Read<unsigned char>("count", stream, count_var53, "\t\t");

				output4.DamagedTargets.resize(count_var53);

				for (unsigned char i = 0; i < count_var53; ++i)
				{
					int targetId_var54 = 0;
					Read<int>("targetId", stream, targetId_var54, "\t\t\t");

					output4.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var54;

					unsigned char damageCount_var55 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var55, "\t\t\t");

					short posX_var56 = 0;
					Read<short>("posX", stream, posX_var56, "\t\t\t");

					short posY_var57 = 0;
					Read<short>("posY", stream, posY_var57, "\t\t\t");

					short posZ_var58 = 0;
					Read<short>("posZ", stream, posZ_var58, "\t\t\t");
					Read<Vector3S>("direction", stream, output4.DamagedTargets[i].Direction, "\t\t\t");

					output4.DamagedTargets[i].Damages.resize(damageCount_var55);

					for (unsigned char j = 0; j < damageCount_var55; ++j)
					{
						unsigned char hitType_var60 = 0;
						Read<unsigned char>("hitType", stream, hitType_var60, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var60, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output4.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var60;

						Read<long long>("damage", stream, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				long long skillSn_var62 = 0;
				Read<long long>("skillSn", stream, skillSn_var62, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var62;

				unsigned int skillId_var63 = 0;
				Read<unsigned int>("skillId", stream, skillId_var63, "\t\t");

				output5.SkillId = (Enum::SkillId)skillId_var63;

				unsigned short skillLevel_var64 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var64, "\t\t");

				output5.SkillLevel = (Enum::SkillLevel)skillLevel_var64;

				unsigned char count_var65 = 0;
				Read<unsigned char>("count", stream, count_var65, "\t\t");

				output5.DamagedTargets.resize(count_var65);

				for (unsigned char i = 0; i < count_var65; ++i)
				{
					int targetId_var66 = 0;
					Read<int>("targetId", stream, targetId_var66, "\t\t\t");

					output5.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var66;

					unsigned char damageCount_var67 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var67, "\t\t\t");

					short posX_var68 = 0;
					Read<short>("posX", stream, posX_var68, "\t\t\t");

					short posY_var69 = 0;
					Read<short>("posY", stream, posY_var69, "\t\t\t");

					short posZ_var70 = 0;
					Read<short>("posZ", stream, posZ_var70, "\t\t\t");
					Read<Vector3S>("direction", stream, output5.DamagedTargets[i].Direction, "\t\t\t");

					output5.DamagedTargets[i].Damages.resize(damageCount_var67);

					for (unsigned char j = 0; j < damageCount_var67; ++j)
					{
						unsigned char hitType_var72 = 0;
						Read<unsigned char>("hitType", stream, hitType_var72, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var72, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output5.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var72;

						Read<long long>("damage", stream, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var74 = 0;
				Read<int>("unknown", stream, unknown_var74, "\t\t");

				int count_var75 = 0;
				Read<int>("count", stream, count_var75, "\t\t");

				for (int i = 0; i < count_var75; ++i)
				{
					int unknown_var76 = 0;
					Read<int>("unknown", stream, unknown_var76, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var77 = 0;
				Read<long long>("skillSn", stream, skillSn_var77, "\t\t");

				bool hasTarget_var78 = false;
				Read<bool>("hasTarget", stream, hasTarget_var78, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var78, (bool)0, (bool)1);

				if (hasTarget_var78)
				{
					unsigned int skillId_var79 = 0;
					Read<unsigned int>("skillId", stream, skillId_var79, "\t\t\t");

					unsigned short skillLevel_var80 = 0;
					Read<unsigned short>("skillLevel", stream, skillLevel_var80, "\t\t\t");

					int unknown_var81 = 0;
					Read<int>("unknown", stream, unknown_var81, "\t\t\t");

					int npcId_var82 = 0;
					Read<int>("npcId", stream, npcId_var82, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<13, ClientPacket, 0x3>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			std::wstring auth1_var1;
			Read<std::wstring>("auth1", stream, auth1_var1, "\t");

			std::wstring auth2_var2;
			Read<std::wstring>("auth2", stream, auth2_var2, "\t");

			unsigned long long unknown_var3 = 0;
			Read<unsigned long long>("unknown", stream, unknown_var3, "\t");

			unsigned long long unknown_var4 = 0;
			Read<unsigned long long>("unknown", stream, unknown_var4, "\t");

			int unknown_var5 = 0;
			Read<int>("unknown", stream, unknown_var5, "\t");

			short unknown_var6 = 0;
			Read<short>("unknown", stream, unknown_var6, "\t");

			int unknown_var7 = 0;
			Read<int>("unknown", stream, unknown_var7, "\t");

			int unknown_var8 = 0;
			Read<int>("unknown", stream, unknown_var8, "\t");
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

			int targetActor_var1 = 0;
			Read<int>("targetActor", stream, targetActor_var1, "\t");

			int instanceId_var2 = 0;
			Read<int>("instanceId", stream, instanceId_var2, "\t");

			output0.InstanceId = (Enum::EffectInstanceId)instanceId_var2;

			int sourceActor_var3 = 0;
			Read<int>("sourceActor", stream, sourceActor_var3, "\t");

			if (mode_var0 == 0)
			{
				Read<int>("startTime", stream, output0.StartTime, "\t\t");
				Read<int>("endTime", stream, output0.EndTime, "\t\t");

				int effectId_var6 = 0;
				Read<int>("effectId", stream, effectId_var6, "\t\t");

				output0.EffectId = (Enum::EffectId)effectId_var6;

				short effectLevel_var7 = 0;
				Read<short>("effectLevel", stream, effectLevel_var7, "\t\t");

				output0.EffectLevel = (Enum::EffectLevel)effectLevel_var7;

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

					int effectId_var14 = 0;
					Read<int>("effectId", stream, effectId_var14, "\t\t\t");

					output0.EffectId = (Enum::EffectId)effectId_var14;

					short effectLevel_var15 = 0;
					Read<short>("effectLevel", stream, effectLevel_var15, "\t\t\t");

					output0.EffectLevel = (Enum::EffectLevel)effectLevel_var15;

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

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", stream, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				Read<int>("serverTick", stream, output0.ServerTick, "\t\t");

				int skillId_var3 = 0;
				Read<int>("skillId", stream, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				short skillLevel_var4 = 0;
				Read<short>("skillLevel", stream, skillLevel_var4, "\t\t");

				output0.SkillLevel = (Enum::SkillLevel)skillLevel_var4;

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

					long long skillSn_var18 = 0;
					Read<long long>("skillSn", stream, skillSn_var18, "\t\t\t");

					output1.SkillSn = (Enum::SkillSn)skillSn_var18;

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

						int attackCount_var24 = 0;
						Read<int>("attackCount", stream, attackCount_var24, "\t\t\t\t");

						int sourceId_var25 = 0;
						Read<int>("sourceId", stream, sourceId_var25, "\t\t\t\t");

						int targetId_var26 = 0;
						Read<int>("targetId", stream, targetId_var26, "\t\t\t\t");

						projectile_array0.TargetId = (Enum::ActorId)targetId_var26;

						Read<unsigned char>("index", stream, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var28 = false;
						Read<bool>("moreTargets", stream, moreTargets_var28, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var28, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var28)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							int attackCount_var29 = 0;
							Read<int>("attackCount", stream, attackCount_var29, "\t\t\t\t\t");

							int sourceId_var30 = 0;
							Read<int>("sourceId", stream, sourceId_var30, "\t\t\t\t\t");

							int targetId_var31 = 0;
							Read<int>("targetId", stream, targetId_var31, "\t\t\t\t\t");

							nextTarget_array1.TargetId = (Enum::ActorId)targetId_var31;

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

					long long skillSn_var34 = 0;
					Read<long long>("skillSn", stream, skillSn_var34, "\t\t\t");

					output2.SkillSn = (Enum::SkillSn)skillSn_var34;

					int attackCounter_var35 = 0;
					Read<int>("attackCounter", stream, attackCounter_var35, "\t\t\t");

					int sourceId_var36 = 0;
					Read<int>("sourceId", stream, sourceId_var36, "\t\t\t");
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

						int entityId_var43 = 0;
						Read<int>("entityId", stream, entityId_var43, "\t\t\t\t");

						hitActor_array2.EntityId = (Enum::ActorId)entityId_var43;

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

					long long skillSn_var45 = 0;
					Read<long long>("skillSn", stream, skillSn_var45, "\t\t\t");

					output3.SkillSn = (Enum::SkillSn)skillSn_var45;

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

				long long skillSn_var51 = 0;
				Read<long long>("skillSn", stream, skillSn_var51, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var51;

				int skillId_var52 = 0;
				Read<int>("skillId", stream, skillId_var52, "\t\t");

				output4.SkillId = (Enum::SkillId)skillId_var52;

				short skillLevel_var53 = 0;
				Read<short>("skillLevel", stream, skillLevel_var53, "\t\t");

				output4.SkillLevel = (Enum::SkillLevel)skillLevel_var53;

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

				long long skillSn_var62 = 0;
				Read<long long>("skillSn", stream, skillSn_var62, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var62;

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

				long long skillSn_var64 = 0;
				Read<long long>("skillSn", stream, skillSn_var64, "\t\t");

				output6.SkillSn = (Enum::SkillSn)skillSn_var64;

				if (stream.Succeeded())
				{
					PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

		template <>
		void ParsePacket<2503, ServerPacket, 0x3d>(ParserUtils::DataStream& stream)
		{
			using namespace ParserUtils::Packets;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", stream, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", stream, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				int casterId_var2 = 0;
				Read<int>("casterId", stream, casterId_var2, "\t\t");

				output0.CasterId = (Enum::ActorId)casterId_var2;

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", stream, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				if (skillId_var3 == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", stream, unknown_var4, "\t\t\t");
				}

				if (skillId_var3 != 0)
				{
					unsigned short skillLevel_var5 = 0;
					Read<unsigned short>("skillLevel", stream, skillLevel_var5, "\t\t\t");

					output0.SkillLevel = (Enum::SkillLevel)skillLevel_var5;

					Read<unsigned char>("motionPoint", stream, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", stream, output0.AttackPoint, "\t\t\t");

					short posX_var8 = 0;
					Read<short>("posX", stream, posX_var8, "\t\t\t");

					short posY_var9 = 0;
					Read<short>("posY", stream, posY_var9, "\t\t\t");

					short posZ_var10 = 0;
					Read<short>("posZ", stream, posZ_var10, "\t\t\t");
					Read<Vector3S>("direction", stream, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", stream, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					unsigned char count_var13 = 0;
					Read<unsigned char>("count", stream, count_var13, "\t\t\t");

					output0.Hits.resize(count_var13);

					for (unsigned char i = 0; i < count_var13; ++i)
					{
						long long hitId_var14 = 0;
						Read<long long>("hitId", stream, hitId_var14, "\t\t\t\t");

						int attackCount_var15 = 0;
						Read<int>("attackCount", stream, attackCount_var15, "\t\t\t\t");

						int casterId_var16 = 0;
						Read<int>("casterId", stream, casterId_var16, "\t\t\t\t");

						int targetId_var17 = 0;
						Read<int>("targetId", stream, targetId_var17, "\t\t\t\t");

						output0.Hits[i].TargetId = (Enum::ActorId)targetId_var17;

						Read<short>("animation", stream, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				long long skillSn_var19 = 0;
				Read<long long>("skillSn", stream, skillSn_var19, "\t\t");

				output1.SkillSn = (Enum::SkillSn)skillSn_var19;

				long long hitId_var20 = 0;
				Read<long long>("hitId", stream, hitId_var20, "\t\t");

				int casterId_var21 = 0;
				Read<int>("casterId", stream, casterId_var21, "\t\t");

				output1.CasterId = (Enum::ActorId)casterId_var21;

				unsigned int skillId_var22 = 0;
				Read<unsigned int>("skillId", stream, skillId_var22, "\t\t");

				output1.SkillId = (Enum::SkillId)skillId_var22;

				unsigned short skillLevel_var23 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var23, "\t\t");

				output1.SkillLevel = (Enum::SkillLevel)skillLevel_var23;

				Read<unsigned char>("motionPoint", stream, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", stream, output1.AttackPoint, "\t\t");

				short posX_var26 = 0;
				Read<short>("posX", stream, posX_var26, "\t\t");

				short posY_var27 = 0;
				Read<short>("posY", stream, posY_var27, "\t\t");

				short posZ_var28 = 0;
				Read<short>("posZ", stream, posZ_var28, "\t\t");

				short dirX_var29 = 0;
				Read<short>("dirX", stream, dirX_var29, "\t\t");

				short dirY_var30 = 0;
				Read<short>("dirY", stream, dirY_var30, "\t\t");

				short dirZ_var31 = 0;
				Read<short>("dirZ", stream, dirZ_var31, "\t\t");

				unsigned char count_var32 = 0;
				Read<unsigned char>("count", stream, count_var32, "\t\t");

				output1.DamagedTargets.resize(count_var32);

				for (unsigned char i = 0; i < count_var32; ++i)
				{
					int targetId_var33 = 0;
					Read<int>("targetId", stream, targetId_var33, "\t\t\t");

					output1.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var33;

					unsigned char damageCount_var34 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var34, "\t\t\t");

					output1.DamagedTargets[i].Damages.resize(damageCount_var34);

					for (unsigned char j = 0; j < damageCount_var34; ++j)
					{
						unsigned char hitType_var35 = 0;
						Read<unsigned char>("hitType", stream, hitType_var35, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var35, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output1.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var35;

						Read<long long>("damage", stream, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				int casterId_var37 = 0;
				Read<int>("casterId", stream, casterId_var37, "\t\t");

				output2.CasterId = (Enum::ActorId)casterId_var37;

				int targetId_var38 = 0;
				Read<int>("targetId", stream, targetId_var38, "\t\t");

				output2.TargetId = (Enum::ActorId)targetId_var38;

				Read<int>("serverTick", stream, output2.ServerTick, "\t\t");

				unsigned char hitType_var40 = 0;
				Read<unsigned char>("hitType", stream, hitType_var40, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", hitType_var40, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				output2.HitType = (Enum::HitType)hitType_var40;

				Read<long long>("damage", stream, output2.Damage, "\t\t");

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				int casterId_var42 = 0;
				Read<int>("casterId", stream, casterId_var42, "\t\t");

				output3.CasterId = (Enum::ActorId)casterId_var42;

				int targetId_var43 = 0;
				Read<int>("targetId", stream, targetId_var43, "\t\t");

				output3.TargetId = (Enum::ActorId)targetId_var43;

				Read<int>("serverTick", stream, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", stream, output3.HpAmount, "\t\t");
				Read<int>("spAmount", stream, output3.SpAmount, "\t\t");
				Read<int>("epAmount", stream, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", stream, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				long long skillSn_var49 = 0;
				Read<long long>("skillSn", stream, skillSn_var49, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var49;

				int casterId_var50 = 0;
				Read<int>("casterId", stream, casterId_var50, "\t\t");

				output4.CasterId = (Enum::ActorId)casterId_var50;

				int regionSkillObjectId_var51 = 0;
				Read<int>("regionSkillObjectId", stream, regionSkillObjectId_var51, "\t\t");

				output4.RegionSkillObjectId = (Enum::ActorId)regionSkillObjectId_var51;

				Read<unsigned char>("attackPoint", stream, output4.AttackPoint, "\t\t");

				unsigned char count_var53 = 0;
				Read<unsigned char>("count", stream, count_var53, "\t\t");

				output4.DamagedTargets.resize(count_var53);

				for (unsigned char i = 0; i < count_var53; ++i)
				{
					int targetId_var54 = 0;
					Read<int>("targetId", stream, targetId_var54, "\t\t\t");

					output4.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var54;

					unsigned char damageCount_var55 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var55, "\t\t\t");

					short posX_var56 = 0;
					Read<short>("posX", stream, posX_var56, "\t\t\t");

					short posY_var57 = 0;
					Read<short>("posY", stream, posY_var57, "\t\t\t");

					short posZ_var58 = 0;
					Read<short>("posZ", stream, posZ_var58, "\t\t\t");
					Read<Vector3S>("direction", stream, output4.DamagedTargets[i].Direction, "\t\t\t");

					output4.DamagedTargets[i].Damages.resize(damageCount_var55);

					for (unsigned char j = 0; j < damageCount_var55; ++j)
					{
						unsigned char hitType_var60 = 0;
						Read<unsigned char>("hitType", stream, hitType_var60, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var60, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output4.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var60;

						Read<long long>("damage", stream, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				long long skillSn_var62 = 0;
				Read<long long>("skillSn", stream, skillSn_var62, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var62;

				unsigned int skillId_var63 = 0;
				Read<unsigned int>("skillId", stream, skillId_var63, "\t\t");

				output5.SkillId = (Enum::SkillId)skillId_var63;

				unsigned short skillLevel_var64 = 0;
				Read<unsigned short>("skillLevel", stream, skillLevel_var64, "\t\t");

				output5.SkillLevel = (Enum::SkillLevel)skillLevel_var64;

				unsigned char count_var65 = 0;
				Read<unsigned char>("count", stream, count_var65, "\t\t");

				output5.DamagedTargets.resize(count_var65);

				for (unsigned char i = 0; i < count_var65; ++i)
				{
					int targetId_var66 = 0;
					Read<int>("targetId", stream, targetId_var66, "\t\t\t");

					output5.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var66;

					unsigned char damageCount_var67 = 0;
					Read<unsigned char>("damageCount", stream, damageCount_var67, "\t\t\t");

					short posX_var68 = 0;
					Read<short>("posX", stream, posX_var68, "\t\t\t");

					short posY_var69 = 0;
					Read<short>("posY", stream, posY_var69, "\t\t\t");

					short posZ_var70 = 0;
					Read<short>("posZ", stream, posZ_var70, "\t\t\t");
					Read<Vector3S>("direction", stream, output5.DamagedTargets[i].Direction, "\t\t\t");

					output5.DamagedTargets[i].Damages.resize(damageCount_var67);

					for (unsigned char j = 0; j < damageCount_var67; ++j)
					{
						unsigned char hitType_var72 = 0;
						Read<unsigned char>("hitType", stream, hitType_var72, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var72, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output5.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var72;

						Read<long long>("damage", stream, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var74 = 0;
				Read<int>("unknown", stream, unknown_var74, "\t\t");

				int count_var75 = 0;
				Read<int>("count", stream, count_var75, "\t\t");

				for (int i = 0; i < count_var75; ++i)
				{
					int unknown_var76 = 0;
					Read<int>("unknown", stream, unknown_var76, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var77 = 0;
				Read<long long>("skillSn", stream, skillSn_var77, "\t\t");

				bool hasTarget_var78 = false;
				Read<bool>("hasTarget", stream, hasTarget_var78, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var78, (bool)0, (bool)1);

				if (hasTarget_var78)
				{
					unsigned int skillId_var79 = 0;
					Read<unsigned int>("skillId", stream, skillId_var79, "\t\t\t");

					unsigned short skillLevel_var80 = 0;
					Read<unsigned short>("skillLevel", stream, skillLevel_var80, "\t\t\t");

					int unknown_var81 = 0;
					Read<int>("unknown", stream, unknown_var81, "\t\t\t");

					int npcId_var82 = 0;
					Read<int>("npcId", stream, npcId_var82, "\t\t\t");
				}
			}
		}

	}
}
