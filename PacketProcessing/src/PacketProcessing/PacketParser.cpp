#include "PacketParser.h"

#include <vector>

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		void ParsePacket(PacketHandler& handler, unsigned short version, bool isServer, unsigned short opcode)
		{
			static const std::vector<size_t> versionIndices = {
				1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5
			};
			static const std::vector<PacketVersionData> versions = {
				{
					0x7, 0x1,
					{
						{ "Reconnect7", &ParsePacket<12, ServerPacket, 0x7> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestFieldEnter", &ParsePacket<12, ServerPacket, 0x16> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldRemovePlayer", &ParsePacket<12, ServerPacket, 0x18> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "FieldAddItem", &ParsePacket<12, ServerPacket, 0x2b> },
						{ "FieldRemoveItem", &ParsePacket<12, ServerPacket, 0x2c> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "FieldAddNpc", &ParsePacket<12, ServerPacket, 0x56> },
						{ "FieldRemoveNpc", &ParsePacket<12, ServerPacket, 0x57> },
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
					0x7, 0x1,
					{
						{ "Reconnect7", &ParsePacket<12, ServerPacket, 0x7> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestFieldEnter", &ParsePacket<12, ServerPacket, 0x16> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldRemovePlayer", &ParsePacket<12, ServerPacket, 0x18> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "FieldAddItem", &ParsePacket<12, ServerPacket, 0x2b> },
						{ "FieldRemoveItem", &ParsePacket<12, ServerPacket, 0x2c> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "Buff", &ParsePacket<13, ServerPacket, 0x47> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldAddNpc", &ParsePacket<12, ServerPacket, 0x56> },
						{ "FieldRemoveNpc", &ParsePacket<12, ServerPacket, 0x57> },
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
					0x7, 0x1,
					{
						{ "Reconnect7", &ParsePacket<12, ServerPacket, 0x7> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestFieldEnter", &ParsePacket<12, ServerPacket, 0x16> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldRemovePlayer", &ParsePacket<12, ServerPacket, 0x18> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "FieldAddItem", &ParsePacket<12, ServerPacket, 0x2b> },
						{ "FieldRemoveItem", &ParsePacket<12, ServerPacket, 0x2c> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "Buff", &ParsePacket<13, ServerPacket, 0x47> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldAddNpc", &ParsePacket<12, ServerPacket, 0x56> },
						{ "FieldRemoveNpc", &ParsePacket<12, ServerPacket, 0x57> },
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
					0x7, 0x1,
					{
						{ "Reconnect7", &ParsePacket<12, ServerPacket, 0x7> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestFieldEnter", &ParsePacket<12, ServerPacket, 0x16> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldRemovePlayer", &ParsePacket<12, ServerPacket, 0x18> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "FieldAddItem", &ParsePacket<2486, ServerPacket, 0x2b> },
						{ "FieldRemoveItem", &ParsePacket<12, ServerPacket, 0x2c> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "Buff", &ParsePacket<13, ServerPacket, 0x47> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldAddNpc", &ParsePacket<12, ServerPacket, 0x56> },
						{ "FieldRemoveNpc", &ParsePacket<12, ServerPacket, 0x57> },
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
					0x7, 0x1,
					{
						{ "Reconnect7", &ParsePacket<12, ServerPacket, 0x7> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestFieldEnter", &ParsePacket<12, ServerPacket, 0x16> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldRemovePlayer", &ParsePacket<12, ServerPacket, 0x18> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "FieldAddItem", &ParsePacket<2497, ServerPacket, 0x2b> },
						{ "FieldRemoveItem", &ParsePacket<12, ServerPacket, 0x2c> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "Buff", &ParsePacket<13, ServerPacket, 0x47> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldAddNpc", &ParsePacket<12, ServerPacket, 0x56> },
						{ "FieldRemoveNpc", &ParsePacket<12, ServerPacket, 0x57> },
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
					0x7, 0x1,
					{
						{ "Reconnect7", &ParsePacket<12, ServerPacket, 0x7> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "RequestFieldEnter", &ParsePacket<12, ServerPacket, 0x16> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldRemovePlayer", &ParsePacket<12, ServerPacket, 0x18> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "FieldAddItem", &ParsePacket<2497, ServerPacket, 0x2b> },
						{ "FieldRemoveItem", &ParsePacket<12, ServerPacket, 0x2c> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
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
						{ "Buff", &ParsePacket<13, ServerPacket, 0x47> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "", &ParsePacket<0, false, 0> },
						{ "FieldAddNpc", &ParsePacket<12, ServerPacket, 0x56> },
						{ "FieldRemoveNpc", &ParsePacket<12, ServerPacket, 0x57> },
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

			size_t versionIndex = version == 12 ? 0 : versionIndices[std::min(39, std::max(version, (unsigned short)2464) - 2464)];
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

			opcodes[opcode - minOpcode].Callback(handler);
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x21>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0);

			if (mode_var0 == 0)
			{
				Client::StateSkillPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", handler, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				Read<unsigned int>("serverTick", handler, output0.ServerTick, "\t\t");

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", handler, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				unsigned short skillLevel_var4 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var4, "\t\t");

				ValidateValues(stream, "skillLevel", "\t\t", skillLevel_var4, (unsigned short)1);

				output0.SkillLevel = (Enum::SkillLevel)skillLevel_var4;

				Read<int>("animation", handler, output0.Animation, "\t\t");
				Read<int>("clientTick", handler, output0.ClientTick, "\t\t");

				long long unknown_var7 = 0;
				Read<long long>("unknown", handler, unknown_var7, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::StateSkillPacket>(output0);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x1>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::ResponseVersionPacket output0;

			Read<unsigned int>("version", handler, output0.Version, "\t");

			unsigned short feature_var1 = 0;
			Read<unsigned short>("feature", handler, feature_var1, "\t");

			unsigned short locale_var2 = 0;
			Read<unsigned short>("locale", handler, locale_var2, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::ResponseVersionPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xa>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::ResponseHeartbeatPacket output0;

			Read<int>("serverTick", handler, output0.ServerTick, "\t");
			Read<int>("clientTick", handler, output0.ClientTick, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::ResponseHeartbeatPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x2>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::HandshakePacket output0;

			Read<unsigned char>("function", handler, output0.Function, "\t");

			int count_var1 = 0;
			Read<int>("count", handler, count_var1, "\t");

			ResizeVector(handler, output0.Data, count_var1);

			for (int i = 0; i < count_var1 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				Read<std::wstring>("unknown", handler, output0.Data[i].String, "\t\t");

				long long unknown_var3 = 0;
				Read<long long>("unknown", handler, unknown_var3, "\t\t");
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::HandshakePacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			if (mode_var0 == 0)
			{
				Client::LogInPacket output0;

				Read<std::wstring>("username", handler, output0.Username, "\t\t");
				Read<std::wstring>("password", handler, output0.Password, "\t\t");

				short unknown_var3 = 0;
				Read<short>("unknown", handler, unknown_var3, "\t\t");
				Read<unsigned long long>("machineLow", handler, output0.MachineLow, "\t\t");
				Read<unsigned long long>("machineHigh", handler, output0.MachineHigh, "\t\t");

				int unknownMachineIdPtr_var6 = 0;
				Read<int>("unknownMachineIdPtr", handler, unknownMachineIdPtr_var6, "\t\t");
				Read<int>("sessionKey", handler, output0.SessionKey, "\t\t");
				Read<std::string>("locale", handler, output0.Locale, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::LogInPacket>(output0);

					return;
				}
			}

			if (mode_var0 != 0)
			{
				Client::LogInAuthTokenPacket output1;

				long long unknown_var9 = 0;
				Read<long long>("unknown", handler, unknown_var9, "\t\t");

				std::string authToken_var10;
				Read<std::string>("authToken", handler, authToken_var10, "\t\t");

				short unknown_var11 = 0;
				Read<short>("unknown", handler, unknown_var11, "\t\t");

				int unknown_var12 = 0;
				Read<int>("unknown", handler, unknown_var12, "\t\t");
				Read<unsigned long long>("machineLow", handler, output1.MachineLow, "\t\t");
				Read<unsigned long long>("machineHigh", handler, output1.MachineHigh, "\t\t");

				int unknown_var15 = 0;
				Read<int>("unknown", handler, unknown_var15, "\t\t");

				int unknown_var16 = 0;
				Read<int>("unknown", handler, unknown_var16, "\t\t");
				Read<std::string>("locale", handler, output1.Locale, "\t\t");

				unsigned char unknown_var18 = 0;
				Read<unsigned char>("unknown", handler, unknown_var18, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::LogInAuthTokenPacket>(output1);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x4>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::ResponseKeyPacket output0;

			long long accountId_var0 = 0;
			Read<long long>("accountId", handler, accountId_var0, "\t");

			output0.AccountId = (Enum::AccountId)accountId_var0;

			if (accountId_var0 != 0)
			{
				Read<int>("tokenA", handler, output0.TokenA, "\t\t");
				Read<int>("tokenB", handler, output0.TokenB, "\t\t");
				Read<unsigned long long>("machineHigh", handler, output0.MachineHigh, "\t\t");
				Read<unsigned long long>("machineLow", handler, output0.MachineLow, "\t\t");
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::ResponseKeyPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xd>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::RequestQuitPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1);

			output0.Mode = (Client::RequestQuitPacket::ModeEnum)mode_var0;

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::RequestQuitPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x20>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Client::SkillCastPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", handler, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				Read<int>("serverTick", handler, output0.ServerTick, "\t\t");

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", handler, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				unsigned short skillLevel_var4 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var4, "\t\t");

				output0.SkillLevel = (Enum::SkillLevel)skillLevel_var4;

				Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("direction", handler, output0.Direction, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");

				float unknown_var9 = 0;
				Read<float>("unknown", handler, unknown_var9, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var9, (float)0);

				Read<int>("clientTick", handler, output0.ClientTick, "\t\t");

				bool unknown_var11 = false;
				Read<bool>("unknown", handler, unknown_var11, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", handler, unknown_var12, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var12, (long long)0);

				bool flag_var13 = false;
				Read<bool>("flag", handler, flag_var13, "\t\t");

				ValidateValues(stream, "flag", "\t\t", flag_var13, (bool)0, (bool)1);

				output0.Flag = (bool)flag_var13;

				if (flag_var13)
				{
					int unknown_var14 = 0;
					Read<int>("unknown", handler, unknown_var14, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var14, (int)0);

					std::string unknown_var15;
					Read<std::string>("unknown", handler, unknown_var15, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				unsigned char damageMode_var16 = 0;
				Read<unsigned char>("damageMode", handler, damageMode_var16, "\t\t");

				ValidateValues(stream, "damageMode", "\t\t", damageMode_var16, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var16 == 0)
				{
					Client::SkillSyncDamagePacket output1;

					long long skillSn_var17 = 0;
					Read<long long>("skillSn", handler, skillSn_var17, "\t\t\t");

					output1.SkillSn = (Enum::SkillSn)skillSn_var17;

					Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t\t");
					Read<Vector3S>("position", handler, output1.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output1.Rotation, "\t\t\t");

					unsigned char count_var21 = 0;
					Read<unsigned char>("count", handler, count_var21, "\t\t\t");

					int unknown_var22 = 0;
					Read<int>("unknown", handler, unknown_var22, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var22, (int)0);

					ResizeVector(handler, output1.Projectiles, count_var21);

					for (unsigned char i = 0; i < count_var21 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& projectile_array0 = output1.Projectiles[i];

						long long skillAttack_var23 = 0;
						Read<long long>("skillAttack", handler, skillAttack_var23, "\t\t\t\t");

						projectile_array0.SkillAttack = (Enum::SkillAttackId)skillAttack_var23;

						int targetId_var24 = 0;
						Read<int>("targetId", handler, targetId_var24, "\t\t\t\t");

						projectile_array0.TargetId = (Enum::ActorId)targetId_var24;

						Read<unsigned char>("index", handler, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var26 = false;
						Read<bool>("moreTargets", handler, moreTargets_var26, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var26 && !handler.PacketStream.HasRecentlyFailed)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							long long skillAttack_var27 = 0;
							Read<long long>("skillAttack", handler, skillAttack_var27, "\t\t\t\t\t");

							nextTarget_array1.SkillAttack = (Enum::SkillAttackId)skillAttack_var27;

							int targetId_var28 = 0;
							Read<int>("targetId", handler, targetId_var28, "\t\t\t\t\t");

							nextTarget_array1.TargetId = (Enum::ActorId)targetId_var28;

							Read<unsigned char>("index", handler, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var30 = 0;
							Read<unsigned char>("unknown", handler, unknown_var30, "\t\t\t\t\t");

							Read<bool>("moreTargets", handler, moreTargets_var26, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var26, (bool)0, (bool)1);

							++j;
						}
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillSyncDamagePacket>(output1);

						return;
					}
				}

				if (damageMode_var16 == 1)
				{
					Client::SkillDamagePacket output2;

					long long skillSn_var31 = 0;
					Read<long long>("skillSn", handler, skillSn_var31, "\t\t\t");

					output2.SkillSn = (Enum::SkillSn)skillSn_var31;

					long long skillAttack_var32 = 0;
					Read<long long>("skillAttack", handler, skillAttack_var32, "\t\t\t");

					output2.SkillAttack = (Enum::SkillAttackId)skillAttack_var32;

					Read<Vector3S>("position", handler, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", handler, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", handler, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output2.AttackPoint, "\t\t\t");

					unsigned char count_var37 = 0;
					Read<unsigned char>("count", handler, count_var37, "\t\t\t");

					int unknown_var38 = 0;
					Read<int>("unknown", handler, unknown_var38, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var38, (int)0);

					ResizeVector(handler, output2.Hits, count_var37);

					for (unsigned char i = 0; i < count_var37 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& hitActor_array2 = output2.Hits[i];

						int entityId_var39 = 0;
						Read<int>("entityId", handler, entityId_var39, "\t\t\t\t");

						hitActor_array2.EntityId = (Enum::ActorId)entityId_var39;

						unsigned char unknown_var40 = 0;
						Read<unsigned char>("unknown", handler, unknown_var40, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var40, (unsigned char)0);
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);

						return;
					}
				}

				if (damageMode_var16 == 2)
				{
					Client::SkillRegionSkillPacket output3;

					long long skillSn_var41 = 0;
					Read<long long>("skillSn", handler, skillSn_var41, "\t\t\t");

					output3.SkillSn = (Enum::SkillSn)skillSn_var41;

					Read<unsigned char>("attackPoint", handler, output3.AttackPoint, "\t\t\t");

					int unknown_var43 = 0;
					Read<int>("unknown", handler, unknown_var43, "\t\t\t");
					Read<int>("attackCounter", handler, output3.AttackCounter, "\t\t\t");
					Read<Vector3S>("position", handler, output3.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output3.Rotation, "\t\t\t");

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);

						return;
					}
				}
			}

			if (mode_var0 == 2)
			{
				Client::SkillSyncPacket output4;

				long long skillSn_var47 = 0;
				Read<long long>("skillSn", handler, skillSn_var47, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var47;

				unsigned int skillId_var48 = 0;
				Read<unsigned int>("skillId", handler, skillId_var48, "\t\t");

				output4.SkillId = (Enum::SkillId)skillId_var48;

				unsigned short skillLevel_var49 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var49, "\t\t");

				output4.SkillLevel = (Enum::SkillLevel)skillLevel_var49;

				Read<unsigned char>("motionPoint", handler, output4.MotionPoint, "\t\t");
				Read<Vector3S>("position", handler, output4.Position, "\t\t");

				Vector3S unknown_var52;
				Read<Vector3S>("unknown", handler, unknown_var52, "\t\t");
				Read<Vector3S>("rotation", handler, output4.Rotation, "\t\t");

				Vector3S unknown_var54;
				Read<Vector3S>("unknown", handler, unknown_var54, "\t\t");

				bool unknown_var55 = false;
				Read<bool>("unknown", handler, unknown_var55, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var55, (bool)0, (bool)1);

				int unknown_var56 = 0;
				Read<int>("unknown", handler, unknown_var56, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var56, (int)0);

				unsigned char unknown_var57 = 0;
				Read<unsigned char>("unknown", handler, unknown_var57, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var57, (unsigned char)0);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				long long skillSn_var58 = 0;
				Read<long long>("skillSn", handler, skillSn_var58, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var58;

				Read<int>("serverTick", handler, output5.ServerTick, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				long long skillSn_var60 = 0;
				Read<long long>("skillSn", handler, skillSn_var60, "\t\t");

				output6.SkillSn = (Enum::SkillSn)skillSn_var60;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0x22>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)8, (unsigned char)0, (unsigned char)9, (unsigned char)1, (unsigned char)2, (unsigned char)4, (unsigned char)6, (unsigned char)7, (unsigned char)11);

			if (mode_var0 == 0)
			{
				Client::NpcTalkClosePacket output0;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkClosePacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Client::NpcTalkBeginPacket output1;

				int actorId_var1 = 0;
				Read<int>("actorId", handler, actorId_var1, "\t\t");

				output1.ActorId = (Enum::ActorId)actorId_var1;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkBeginPacket>(output1);

					return;
				}
			}

			if (mode_var0 == 2)
			{
				Client::NpcTalkContinuePacket output2;

				Read<int>("index", handler, output2.Index, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkContinuePacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::NpcTalkEnchantUnknownPacket output3;

				short unknown_var3 = 0;
				Read<short>("unknown", handler, unknown_var3, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantUnknownPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Client::NpcTalkEnchantPacket output4;

				int npcId_var4 = 0;
				Read<int>("npcId", handler, npcId_var4, "\t\t");

				output4.NpcId = (Enum::NpcId)npcId_var4;

				int scriptId_var5 = 0;
				Read<int>("scriptId", handler, scriptId_var5, "\t\t");

				output4.ScriptId = (Enum::ScriptId)scriptId_var5;

				short eventType_var6 = 0;
				Read<short>("eventType", handler, eventType_var6, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", eventType_var6, (short)1, (short)202, (short)2, (short)3);

				output4.EventType = (Client::NpcTalkEnchantPacket::EventTypeEnum)eventType_var6;

				if (eventType_var6 == 1)
				{
					long long itemInstanceId_var7 = 0;
					Read<long long>("itemInstanceId", handler, itemInstanceId_var7, "\t\t\t");

					output4.ItemInstanceId = (Enum::ItemInstanceId)itemInstanceId_var7;
				}

				if (eventType_var6 == 202)
				{
					short unknown_var8 = 0;
					Read<short>("unknown", handler, unknown_var8, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkEnchantPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				Client::NpcTalkNextQuestPacket output5;

				int questId_var9 = 0;
				Read<int>("questId", handler, questId_var9, "\t\t");

				output5.QuestId = (Enum::QuestId)questId_var9;

				short eventType_var10 = 0;
				Read<short>("eventType", handler, eventType_var10, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", eventType_var10, (short)0, (short)2);

				output5.EventType = (Client::NpcTalkNextQuestPacket::EventTypeEnum)eventType_var10;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkNextQuestPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 8)
			{
				Client::NpcTalkAllianceQuestAcceptPacket output6;

				Read<int>("index", handler, output6.Index, "\t\t");

				short eventType_var12 = 0;
				Read<short>("eventType", handler, eventType_var12, "\t\t");

				ValidateValues(stream, "eventType", "\t\t", eventType_var12, (short)0, (short)2);

				output6.EventType = (Client::NpcTalkAllianceQuestAcceptPacket::EventTypeEnum)eventType_var12;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(output6);

					return;
				}
			}

			if (mode_var0 == 9)
			{
				Client::NpcTalkAllianceQuestTalkPacket output7;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(output7);

					return;
				}
			}

			if (mode_var0 == 11)
			{
				Client::NpcTalkCinematicPacket output8;

				int actorId_var13 = 0;
				Read<int>("actorId", handler, actorId_var13, "\t\t");

				output8.ActorId = (Enum::ActorId)actorId_var13;

				Read<int>("index", handler, output8.Index, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::NpcTalkCinematicPacket>(output8);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ClientPacket, 0xb7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Client::SystemInfoPacket output0;

			Read<std::wstring>("info", handler, output0.Info, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Client::SystemInfoPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x7>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::Reconnect7Packet output0;

			int unknown_var0 = 0;
			Read<int>("unknown", handler, unknown_var0, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::Reconnect7Packet>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x3e>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", handler, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				int casterId_var2 = 0;
				Read<int>("casterId", handler, casterId_var2, "\t\t");

				output0.CasterId = (Enum::ActorId)casterId_var2;

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", handler, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				if (skillId_var3 == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", handler, unknown_var4, "\t\t\t");
				}

				if (skillId_var3 != 0)
				{
					unsigned short skillLevel_var5 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var5, "\t\t\t");

					output0.SkillLevel = (Enum::SkillLevel)skillLevel_var5;

					Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t\t");

					Vector3Short position_var8;
					Read<Vector3Short>("position", handler, position_var8, "\t\t\t");

					output0.Position = (Vector3S)position_var8;

					Read<Vector3S>("direction", handler, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", handler, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					int serverTick_var11 = 0;
					Read<int>("serverTick", handler, serverTick_var11, "\t\t\t");

					unsigned char count_var12 = 0;
					Read<unsigned char>("count", handler, count_var12, "\t\t\t");

					ResizeVector(handler, output0.Hits, count_var12);

					for (unsigned char i = 0; i < count_var12 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						long long unknown_var13 = 0;
						Read<long long>("unknown", handler, unknown_var13, "\t\t\t\t");

						long long skillAttack_var14 = 0;
						Read<long long>("skillAttack", handler, skillAttack_var14, "\t\t\t\t");

						output0.Hits[i].SkillAttack = (Enum::SkillAttackId)skillAttack_var14;

						int targetId_var15 = 0;
						Read<int>("targetId", handler, targetId_var15, "\t\t\t\t");

						output0.Hits[i].TargetId = (Enum::ActorId)targetId_var15;

						Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				long long skillSn_var17 = 0;
				Read<long long>("skillSn", handler, skillSn_var17, "\t\t");

				output1.SkillSn = (Enum::SkillSn)skillSn_var17;

				long long skillAttack_var18 = 0;
				Read<long long>("skillAttack", handler, skillAttack_var18, "\t\t");

				output1.SkillAttack = (Enum::SkillAttackId)skillAttack_var18;

				int casterId_var19 = 0;
				Read<int>("casterId", handler, casterId_var19, "\t\t");

				output1.CasterId = (Enum::ActorId)casterId_var19;

				unsigned int skillId_var20 = 0;
				Read<unsigned int>("skillId", handler, skillId_var20, "\t\t");

				output1.SkillId = (Enum::SkillId)skillId_var20;

				unsigned short skillLevel_var21 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var21, "\t\t");

				output1.SkillLevel = (Enum::SkillLevel)skillLevel_var21;

				Read<unsigned char>("motionPoint", handler, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t");

				Vector3Short position_var24;
				Read<Vector3Short>("position", handler, position_var24, "\t\t");

				output1.Position = (Vector3S)position_var24;

				Vector3Short direction_var25;
				Read<Vector3Short>("direction", handler, direction_var25, "\t\t");

				output1.Direction = (Vector3S)direction_var25;

				unsigned char count_var26 = 0;
				Read<unsigned char>("count", handler, count_var26, "\t\t");

				ResizeVector(handler, output1.DamagedTargets, count_var26);

				for (unsigned char i = 0; i < count_var26 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var27 = 0;
					Read<int>("targetId", handler, targetId_var27, "\t\t\t");

					output1.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var27;

					unsigned char damageCount_var28 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var28, "\t\t\t");

					ResizeVector(handler, output1.DamagedTargets[i].Damages, damageCount_var28);

					for (unsigned char j = 0; j < damageCount_var28 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var29 = 0;
						Read<unsigned char>("hitType", handler, hitType_var29, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var29, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output1.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var29;

						Read<long long>("damage", handler, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				int casterId_var31 = 0;
				Read<int>("casterId", handler, casterId_var31, "\t\t");

				output2.CasterId = (Enum::ActorId)casterId_var31;

				int targetId_var32 = 0;
				Read<int>("targetId", handler, targetId_var32, "\t\t");

				output2.TargetId = (Enum::ActorId)targetId_var32;

				Read<int>("serverTick", handler, output2.ServerTick, "\t\t");

				unsigned char hitType_var34 = 0;
				Read<unsigned char>("hitType", handler, hitType_var34, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", hitType_var34, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				output2.HitType = (Enum::HitType)hitType_var34;

				int damage_var35 = 0;
				Read<int>("damage", handler, damage_var35, "\t\t");

				output2.Damage = (long long)damage_var35;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				int casterId_var36 = 0;
				Read<int>("casterId", handler, casterId_var36, "\t\t");

				output3.CasterId = (Enum::ActorId)casterId_var36;

				int targetId_var37 = 0;
				Read<int>("targetId", handler, targetId_var37, "\t\t");

				output3.TargetId = (Enum::ActorId)targetId_var37;

				Read<int>("serverTick", handler, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", handler, output3.HpAmount, "\t\t");
				Read<int>("spAmount", handler, output3.SpAmount, "\t\t");
				Read<int>("epAmount", handler, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", handler, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				long long skillSn_var43 = 0;
				Read<long long>("skillSn", handler, skillSn_var43, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var43;

				int casterId_var44 = 0;
				Read<int>("casterId", handler, casterId_var44, "\t\t");

				output4.CasterId = (Enum::ActorId)casterId_var44;

				int regionSkillObjectId_var45 = 0;
				Read<int>("regionSkillObjectId", handler, regionSkillObjectId_var45, "\t\t");

				output4.RegionSkillObjectId = (Enum::ActorId)regionSkillObjectId_var45;

				Read<unsigned char>("attackPoint", handler, output4.AttackPoint, "\t\t");

				unsigned char count_var47 = 0;
				Read<unsigned char>("count", handler, count_var47, "\t\t");

				ResizeVector(handler, output4.DamagedTargets, count_var47);

				for (unsigned char i = 0; i < count_var47 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var48 = 0;
					Read<int>("targetId", handler, targetId_var48, "\t\t\t");

					output4.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var48;

					unsigned char damageCount_var49 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var49, "\t\t\t");

					Vector3Short position_var50;
					Read<Vector3Short>("position", handler, position_var50, "\t\t\t");

					output4.DamagedTargets[i].Position = (Vector3S)position_var50;

					Read<Vector3S>("direction", handler, output4.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output4.DamagedTargets[i].Damages, damageCount_var49);

					for (unsigned char j = 0; j < damageCount_var49 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var52 = 0;
						Read<unsigned char>("hitType", handler, hitType_var52, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var52, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output4.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var52;

						Read<long long>("damage", handler, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				long long skillSn_var54 = 0;
				Read<long long>("skillSn", handler, skillSn_var54, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var54;

				unsigned int skillId_var55 = 0;
				Read<unsigned int>("skillId", handler, skillId_var55, "\t\t");

				output5.SkillId = (Enum::SkillId)skillId_var55;

				unsigned short skillLevel_var56 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var56, "\t\t");

				output5.SkillLevel = (Enum::SkillLevel)skillLevel_var56;

				unsigned char count_var57 = 0;
				Read<unsigned char>("count", handler, count_var57, "\t\t");

				ResizeVector(handler, output5.DamagedTargets, count_var57);

				for (unsigned char i = 0; i < count_var57 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var58 = 0;
					Read<int>("targetId", handler, targetId_var58, "\t\t\t");

					output5.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var58;

					unsigned char damageCount_var59 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var59, "\t\t\t");

					Vector3Short position_var60;
					Read<Vector3Short>("position", handler, position_var60, "\t\t\t");

					output5.DamagedTargets[i].Position = (Vector3S)position_var60;

					Read<Vector3S>("direction", handler, output5.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output5.DamagedTargets[i].Damages, damageCount_var59);

					for (unsigned char j = 0; j < damageCount_var59 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var62 = 0;
						Read<unsigned char>("hitType", handler, hitType_var62, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var62, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output5.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var62;

						Read<long long>("damage", handler, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var64 = 0;
				Read<int>("unknown", handler, unknown_var64, "\t\t");

				int count_var65 = 0;
				Read<int>("count", handler, count_var65, "\t\t");

				for (int i = 0; i < count_var65 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int unknown_var66 = 0;
					Read<int>("unknown", handler, unknown_var66, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var67 = 0;
				Read<long long>("skillSn", handler, skillSn_var67, "\t\t");

				bool hasTarget_var68 = false;
				Read<bool>("hasTarget", handler, hasTarget_var68, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var68, (bool)0, (bool)1);

				if (hasTarget_var68)
				{
					unsigned int skillId_var69 = 0;
					Read<unsigned int>("skillId", handler, skillId_var69, "\t\t\t");

					unsigned short skillLevel_var70 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var70, "\t\t\t");

					int unknown_var71 = 0;
					Read<int>("unknown", handler, unknown_var71, "\t\t\t");

					int npcId_var72 = 0;
					Read<int>("npcId", handler, npcId_var72, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x56>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddNpc output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0, "\t");

			output0.ActorId = (Enum::ActorId)actorId_var0;

			int npcId_var1 = 0;
			Read<int>("npcId", handler, npcId_var1, "\t");

			output0.NpcId = (Enum::NpcId)npcId_var1;

			Read<Vector3S>("position", handler, output0.Position, "\t");
			Read<Vector3S>("rotation", handler, output0.Rotation, "\t");

			bool isBoss_var4 = false;

			isBoss_var4 = handler.IsNpcBoss(npcId_var1);

			ValidateValues(stream, "isBoss", "\t", isBoss_var4, (bool)0, (bool)1);

			if (isBoss_var4)
			{
				Read<std::string>("kfmName", handler, output0.KfmName, "\t\t");
			}

			unsigned char defaultStatsMode_var6 = 0;
			Read<unsigned char>("defaultStatsMode", handler, defaultStatsMode_var6, "\t");

			ValidateValues(stream, "defaultStatsMode", "\t", defaultStatsMode_var6, (unsigned char)35);

			if (defaultStatsMode_var6 == 35)
			{
				Read<unsigned long long>("hpMax", handler, output0.Hp.Max, "\t\t");
				Read<unsigned int>("moveSpeedMax", handler, output0.MoveSpeed.Max, "\t\t");
				Read<unsigned long long>("hpBase", handler, output0.Hp.Base, "\t\t");
				Read<unsigned int>("moveSpeedBase", handler, output0.MoveSpeed.Base, "\t\t");
				Read<unsigned long long>("hpCurrent", handler, output0.Hp.Current, "\t\t");
				Read<unsigned int>("moveSpeedCurrent", handler, output0.MoveSpeed.Current, "\t\t");
			}
			Read<bool>("isDead", handler, output0.IsDead, "\t");

			ValidateValues(stream, "isDead", "\t", output0.IsDead, (bool)0, (bool)1);

			unsigned short effectCount_var14 = 0;
			Read<unsigned short>("effectCount", handler, effectCount_var14, "\t");

			ResizeVector(handler, output0.AdditionalEffects, effectCount_var14);

			for (unsigned short i = 0; i < effectCount_var14 && !handler.PacketStream.HasRecentlyFailed; ++i)
			{
				int ownerId_var15 = 0;
				Read<int>("ownerId", handler, ownerId_var15, "\t\t");

				output0.AdditionalEffects[i].OwnerId = (Enum::ActorId)ownerId_var15;

				int buffInstanceId_var16 = 0;
				Read<int>("buffInstanceId", handler, buffInstanceId_var16, "\t\t");

				int casterId_var17 = 0;
				Read<int>("casterId", handler, casterId_var17, "\t\t");

				output0.AdditionalEffects[i].CasterId = (Enum::ActorId)casterId_var17;

				Read<int>("startTick", handler, output0.AdditionalEffects[i].StartTick, "\t\t");
				Read<int>("endTick", handler, output0.AdditionalEffects[i].EndTick, "\t\t");

				int effectId_var20 = 0;
				Read<int>("effectId", handler, effectId_var20, "\t\t");

				output0.AdditionalEffects[i].EffectId = (Enum::EffectId)effectId_var20;

				short effectLevel_var21 = 0;
				Read<short>("effectLevel", handler, effectLevel_var21, "\t\t");

				output0.AdditionalEffects[i].EffectLevel = (Enum::EffectLevel)effectLevel_var21;

				Read<int>("stacks", handler, output0.AdditionalEffects[i].Stacks, "\t\t");
				Read<bool>("enabled", handler, output0.AdditionalEffects[i].Enabled, "\t\t");

				ValidateValues(stream, "enabled", "\t\t", output0.AdditionalEffects[i].Enabled, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.AdditionalEffects[i].ShieldHealth, "\t\t");
			}

			long long petItemInstanceId_var25 = 0;
			Read<long long>("petItemInstanceId", handler, petItemInstanceId_var25, "\t");

			unsigned char unknown_var26 = 0;
			Read<unsigned char>("unknown", handler, unknown_var26, "\t");

			short level_var27 = 0;
			Read<short>("level", handler, level_var27, "\t");

			output0.Level = (unsigned short)level_var27;

			short unknownLevelPad_var28 = 0;
			Read<short>("unknownLevelPad", handler, unknownLevelPad_var28, "\t");

			ValidateValues(stream, "unknownLevelPad", "\t", unknownLevelPad_var28, (short)0);

			int unknown_var29 = 0;
			Read<int>("unknown", handler, unknown_var29, "\t");

			if (isBoss_var4)
			{
				Read<std::wstring>("spawnEffect", handler, output0.SpawnEffect, "\t\t");

				int skillCount_var31 = 0;
				Read<int>("skillCount", handler, skillCount_var31, "\t\t");

				ResizeVector(handler, output0.Skills, skillCount_var31);

				for (int i = 0; i < skillCount_var31 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int skillId_var32 = 0;
					Read<int>("skillId", handler, skillId_var32, "\t\t\t");

					output0.Skills[i].SkillId = (Enum::SkillId)skillId_var32;

					short skillLevel_var33 = 0;
					Read<short>("skillLevel", handler, skillLevel_var33, "\t\t\t");

					output0.Skills[i].SkillLevel = (Enum::SkillLevel)skillLevel_var33;
				}

				int unknown_var34 = 0;
				Read<int>("unknown", handler, unknown_var34, "\t\t");
			}

			bool hasHiddenHp_var35 = false;

			hasHiddenHp_var35 = handler.NpcHasHiddenHp(npcId_var1);

			ValidateValues(stream, "hasHiddenHp", "\t", hasHiddenHp_var35, (bool)0, (bool)1);

			if (hasHiddenHp_var35)
			{
				Read<long long>("hiddenHpAdd", handler, output0.HiddenHpAdd, "\t\t");
			}

			bool unknownBool_var37 = false;
			Read<bool>("unknownBool", handler, unknownBool_var37, "\t");

			ValidateValues(stream, "unknownBool", "\t", unknownBool_var37, (bool)0, (bool)1);

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddNpc>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x16>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char message_var0 = 0;
			Read<unsigned char>("message", handler, message_var0, "\t");

			ValidateValues(stream, "message", "\t", message_var0, (unsigned char)0);

			if (message_var0 == 0)
			{
				Server::RequestFieldEnterPacket output0;

				int mapId_var1 = 0;
				Read<int>("mapId", handler, mapId_var1, "\t\t");

				output0.MapId = (Enum::MapId)mapId_var1;

				unsigned char unknown_var2 = 0;
				Read<unsigned char>("unknown", handler, unknown_var2, "\t\t");

				unsigned char unknown_var3 = 0;
				Read<unsigned char>("unknown", handler, unknown_var3, "\t\t");

				int unknown_var4 = 0;
				Read<int>("unknown", handler, unknown_var4, "\t\t");

				int unknown_var5 = 0;
				Read<int>("unknown", handler, unknown_var5, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");

				int unknown_var8 = 0;
				Read<int>("unknown", handler, unknown_var8, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::RequestFieldEnterPacket>(output0);

					return;
				}
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x48>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::BuffPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			output0.Mode = (Server::BuffPacket::ModeEnum)mode_var0;

			int targetId_var1 = 0;
			Read<int>("targetId", handler, targetId_var1, "\t");

			output0.TargetId = (Enum::ActorId)targetId_var1;

			int instanceId_var2 = 0;
			Read<int>("instanceId", handler, instanceId_var2, "\t");

			output0.InstanceId = (Enum::EffectInstanceId)instanceId_var2;

			int sourceId_var3 = 0;
			Read<int>("sourceId", handler, sourceId_var3, "\t");

			output0.SourceId = (Enum::ActorId)sourceId_var3;

			if (instanceId_var2 != 0)
			{
				if (mode_var0 == 0)
				{
					Read<int>("startTime", handler, output0.StartTime, "\t\t\t");
					Read<int>("endTime", handler, output0.EndTime, "\t\t\t");

					int effectId_var6 = 0;
					Read<int>("effectId", handler, effectId_var6, "\t\t\t");

					output0.EffectId = (Enum::EffectId)effectId_var6;

					short effectLevel_var7 = 0;
					Read<short>("effectLevel", handler, effectLevel_var7, "\t\t\t");

					output0.EffectLevel = (Enum::EffectLevel)effectLevel_var7;

					Read<int>("stacks", handler, output0.Stacks, "\t\t\t");
					Read<bool>("hasShield", handler, output0.UpdateShield, "\t\t\t");

					ValidateValues(stream, "hasShield", "\t\t\t", output0.UpdateShield, (bool)0, (bool)1);

					Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t\t");
				}

				if (mode_var0 == 2)
				{
					int flags_var11 = 0;
					Read<int>("flags", handler, flags_var11, "\t\t\t");

					output0.UpdateEffect = GetBit(flags_var11, 0);
					output0.UpdateShield = GetBit(flags_var11, 1);

					if (GetBit(flags_var11, 0) == 1)
					{
						Read<int>("startTime", handler, output0.StartTime, "\t\t\t\t");
						Read<int>("endTime", handler, output0.EndTime, "\t\t\t\t");

						int effectId_var14 = 0;
						Read<int>("effectId", handler, effectId_var14, "\t\t\t\t");

						output0.EffectId = (Enum::EffectId)effectId_var14;

						short effectLevel_var15 = 0;
						Read<short>("effectLevel", handler, effectLevel_var15, "\t\t\t\t");

						output0.EffectLevel = (Enum::EffectLevel)effectLevel_var15;

						Read<int>("stacks", handler, output0.Stacks, "\t\t\t\t");
						Read<bool>("enabled", handler, output0.Enabled, "\t\t\t\t");

						ValidateValues(stream, "enabled", "\t\t\t\t", output0.Enabled, (bool)0, (bool)1);
					}

					if (GetBit(flags_var11, 1) == 1)
					{
						Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t\t\t");
					}
				}
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::BuffPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x18>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldRemovePlayerPacket output0;

			int characterId_var0 = 0;
			Read<int>("characterId", handler, characterId_var0, "\t");

			output0.CharacterId = (Enum::CharacterId)characterId_var0;

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemovePlayerPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x1d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::UserChatPacket output0;

			long long accountId_var0 = 0;
			Read<long long>("accountId", handler, accountId_var0, "\t");

			output0.AccountId = (Enum::AccountId)accountId_var0;

			long long characterId_var1 = 0;
			Read<long long>("characterId", handler, characterId_var1, "\t");

			output0.CharacterId = (Enum::CharacterId)characterId_var1;

			Read<std::wstring>("characterName", handler, output0.CharacterName, "\t");

			unsigned char unknown_var3 = 0;
			Read<unsigned char>("unknown", handler, unknown_var3, "\t");
			Read<std::wstring>("message", handler, output0.Message, "\t");

			int type_var5 = 0;
			Read<int>("type", handler, type_var5, "\t");

			ValidateValues(stream, "type", "\t", type_var5, (int)8, (int)0, (int)3, (int)4, (int)5, (int)6, (int)7, (int)9, (int)11, (int)12, (int)13, (int)14, (int)15, (int)16, (int)18, (int)19, (int)20, (int)23);

			output0.Type = (Server::UserChatPacket::TypeEnum)type_var5;

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t");

			int channelId_var7 = 0;
			Read<int>("channelId", handler, channelId_var7, "\t");

			output0.ChannelId = (Enum::ChannelId)channelId_var7;

			if (type_var5 == 3)
			{
				std::wstring unknown_var8;
				Read<std::wstring>("unknown", handler, unknown_var8, "\t\t");
			}

			if (type_var5 == 16)
			{
				int superChatId_var9 = 0;
				Read<int>("superChatId", handler, superChatId_var9, "\t\t");

				output0.SuperChatId = (Enum::SuperChatId)superChatId_var9;
			}

			if (type_var5 == 20)
			{
				long long clubId_var10 = 0;
				Read<long long>("clubId", handler, clubId_var10, "\t\t");

				output0.ClubId = (Enum::ClubId)clubId_var10;
			}

			unsigned char unknown_var11 = 0;
			Read<unsigned char>("unknown", handler, unknown_var11, "\t");

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::UserChatPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddItemPacket output0;

			int objectId_var0 = 0;
			Read<int>("objectId", handler, objectId_var0, "\t");

			output0.ObjectId = (Enum::ItemEntityId)objectId_var0;

			int itemId_var1 = 0;
			Read<int>("itemId", handler, itemId_var1, "\t");

			output0.ItemId = (Enum::ItemId)itemId_var1;

			int amount_var2 = 0;
			Read<int>("amount", handler, amount_var2, "\t");

			output0.Amount = (unsigned int)amount_var2;

			bool hasUid_var3 = false;
			Read<bool>("hasUid", handler, hasUid_var3, "\t");

			ValidateValues(stream, "hasUid", "\t", hasUid_var3, (bool)0, (bool)1);

			if (hasUid_var3)
			{
				long long uid_var4 = 0;
				Read<long long>("uid", handler, uid_var4, "\t\t");
			}
			Read<Vector3S>("position", handler, output0.Position, "\t");

			int ownerId_var6 = 0;
			Read<int>("ownerId", handler, ownerId_var6, "\t");

			output0.OwnerId = (Enum::CharacterId)ownerId_var6;

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7, "\t");

			unsigned char unknown_var8 = 0;
			Read<unsigned char>("unknown", handler, unknown_var8, "\t");

			int rarity_var9 = 0;
			Read<int>("rarity", handler, rarity_var9, "\t");

			ValidateValues(stream, "rarity", "\t", rarity_var9, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			output0.Rarity = (Enum::Rarity)rarity_var9;

			short unknown_var10 = 0;
			Read<short>("unknown", handler, unknown_var10, "\t");

			bool unknown_var11 = false;
			Read<bool>("unknown", handler, unknown_var11, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var11, (bool)0, (bool)1);

			bool unknown_var12 = false;
			Read<bool>("unknown", handler, unknown_var12, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var12, (bool)0, (bool)1);

			if (itemId_var1 < 90000001 || itemId_var1 > 90000003)
			{

				{
					int amount_var13 = 0;
					Read<int>("amount", handler, amount_var13, "\t\t\t");

					output0.ItemData.Amount = (unsigned int)amount_var13;

					int unknown_var14 = 0;
					Read<int>("unknown", handler, unknown_var14, "\t\t\t");

					int unknown_var15 = 0;
					Read<int>("unknown", handler, unknown_var15, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var15, (int)18446744073709551615);

					long long creationTime_var16 = 0;
					Read<long long>("creationTime", handler, creationTime_var16, "\t\t\t");

					output0.ItemData.CreationTime = (unsigned long long)creationTime_var16;

					long long expirationTime_var17 = 0;
					Read<long long>("expirationTime", handler, expirationTime_var17, "\t\t\t");

					output0.ItemData.ExpirationTime = (unsigned long long)expirationTime_var17;

					long long unknown_var18 = 0;
					Read<long long>("unknown", handler, unknown_var18, "\t\t\t");

					int timesChanged_var19 = 0;
					Read<int>("timesChanged", handler, timesChanged_var19, "\t\t\t");

					output0.ItemData.TimesChanged = (unsigned int)timesChanged_var19;

					int remainingUses_var20 = 0;
					Read<int>("remainingUses", handler, remainingUses_var20, "\t\t\t");

					output0.ItemData.RemainingUses = (unsigned int)remainingUses_var20;

					bool isLocked_var21 = false;
					Read<bool>("isLocked", handler, isLocked_var21, "\t\t\t");

					ValidateValues(stream, "isLocked", "\t\t\t", isLocked_var21, (bool)0, (bool)1);

					output0.ItemData.IsLocked = (bool)isLocked_var21;

					long long unlockTime_var22 = 0;
					Read<long long>("unlockTime", handler, unlockTime_var22, "\t\t\t");

					output0.ItemData.UnlockTime = (bool)unlockTime_var22;

					short glamorForges_var23 = 0;
					Read<short>("glamorForges", handler, glamorForges_var23, "\t\t\t");

					output0.ItemData.GlamorForges = (bool)glamorForges_var23;

					unsigned char unknownBool_var24 = 0;
					Read<unsigned char>("unknownBool", handler, unknownBool_var24, "\t\t\t");

					ValidateValues(stream, "unknownBool", "\t\t\t", unknownBool_var24, (unsigned char)0);

					int unknown_var25 = 0;
					Read<int>("unknown", handler, unknown_var25, "\t\t\t");

					{

						{

							Color4I_BGRA dyeColorPrimary_var26;
							Read<Color4I_BGRA>("dyeColorPrimary", handler, dyeColorPrimary_var26, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Primary = (Color4I)dyeColorPrimary_var26;

							Color4I_BGRA dyeColorSecondary_var27;
							Read<Color4I_BGRA>("dyeColorSecondary", handler, dyeColorSecondary_var27, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Secondary = (Color4I)dyeColorSecondary_var27;

							Color4I_BGRA dyeColorTertiary_var28;
							Read<Color4I_BGRA>("dyeColorTertiary", handler, dyeColorTertiary_var28, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Tertiary = (Color4I)dyeColorTertiary_var28;

							int dyeColorIndex_var29 = 0;
							Read<int>("dyeColorIndex", handler, dyeColorIndex_var29, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Index = (unsigned int)dyeColorIndex_var29;

							int unknown_var30 = 0;
							Read<int>("unknown", handler, unknown_var30, "\t\t\t\t\t");
						}

						short itemCategory_var31 = 0;

						itemCategory_var31 = handler.GetItemCategory(itemId_var1);

						if (itemCategory_var31 == 113)
						{

							{
								Read<Vector3S>("position1", handler, output0.ItemData.Customization.Cap.Position1, "\t\t\t\t\t\t");
								Read<Vector3S>("position2", handler, output0.ItemData.Customization.Cap.Position2, "\t\t\t\t\t\t");
								Read<Vector3S>("position3", handler, output0.ItemData.Customization.Cap.Position3, "\t\t\t\t\t\t");
								Read<Vector3S>("position4", handler, output0.ItemData.Customization.Cap.Position4, "\t\t\t\t\t\t");

								float unknown_var36 = 0;
								Read<float>("unknown", handler, unknown_var36, "\t\t\t\t\t\t");
							}
						}

						if (itemCategory_var31 == 102)
						{

							{
								Read<float>("backLength", handler, output0.ItemData.Customization.Hair.BackLength, "\t\t\t\t\t\t");
								Read<Vector3S>("backPosition1", handler, output0.ItemData.Customization.Hair.BackPosition1, "\t\t\t\t\t\t");
								Read<Vector3S>("backPosition2", handler, output0.ItemData.Customization.Hair.BackPosition2, "\t\t\t\t\t\t");
								Read<float>("frontLength", handler, output0.ItemData.Customization.Hair.FrontLength, "\t\t\t\t\t\t");
								Read<Vector3S>("frontPosition1", handler, output0.ItemData.Customization.Hair.FrontPosition1, "\t\t\t\t\t\t");
								Read<Vector3S>("frontPosition2", handler, output0.ItemData.Customization.Hair.FrontPosition2, "\t\t\t\t\t\t");
							}
						}

						if (itemCategory_var31 == 104)
						{

							{
								Read<Vector3S>("position1", handler, output0.ItemData.Customization.Decal.Position1, "\t\t\t\t\t\t");
								Read<Vector3S>("position2", handler, output0.ItemData.Customization.Decal.Position2, "\t\t\t\t\t\t");
								Read<Vector3S>("position3", handler, output0.ItemData.Customization.Decal.Position3, "\t\t\t\t\t\t");
								Read<Vector3S>("position4", handler, output0.ItemData.Customization.Decal.Position4, "\t\t\t\t\t\t");
							}
						}
					}

					{

						unsigned char unknown_var47 = 0;
						Read<unsigned char>("unknown", handler, unknown_var47, "\t\t\t\t");

						{

							short statCount_var48 = 0;
							Read<short>("statCount", handler, statCount_var48, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Constant.Basic, statCount_var48);

							for (short i = 0; i < statCount_var48 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var49 = 0;
								Read<short>("type", handler, type_var49, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Constant.Basic[i].Type = (Enum::StatAttributeBasic)type_var49;

								Read<int>("value", handler, output0.ItemData.Stats.Constant.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Constant.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var48, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Constant.Special, statCount_var48);

							for (short i = 0; i < statCount_var48 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var52 = 0;
								Read<short>("type", handler, type_var52, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Constant.Special[i].Type = (Enum::StatAttributeSpecial)type_var52;

								Read<float>("value", handler, output0.ItemData.Stats.Constant.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Constant.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var55 = 0;
						Read<int>("unknown", handler, unknown_var55, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var55, (int)0);

						{

							short statCount_var56 = 0;
							Read<short>("statCount", handler, statCount_var56, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Static.Basic, statCount_var56);

							for (short i = 0; i < statCount_var56 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var57 = 0;
								Read<short>("type", handler, type_var57, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Static.Basic[i].Type = (Enum::StatAttributeBasic)type_var57;

								Read<int>("value", handler, output0.ItemData.Stats.Static.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Static.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var56, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Static.Special, statCount_var56);

							for (short i = 0; i < statCount_var56 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var60 = 0;
								Read<short>("type", handler, type_var60, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Static.Special[i].Type = (Enum::StatAttributeSpecial)type_var60;

								Read<float>("value", handler, output0.ItemData.Stats.Static.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Static.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var63 = 0;
						Read<int>("unknown", handler, unknown_var63, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var63, (int)0);

						{

							short statCount_var64 = 0;
							Read<short>("statCount", handler, statCount_var64, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Random.Basic, statCount_var64);

							for (short i = 0; i < statCount_var64 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var65 = 0;
								Read<short>("type", handler, type_var65, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Random.Basic[i].Type = (Enum::StatAttributeBasic)type_var65;

								Read<int>("value", handler, output0.ItemData.Stats.Random.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Random.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var64, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Random.Special, statCount_var64);

							for (short i = 0; i < statCount_var64 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var68 = 0;
								Read<short>("type", handler, type_var68, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Random.Special[i].Type = (Enum::StatAttributeSpecial)type_var68;

								Read<float>("value", handler, output0.ItemData.Stats.Random.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Random.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var71 = 0;
						Read<int>("unknown", handler, unknown_var71, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var71, (int)0);

						{

							short statCount_var72 = 0;
							Read<short>("statCount", handler, statCount_var72, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Title.Basic, statCount_var72);

							for (short i = 0; i < statCount_var72 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var73 = 0;
								Read<short>("type", handler, type_var73, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Title.Basic[i].Type = (Enum::StatAttributeBasic)type_var73;

								Read<int>("value", handler, output0.ItemData.Stats.Title.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Title.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var72, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Title.Special, statCount_var72);

							for (short i = 0; i < statCount_var72 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var76 = 0;
								Read<short>("type", handler, type_var76, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Title.Special[i].Type = (Enum::StatAttributeSpecial)type_var76;

								Read<float>("value", handler, output0.ItemData.Stats.Title.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Title.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var79 = 0;
						Read<int>("unknown", handler, unknown_var79, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var79, (int)0);

						{

							short statCount_var80 = 0;
							Read<short>("statCount", handler, statCount_var80, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment1.Basic, statCount_var80);

							for (short i = 0; i < statCount_var80 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var81 = 0;
								Read<short>("type", handler, type_var81, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment1.Basic[i].Type = (Enum::StatAttributeBasic)type_var81;

								Read<int>("value", handler, output0.ItemData.Stats.Empowerment1.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment1.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var80, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment1.Special, statCount_var80);

							for (short i = 0; i < statCount_var80 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var84 = 0;
								Read<short>("type", handler, type_var84, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment1.Special[i].Type = (Enum::StatAttributeSpecial)type_var84;

								Read<float>("value", handler, output0.ItemData.Stats.Empowerment1.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment1.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var87 = 0;
						Read<int>("unknown", handler, unknown_var87, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var87, (int)0);

						{

							short statCount_var88 = 0;
							Read<short>("statCount", handler, statCount_var88, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment2.Basic, statCount_var88);

							for (short i = 0; i < statCount_var88 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var89 = 0;
								Read<short>("type", handler, type_var89, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment2.Basic[i].Type = (Enum::StatAttributeBasic)type_var89;

								Read<int>("value", handler, output0.ItemData.Stats.Empowerment2.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment2.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var88, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment2.Special, statCount_var88);

							for (short i = 0; i < statCount_var88 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var92 = 0;
								Read<short>("type", handler, type_var92, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment2.Special[i].Type = (Enum::StatAttributeSpecial)type_var92;

								Read<float>("value", handler, output0.ItemData.Stats.Empowerment2.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment2.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var95 = 0;
						Read<int>("unknown", handler, unknown_var95, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var95, (int)0);

						{

							short statCount_var96 = 0;
							Read<short>("statCount", handler, statCount_var96, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment3.Basic, statCount_var96);

							for (short i = 0; i < statCount_var96 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var97 = 0;
								Read<short>("type", handler, type_var97, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment3.Basic[i].Type = (Enum::StatAttributeBasic)type_var97;

								Read<int>("value", handler, output0.ItemData.Stats.Empowerment3.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment3.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var96, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment3.Special, statCount_var96);

							for (short i = 0; i < statCount_var96 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var100 = 0;
								Read<short>("type", handler, type_var100, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment3.Special[i].Type = (Enum::StatAttributeSpecial)type_var100;

								Read<float>("value", handler, output0.ItemData.Stats.Empowerment3.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment3.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var103 = 0;
						Read<int>("unknown", handler, unknown_var103, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var103, (int)0);

						{

							short statCount_var104 = 0;
							Read<short>("statCount", handler, statCount_var104, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment4.Basic, statCount_var104);

							for (short i = 0; i < statCount_var104 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var105 = 0;
								Read<short>("type", handler, type_var105, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment4.Basic[i].Type = (Enum::StatAttributeBasic)type_var105;

								Read<int>("value", handler, output0.ItemData.Stats.Empowerment4.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment4.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var104, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment4.Special, statCount_var104);

							for (short i = 0; i < statCount_var104 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var108 = 0;
								Read<short>("type", handler, type_var108, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment4.Special[i].Type = (Enum::StatAttributeSpecial)type_var108;

								Read<float>("value", handler, output0.ItemData.Stats.Empowerment4.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment4.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var111 = 0;
						Read<int>("unknown", handler, unknown_var111, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var111, (int)0);

						{

							short statCount_var112 = 0;
							Read<short>("statCount", handler, statCount_var112, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment5.Basic, statCount_var112);

							for (short i = 0; i < statCount_var112 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var113 = 0;
								Read<short>("type", handler, type_var113, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment5.Basic[i].Type = (Enum::StatAttributeBasic)type_var113;

								Read<int>("value", handler, output0.ItemData.Stats.Empowerment5.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment5.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var112, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Empowerment5.Special, statCount_var112);

							for (short i = 0; i < statCount_var112 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var116 = 0;
								Read<short>("type", handler, type_var116, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Empowerment5.Special[i].Type = (Enum::StatAttributeSpecial)type_var116;

								Read<float>("value", handler, output0.ItemData.Stats.Empowerment5.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Empowerment5.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var119 = 0;
						Read<int>("unknown", handler, unknown_var119, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var119, (int)0);
					}

					{

						int enchantLevel_var120 = 0;
						Read<int>("enchantLevel", handler, enchantLevel_var120, "\t\t\t\t");

						output0.ItemData.Enchantment.Level = (unsigned int)enchantLevel_var120;

						int enchantExp_var121 = 0;
						Read<int>("enchantExp", handler, enchantExp_var121, "\t\t\t\t");

						output0.ItemData.Enchantment.EnchantExp = (unsigned int)enchantExp_var121;

						Read<unsigned char>("enchantCharges", handler, output0.ItemData.Enchantment.EnchantCharges, "\t\t\t\t");

						long long unknown_var123 = 0;
						Read<long long>("unknown", handler, unknown_var123, "\t\t\t\t");

						int unknown_var124 = 0;
						Read<int>("unknown", handler, unknown_var124, "\t\t\t\t");

						int unknown_var125 = 0;
						Read<int>("unknown", handler, unknown_var125, "\t\t\t\t");
						Read<bool>("canRepackage", handler, output0.ItemData.Enchantment.CanRepackage, "\t\t\t\t");

						ValidateValues(stream, "canRepackage", "\t\t\t\t", output0.ItemData.Enchantment.CanRepackage, (bool)0, (bool)1);

						int charges_var127 = 0;
						Read<int>("charges", handler, charges_var127, "\t\t\t\t");

						output0.ItemData.Enchantment.Charges = (unsigned int)charges_var127;

						unsigned char basicStatCount_var128 = 0;
						Read<unsigned char>("basicStatCount", handler, basicStatCount_var128, "\t\t\t\t");

						ResizeVector(handler, output0.ItemData.Enchantment.Basic, basicStatCount_var128);

						for (unsigned char i = 0; i < basicStatCount_var128 && !handler.PacketStream.HasRecentlyFailed; ++i)
						{
							int type_var129 = 0;
							Read<int>("type", handler, type_var129, "\t\t\t\t\t");

							output0.ItemData.Enchantment.Basic[i].Type = (Enum::StatAttributeBasic)type_var129;

							Read<int>("value", handler, output0.ItemData.Enchantment.Basic[i].Value, "\t\t\t\t\t");
							Read<float>("rate", handler, output0.ItemData.Enchantment.Basic[i].Rate, "\t\t\t\t\t");
						}
					}

					{

						int limitBreakLevel_var132 = 0;
						Read<int>("limitBreakLevel", handler, limitBreakLevel_var132, "\t\t\t\t");

						output0.ItemData.LimitBreak.Level = (unsigned int)limitBreakLevel_var132;

						{

							int statCount_var133 = 0;
							Read<int>("statCount", handler, statCount_var133, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.LimitBreak.Stats.Basic, statCount_var133);

							for (int i = 0; i < statCount_var133 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var134 = 0;
								Read<short>("type", handler, type_var134, "\t\t\t\t\t\t");

								output0.ItemData.LimitBreak.Stats.Basic[i].Type = (Enum::StatAttributeBasic)type_var134;

								Read<int>("value", handler, output0.ItemData.LimitBreak.Stats.Basic[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.LimitBreak.Stats.Basic[i].Rate, "\t\t\t\t\t\t");
							}

							Read<int>("statCount", handler, statCount_var133, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.LimitBreak.Stats.Special, statCount_var133);

							for (int i = 0; i < statCount_var133 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var137 = 0;
								Read<short>("type", handler, type_var137, "\t\t\t\t\t\t");

								output0.ItemData.LimitBreak.Stats.Special[i].Type = (Enum::StatAttributeSpecial)type_var137;

								Read<float>("value", handler, output0.ItemData.LimitBreak.Stats.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.LimitBreak.Stats.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}
					}

					unsigned char extraDataType_var140 = 0;

					extraDataType_var140 = handler.GetItemExtraDataType(itemId_var1);

					ValidateValues(stream, "extraDataType", "\t\t\t", extraDataType_var140, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					if (extraDataType_var140 == 1)
					{

						{
							long long unknown_var141 = 0;
							Read<long long>("unknown", handler, unknown_var141, "\t\t\t\t\t");
							Read<std::wstring>("fileName", handler, output0.ItemData.Template.FileName, "\t\t\t\t\t");
							Read<std::wstring>("name", handler, output0.ItemData.Template.Name, "\t\t\t\t\t");

							unsigned char unknown_var144 = 0;
							Read<unsigned char>("unknown", handler, unknown_var144, "\t\t\t\t\t");

							int unknown_var145 = 0;
							Read<int>("unknown", handler, unknown_var145, "\t\t\t\t\t");

							long long accountId_var146 = 0;
							Read<long long>("accountId", handler, accountId_var146, "\t\t\t\t\t");

							output0.ItemData.Template.AccountId = (Enum::AccountId)accountId_var146;

							long long characterId_var147 = 0;
							Read<long long>("characterId", handler, characterId_var147, "\t\t\t\t\t");

							output0.ItemData.Template.CharacterId = (Enum::CharacterId)characterId_var147;

							Read<std::wstring>("author", handler, output0.ItemData.Template.Author, "\t\t\t\t\t");

							long long creationTime_var149 = 0;
							Read<long long>("creationTime", handler, creationTime_var149, "\t\t\t\t\t");

							output0.ItemData.Template.CreationTime = (unsigned long long)creationTime_var149;

							Read<std::wstring>("url", handler, output0.ItemData.Template.Url, "\t\t\t\t\t");

							unsigned char unknown_var151 = 0;
							Read<unsigned char>("unknown", handler, unknown_var151, "\t\t\t\t\t");
						}

						{

							long long unknown_var152 = 0;
							Read<long long>("unknown", handler, unknown_var152, "\t\t\t\t\t");

							int unknown_var153 = 0;
							Read<int>("unknown", handler, unknown_var153, "\t\t\t\t\t");

							int unknown_var154 = 0;
							Read<int>("unknown", handler, unknown_var154, "\t\t\t\t\t");

							int unknown_var155 = 0;
							Read<int>("unknown", handler, unknown_var155, "\t\t\t\t\t");

							long long unknown_var156 = 0;
							Read<long long>("unknown", handler, unknown_var156, "\t\t\t\t\t");

							int unknown_var157 = 0;
							Read<int>("unknown", handler, unknown_var157, "\t\t\t\t\t");

							long long unknown_var158 = 0;
							Read<long long>("unknown", handler, unknown_var158, "\t\t\t\t\t");

							long long unknown_var159 = 0;
							Read<long long>("unknown", handler, unknown_var159, "\t\t\t\t\t");

							std::wstring unknown_var160;
							Read<std::wstring>("unknown", handler, unknown_var160, "\t\t\t\t\t");
						}
					}

					if (extraDataType_var140 == 2)
					{

						{
							Read<std::wstring>("name", handler, output0.ItemData.Pet.Name, "\t\t\t\t\t");

							long long exp_var162 = 0;
							Read<long long>("exp", handler, exp_var162, "\t\t\t\t\t");

							output0.ItemData.Pet.Exp = (unsigned long long)exp_var162;

							int evolvePoints_var163 = 0;
							Read<int>("evolvePoints", handler, evolvePoints_var163, "\t\t\t\t\t");

							output0.ItemData.Pet.EvolvePoints = (unsigned int)evolvePoints_var163;

							int level_var164 = 0;
							Read<int>("level", handler, level_var164, "\t\t\t\t\t");

							output0.ItemData.Pet.Level = (unsigned int)level_var164;

							Read<bool>("hasItems", handler, output0.ItemData.Pet.HasItems, "\t\t\t\t\t");

							ValidateValues(stream, "hasItems", "\t\t\t\t\t", output0.ItemData.Pet.HasItems, (bool)0, (bool)1);
						}
					}

					if (extraDataType_var140 == 3)
					{

						{
							int length_var166 = 0;
							Read<int>("length", handler, length_var166, "\t\t\t\t\t");

							output0.ItemData.Music.Length = (unsigned int)length_var166;

							int instrument_var167 = 0;
							Read<int>("instrument", handler, instrument_var167, "\t\t\t\t\t");

							output0.ItemData.Music.Instrument = (unsigned int)instrument_var167;

							Read<std::wstring>("title", handler, output0.ItemData.Music.Title, "\t\t\t\t\t");
							Read<std::wstring>("author", handler, output0.ItemData.Music.Author, "\t\t\t\t\t");

							int unknown_var170 = 0;
							Read<int>("unknown", handler, unknown_var170, "\t\t\t\t\t");

							ValidateValues(stream, "unknown", "\t\t\t\t\t", unknown_var170, (int)1);

							long long authorId_var171 = 0;
							Read<long long>("authorId", handler, authorId_var171, "\t\t\t\t\t");

							output0.ItemData.Music.AuthorId = (Enum::CharacterId)authorId_var171;

							Read<bool>("isLocked", handler, output0.ItemData.Music.IsLocked, "\t\t\t\t\t");

							ValidateValues(stream, "isLocked", "\t\t\t\t\t", output0.ItemData.Music.IsLocked, (bool)0, (bool)1);

							long long unknown_var173 = 0;
							Read<long long>("unknown", handler, unknown_var173, "\t\t\t\t\t");

							long long unknown_var174 = 0;
							Read<long long>("unknown", handler, unknown_var174, "\t\t\t\t\t");
						}
					}

					if (extraDataType_var140 == 4)
					{

						{
							unsigned char unknown_var175 = 0;
							Read<unsigned char>("unknown", handler, unknown_var175, "\t\t\t\t\t");

							ValidateValues(stream, "unknown", "\t\t\t\t\t", unknown_var175, (unsigned char)1);

							unsigned char type_var176 = 0;
							Read<unsigned char>("type", handler, type_var176, "\t\t\t\t\t");

							ValidateValues(stream, "type", "\t\t\t\t\t", type_var176, (unsigned char)1, (unsigned char)11);

							output0.ItemData.Badge.Type = (Enum::BadgeType)type_var176;

							Read<std::wstring>("id", handler, output0.ItemData.Badge.Id, "\t\t\t\t\t");

							if (type_var176 == 1)
							{
								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[0], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[0], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[1], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[1], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[2], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[2], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[3], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[3], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[4], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[4], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[5], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[5], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[6], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[6], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[7], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[7], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[8], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[8], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[9], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[9], (bool)0, (bool)1);
							}

							if (type_var176 == 11)
							{
								int petSkinId_var188 = 0;
								Read<int>("petSkinId", handler, petSkinId_var188, "\t\t\t\t\t\t");

								output0.ItemData.Badge.PetSkinId = (Enum::PetId)petSkinId_var188;
							}
						}
					}

					{

						int transferFlags_var189 = 0;
						Read<int>("transferFlags", handler, transferFlags_var189, "\t\t\t\t");

						output0.ItemData.ItemTransfer.TransferFlags = (unsigned int)transferFlags_var189;

						bool unknown_var190 = false;
						Read<bool>("unknown", handler, unknown_var190, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var190, (bool)0, (bool)1);

						int remainingTrades_var191 = 0;
						Read<int>("remainingTrades", handler, remainingTrades_var191, "\t\t\t\t");

						output0.ItemData.ItemTransfer.RemainingTrades = (unsigned int)remainingTrades_var191;

						int remainingPackages_var192 = 0;
						Read<int>("remainingPackages", handler, remainingPackages_var192, "\t\t\t\t");

						output0.ItemData.ItemTransfer.RemainingPackages = (unsigned int)remainingPackages_var192;

						unsigned char unknown_var193 = 0;
						Read<unsigned char>("unknown", handler, unknown_var193, "\t\t\t\t");

						bool unknown_var194 = false;
						Read<bool>("unknown", handler, unknown_var194, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var194, (bool)0, (bool)1);

						bool isBound_var195 = false;
						Read<bool>("isBound", handler, isBound_var195, "\t\t\t\t");

						ValidateValues(stream, "isBound", "\t\t\t\t", isBound_var195, (bool)0, (bool)1);

						output0.ItemData.ItemTransfer.IsBound = (bool)isBound_var195;

						if (isBound_var195)
						{

							{
								long long characterId_var196 = 0;
								Read<long long>("characterId", handler, characterId_var196, "\t\t\t\t\t\t");

								std::wstring name_var197;
								Read<std::wstring>("name", handler, name_var197, "\t\t\t\t\t\t");
							}
						}
					}

					{
						Read<unsigned char>("maxSlots", handler, output0.ItemData.ItemSocket.MaxSlots, "\t\t\t\t");

						unsigned char unlockedSlots_var199 = 0;
						Read<unsigned char>("unlockedSlots", handler, unlockedSlots_var199, "\t\t\t\t");

						output0.ItemData.ItemSocket.UnlockedSlots = (unsigned char)unlockedSlots_var199;

						ResizeVector(handler, output0.ItemData.ItemSocket.Sockets, unlockedSlots_var199);

						for (unsigned char i = 0; i < unlockedSlots_var199 && !handler.PacketStream.HasRecentlyFailed; ++i)
						{
							bool hasGem_var200 = false;
							Read<bool>("hasGem", handler, hasGem_var200, "\t\t\t\t\t");

							ValidateValues(stream, "hasGem", "\t\t\t\t\t", hasGem_var200, (bool)0, (bool)1);

							output0.ItemData.ItemSocket.Sockets[i].HasGem = (bool)hasGem_var200;

							if (hasGem_var200)
							{

								{
									int itemId_var201 = 0;
									Read<int>("itemId", handler, itemId_var201, "\t\t\t\t\t\t\t");

									output0.ItemData.ItemSocket.Sockets[i].Gem.ItemId = (Enum::ItemId)itemId_var201;

									bool isBound_var202 = false;
									Read<bool>("isBound", handler, isBound_var202, "\t\t\t\t\t\t\t");

									ValidateValues(stream, "isBound", "\t\t\t\t\t\t\t", isBound_var202, (bool)0, (bool)1);

									output0.ItemData.ItemSocket.Sockets[i].Gem.IsBound = (bool)isBound_var202;

									if (isBound_var202)
									{

										{
											long long characterId_var203 = 0;
											Read<long long>("characterId", handler, characterId_var203, "\t\t\t\t\t\t\t\t\t");

											std::wstring name_var204;
											Read<std::wstring>("name", handler, name_var204, "\t\t\t\t\t\t\t\t\t");
										}
									}
									Read<bool>("isLocked", handler, output0.ItemData.ItemSocket.Sockets[i].Gem.IsLocked, "\t\t\t\t\t\t\t");

									ValidateValues(stream, "isLocked", "\t\t\t\t\t\t\t", output0.ItemData.ItemSocket.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

									if (isLocked_var21)
									{
										unsigned char unknown_var206 = 0;
										Read<unsigned char>("unknown", handler, unknown_var206, "\t\t\t\t\t\t\t\t");

										long long unlockTime_var207 = 0;
										Read<long long>("unlockTime", handler, unlockTime_var207, "\t\t\t\t\t\t\t\t");

										output0.ItemData.ItemSocket.Sockets[i].Gem.UnlockTime = (unsigned long long)unlockTime_var207;
									}
								}
							}
						}
					}

					{

						long long characterId_var208 = 0;
						Read<long long>("characterId", handler, characterId_var208, "\t\t\t\t");

						output0.ItemData.ItemCouple.CharacterId = (Enum::CharacterId)characterId_var208;

						if (characterId_var208 != 0)
						{
							Read<std::wstring>("name", handler, output0.ItemData.ItemCouple.Name, "\t\t\t\t\t");
							Read<bool>("isCreator", handler, output0.ItemData.ItemCouple.IsCreator, "\t\t\t\t\t");

							ValidateValues(stream, "isCreator", "\t\t\t\t\t", output0.ItemData.ItemCouple.IsCreator, (bool)0, (bool)1);
						}
					}

					{

						long long characterId_var211 = 0;
						Read<long long>("characterId", handler, characterId_var211, "\t\t\t\t");

						std::wstring name_var212;
						Read<std::wstring>("name", handler, name_var212, "\t\t\t\t");
					}
				}
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x2c>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldRemoveItemPacket output0;

			int objectId_var0 = 0;
			Read<int>("objectId", handler, objectId_var0, "\t");

			output0.ObjectId = (Enum::ItemEntityId)objectId_var0;

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemoveItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x57>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldRemoveNpc output0;

			int actorId_var0 = 0;
			Read<int>("actorId", handler, actorId_var0, "\t");

			output0.ActorId = (Enum::ActorId)actorId_var0;

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldRemoveNpc>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<12, ServerPacket, 0x5f>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Server::TrophyStartPacket output0;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::TrophyStartPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::TrophyContentPacket output1;

				int count_var1 = 0;
				Read<int>("count", handler, count_var1, "\t\t");

				ResizeVector(handler, output1.Trophies, count_var1);

				for (int i = 0; i < count_var1 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int trophyId_var2 = 0;
					Read<int>("trophyId", handler, trophyId_var2, "\t\t\t");

					output1.Trophies[i].TrophyId = (Enum::TrophyId)trophyId_var2;

					int unknown_var3 = 0;
					Read<int>("unknown", handler, unknown_var3, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var3, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6, (int)7, (int)8, (int)9);

					unsigned char status_var4 = 0;
					Read<unsigned char>("status", handler, status_var4, "\t\t\t");

					ValidateValues(stream, "status", "\t\t\t", status_var4, (unsigned char)2, (unsigned char)3);

					output1.Trophies[i].Status = (Server::TrophyContentPacket::StatusEnum)status_var4;

					int isDone_var5 = 0;
					Read<int>("isDone", handler, isDone_var5, "\t\t\t");

					output1.Trophies[i].IsDone = (bool)isDone_var5;

					Read<int>("nextGrade", handler, output1.Trophies[i].NextGrade, "\t\t\t");
					Read<int>("lastReward", handler, output1.Trophies[i].LastReward, "\t\t\t");
					Read<bool>("isFavorited", handler, output1.Trophies[i].IsFavorited, "\t\t\t");

					ValidateValues(stream, "isFavorited", "\t\t\t", output1.Trophies[i].IsFavorited, (bool)0, (bool)1);

					long long counter_var9 = 0;
					Read<long long>("counter", handler, counter_var9, "\t\t\t");

					output1.Trophies[i].Counter = (int)counter_var9;

					int timestampsCount_var10 = 0;
					Read<int>("timestampsCount", handler, timestampsCount_var10, "\t\t\t");

					ResizeVector(handler, output1.Trophies[i].Timestamps, timestampsCount_var10);

					for (int j = 0; j < timestampsCount_var10 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						Read<int>("index", handler, output1.Trophies[i].Timestamps[j].Index, "\t\t\t\t");
						Read<long long>("timestamp", handler, output1.Trophies[i].Timestamps[j].Time, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::TrophyContentPacket>(output1);

					return;
				}
			}

			if (mode_var0 == 2)
			{
				Server::TrophyUpdatePacket output2;

				int trophyId_var13 = 0;
				Read<int>("trophyId", handler, trophyId_var13, "\t\t");

				output2.TrophyId = (Enum::TrophyId)trophyId_var13;

				unsigned char status_var14 = 0;
				Read<unsigned char>("status", handler, status_var14, "\t\t");

				ValidateValues(stream, "status", "\t\t", status_var14, (unsigned char)2, (unsigned char)3);

				output2.Status = (Server::TrophyUpdatePacket::StatusEnum)status_var14;

				int isDone_var15 = 0;
				Read<int>("isDone", handler, isDone_var15, "\t\t");

				output2.IsDone = (bool)isDone_var15;

				Read<int>("nextGrade", handler, output2.NextGrade, "\t\t");
				Read<int>("lastReward", handler, output2.LastReward, "\t\t");
				Read<bool>("isFavorited", handler, output2.IsFavorited, "\t\t");

				ValidateValues(stream, "isFavorited", "\t\t", output2.IsFavorited, (bool)0, (bool)1);

				long long counter_var19 = 0;
				Read<long long>("counter", handler, counter_var19, "\t\t");

				output2.Counter = (int)counter_var19;

				int timestampsCount_var20 = 0;
				Read<int>("timestampsCount", handler, timestampsCount_var20, "\t\t");

				ResizeVector(handler, output2.Timestamps, timestampsCount_var20);

				for (int i = 0; i < timestampsCount_var20 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					Read<int>("index", handler, output2.Timestamps[i].Index, "\t\t\t");
					Read<long long>("timestamp", handler, output2.Timestamps[i].Time, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::TrophyUpdatePacket>(output2);

					return;
				}
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddItemPacket output0;

			int objectId_var0 = 0;
			Read<int>("objectId", handler, objectId_var0, "\t");

			output0.ObjectId = (Enum::ItemEntityId)objectId_var0;

			int itemId_var1 = 0;
			Read<int>("itemId", handler, itemId_var1, "\t");

			output0.ItemId = (Enum::ItemId)itemId_var1;

			int amount_var2 = 0;
			Read<int>("amount", handler, amount_var2, "\t");

			output0.Amount = (unsigned int)amount_var2;

			long long uid_var3 = 0;
			Read<long long>("uid", handler, uid_var3, "\t");
			Read<Vector3S>("position", handler, output0.Position, "\t");

			int ownerId_var5 = 0;
			Read<int>("ownerId", handler, ownerId_var5, "\t");

			output0.OwnerId = (Enum::CharacterId)ownerId_var5;

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t");

			int rarity_var7 = 0;
			Read<int>("rarity", handler, rarity_var7, "\t");

			ValidateValues(stream, "rarity", "\t", rarity_var7, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			output0.Rarity = (Enum::Rarity)rarity_var7;

			short unknown_var8 = 0;
			Read<short>("unknown", handler, unknown_var8, "\t");

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var9, (bool)0, (bool)1);

			bool unknown_var10 = false;
			Read<bool>("unknown", handler, unknown_var10, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var10, (bool)0, (bool)1);

			if (itemId_var1 < 90000001 || itemId_var1 > 90000003)
			{

				{
					int amount_var11 = 0;
					Read<int>("amount", handler, amount_var11, "\t\t\t");

					output0.ItemData.Amount = (unsigned int)amount_var11;

					int unknown_var12 = 0;
					Read<int>("unknown", handler, unknown_var12, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var12, (int)18446744073709551615);

					int unknown_var13 = 0;
					Read<int>("unknown", handler, unknown_var13, "\t\t\t");

					long long creationTime_var14 = 0;
					Read<long long>("creationTime", handler, creationTime_var14, "\t\t\t");

					output0.ItemData.CreationTime = (unsigned long long)creationTime_var14;

					long long expirationTime_var15 = 0;
					Read<long long>("expirationTime", handler, expirationTime_var15, "\t\t\t");

					output0.ItemData.ExpirationTime = (unsigned long long)expirationTime_var15;

					long long unknown_var16 = 0;
					Read<long long>("unknown", handler, unknown_var16, "\t\t\t");

					int timesChanged_var17 = 0;
					Read<int>("timesChanged", handler, timesChanged_var17, "\t\t\t");

					output0.ItemData.TimesChanged = (unsigned int)timesChanged_var17;

					int remainingUses_var18 = 0;
					Read<int>("remainingUses", handler, remainingUses_var18, "\t\t\t");

					output0.ItemData.RemainingUses = (unsigned int)remainingUses_var18;

					bool isLocked_var19 = false;
					Read<bool>("isLocked", handler, isLocked_var19, "\t\t\t");

					ValidateValues(stream, "isLocked", "\t\t\t", isLocked_var19, (bool)0, (bool)1);

					output0.ItemData.IsLocked = (bool)isLocked_var19;

					long long unlockTime_var20 = 0;
					Read<long long>("unlockTime", handler, unlockTime_var20, "\t\t\t");

					output0.ItemData.UnlockTime = (bool)unlockTime_var20;

					short glamorForges_var21 = 0;
					Read<short>("glamorForges", handler, glamorForges_var21, "\t\t\t");

					output0.ItemData.GlamorForges = (bool)glamorForges_var21;

					unsigned char unknownBool_var22 = 0;
					Read<unsigned char>("unknownBool", handler, unknownBool_var22, "\t\t\t");

					ValidateValues(stream, "unknownBool", "\t\t\t", unknownBool_var22, (unsigned char)0);

					{

						{

							Color4I_BGRA dyeColorPrimary_var23;
							Read<Color4I_BGRA>("dyeColorPrimary", handler, dyeColorPrimary_var23, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Primary = (Color4I)dyeColorPrimary_var23;

							Color4I_BGRA dyeColorSecondary_var24;
							Read<Color4I_BGRA>("dyeColorSecondary", handler, dyeColorSecondary_var24, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Secondary = (Color4I)dyeColorSecondary_var24;

							Color4I_BGRA dyeColorTertiary_var25;
							Read<Color4I_BGRA>("dyeColorTertiary", handler, dyeColorTertiary_var25, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Tertiary = (Color4I)dyeColorTertiary_var25;

							int dyeColorIndex_var26 = 0;
							Read<int>("dyeColorIndex", handler, dyeColorIndex_var26, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Index = (unsigned int)dyeColorIndex_var26;

							int unknown_var27 = 0;
							Read<int>("unknown", handler, unknown_var27, "\t\t\t\t\t");
						}

						short itemCategory_var28 = 0;

						itemCategory_var28 = handler.GetItemCategory(itemId_var1);

						if (itemCategory_var28 == 113)
						{

							{
								Read<Vector3S>("position1", handler, output0.ItemData.Customization.Cap.Position1, "\t\t\t\t\t\t");
								Read<Vector3S>("position2", handler, output0.ItemData.Customization.Cap.Position2, "\t\t\t\t\t\t");
								Read<Vector3S>("position3", handler, output0.ItemData.Customization.Cap.Position3, "\t\t\t\t\t\t");
								Read<Vector3S>("position4", handler, output0.ItemData.Customization.Cap.Position4, "\t\t\t\t\t\t");

								float unknown_var33 = 0;
								Read<float>("unknown", handler, unknown_var33, "\t\t\t\t\t\t");
							}
						}

						if (itemCategory_var28 == 102)
						{

							{
								Read<float>("backLength", handler, output0.ItemData.Customization.Hair.BackLength, "\t\t\t\t\t\t");
								Read<Vector3S>("backPosition1", handler, output0.ItemData.Customization.Hair.BackPosition1, "\t\t\t\t\t\t");
								Read<Vector3S>("backPosition2", handler, output0.ItemData.Customization.Hair.BackPosition2, "\t\t\t\t\t\t");
								Read<float>("frontLength", handler, output0.ItemData.Customization.Hair.FrontLength, "\t\t\t\t\t\t");
								Read<Vector3S>("frontPosition1", handler, output0.ItemData.Customization.Hair.FrontPosition1, "\t\t\t\t\t\t");
								Read<Vector3S>("frontPosition2", handler, output0.ItemData.Customization.Hair.FrontPosition2, "\t\t\t\t\t\t");
							}
						}

						if (itemCategory_var28 == 104)
						{

							{
								Read<Vector3S>("position1", handler, output0.ItemData.Customization.Decal.Position1, "\t\t\t\t\t\t");
								Read<Vector3S>("position2", handler, output0.ItemData.Customization.Decal.Position2, "\t\t\t\t\t\t");
								Read<Vector3S>("position3", handler, output0.ItemData.Customization.Decal.Position3, "\t\t\t\t\t\t");
								Read<Vector3S>("position4", handler, output0.ItemData.Customization.Decal.Position4, "\t\t\t\t\t\t");
							}
						}
					}

					{

						{

							short statCount_var44 = 0;
							Read<short>("statCount", handler, statCount_var44, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Constant.Basic, statCount_var44);

							for (short i = 0; i < statCount_var44 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var45 = 0;
								Read<short>("type", handler, type_var45, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Constant.Basic[i].Type = (Enum::StatAttributeBasic)type_var45;

								Read<int>("value", handler, output0.ItemData.Stats.Constant.Basic[i].Value, "\t\t\t\t\t\t");

								float rate_var47 = 0;
								Read<float>("rate", handler, rate_var47, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var44, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Constant.Special, statCount_var44);

							for (short i = 0; i < statCount_var44 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var48 = 0;
								Read<short>("type", handler, type_var48, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Constant.Special[i].Type = (Enum::StatAttributeSpecial)type_var48;

								Read<float>("value", handler, output0.ItemData.Stats.Constant.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Constant.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var51 = 0;
						Read<int>("unknown", handler, unknown_var51, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var51, (int)0);

						{

							short statCount_var52 = 0;
							Read<short>("statCount", handler, statCount_var52, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Static.Basic, statCount_var52);

							for (short i = 0; i < statCount_var52 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var53 = 0;
								Read<short>("type", handler, type_var53, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Static.Basic[i].Type = (Enum::StatAttributeBasic)type_var53;

								Read<int>("value", handler, output0.ItemData.Stats.Static.Basic[i].Value, "\t\t\t\t\t\t");

								float rate_var55 = 0;
								Read<float>("rate", handler, rate_var55, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var52, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Static.Special, statCount_var52);

							for (short i = 0; i < statCount_var52 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var56 = 0;
								Read<short>("type", handler, type_var56, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Static.Special[i].Type = (Enum::StatAttributeSpecial)type_var56;

								Read<float>("value", handler, output0.ItemData.Stats.Static.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Static.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var59 = 0;
						Read<int>("unknown", handler, unknown_var59, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var59, (int)0);

						{

							short statCount_var60 = 0;
							Read<short>("statCount", handler, statCount_var60, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Random.Basic, statCount_var60);

							for (short i = 0; i < statCount_var60 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var61 = 0;
								Read<short>("type", handler, type_var61, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Random.Basic[i].Type = (Enum::StatAttributeBasic)type_var61;

								Read<int>("value", handler, output0.ItemData.Stats.Random.Basic[i].Value, "\t\t\t\t\t\t");

								float rate_var63 = 0;
								Read<float>("rate", handler, rate_var63, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var60, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Random.Special, statCount_var60);

							for (short i = 0; i < statCount_var60 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var64 = 0;
								Read<short>("type", handler, type_var64, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Random.Special[i].Type = (Enum::StatAttributeSpecial)type_var64;

								Read<float>("value", handler, output0.ItemData.Stats.Random.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Random.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var67 = 0;
						Read<int>("unknown", handler, unknown_var67, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var67, (int)0);

						{

							short statCount_var68 = 0;
							Read<short>("statCount", handler, statCount_var68, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Title.Basic, statCount_var68);

							for (short i = 0; i < statCount_var68 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var69 = 0;
								Read<short>("type", handler, type_var69, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Title.Basic[i].Type = (Enum::StatAttributeBasic)type_var69;

								Read<int>("value", handler, output0.ItemData.Stats.Title.Basic[i].Value, "\t\t\t\t\t\t");

								float rate_var71 = 0;
								Read<float>("rate", handler, rate_var71, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var68, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Title.Special, statCount_var68);

							for (short i = 0; i < statCount_var68 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var72 = 0;
								Read<short>("type", handler, type_var72, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Title.Special[i].Type = (Enum::StatAttributeSpecial)type_var72;

								Read<float>("value", handler, output0.ItemData.Stats.Title.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.Stats.Title.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var75 = 0;
						Read<int>("unknown", handler, unknown_var75, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var75, (int)0);

						{

							short statCount_var76 = 0;
							Read<short>("statCount", handler, statCount_var76, "\t\t\t\t\t");

							for (short i = 0; i < statCount_var76 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var77 = 0;
								Read<short>("type", handler, type_var77, "\t\t\t\t\t\t");

								int value_var78 = 0;
								Read<int>("value", handler, value_var78, "\t\t\t\t\t\t");

								float rate_var79 = 0;
								Read<float>("rate", handler, rate_var79, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var76, "\t\t\t\t\t");

							for (short i = 0; i < statCount_var76 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var80 = 0;
								Read<short>("type", handler, type_var80, "\t\t\t\t\t\t");

								float value_var81 = 0;
								Read<float>("value", handler, value_var81, "\t\t\t\t\t\t");

								float rate_var82 = 0;
								Read<float>("rate", handler, rate_var82, "\t\t\t\t\t\t");
							}
						}

						int unknown_var83 = 0;
						Read<int>("unknown", handler, unknown_var83, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var83, (int)0);
					}

					{

						int enchantLevel_var84 = 0;
						Read<int>("enchantLevel", handler, enchantLevel_var84, "\t\t\t\t");

						output0.ItemData.Enchantment.Level = (unsigned int)enchantLevel_var84;

						int enchantExp_var85 = 0;
						Read<int>("enchantExp", handler, enchantExp_var85, "\t\t\t\t");

						output0.ItemData.Enchantment.EnchantExp = (unsigned int)enchantExp_var85;

						Read<unsigned char>("enchantCharges", handler, output0.ItemData.Enchantment.EnchantCharges, "\t\t\t\t");

						long long unknown_var87 = 0;
						Read<long long>("unknown", handler, unknown_var87, "\t\t\t\t");

						int unknown_var88 = 0;
						Read<int>("unknown", handler, unknown_var88, "\t\t\t\t");

						int unknown_var89 = 0;
						Read<int>("unknown", handler, unknown_var89, "\t\t\t\t");
						Read<bool>("canRepackage", handler, output0.ItemData.Enchantment.CanRepackage, "\t\t\t\t");

						ValidateValues(stream, "canRepackage", "\t\t\t\t", output0.ItemData.Enchantment.CanRepackage, (bool)0, (bool)1);

						int charges_var91 = 0;
						Read<int>("charges", handler, charges_var91, "\t\t\t\t");

						output0.ItemData.Enchantment.Charges = (unsigned int)charges_var91;

						unsigned char basicStatCount_var92 = 0;
						Read<unsigned char>("basicStatCount", handler, basicStatCount_var92, "\t\t\t\t");

						ResizeVector(handler, output0.ItemData.Enchantment.Basic, basicStatCount_var92);

						for (unsigned char i = 0; i < basicStatCount_var92 && !handler.PacketStream.HasRecentlyFailed; ++i)
						{
							int type_var93 = 0;
							Read<int>("type", handler, type_var93, "\t\t\t\t\t");

							output0.ItemData.Enchantment.Basic[i].Type = (Enum::StatAttributeBasic)type_var93;

							Read<int>("value", handler, output0.ItemData.Enchantment.Basic[i].Value, "\t\t\t\t\t");
							Read<float>("rate", handler, output0.ItemData.Enchantment.Basic[i].Rate, "\t\t\t\t\t");
						}
					}

					{

						int limitBreakLevel_var96 = 0;
						Read<int>("limitBreakLevel", handler, limitBreakLevel_var96, "\t\t\t\t");

						output0.ItemData.LimitBreak.Level = (unsigned int)limitBreakLevel_var96;

						{

							int statCount_var97 = 0;
							Read<int>("statCount", handler, statCount_var97, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.LimitBreak.Stats.Basic, statCount_var97);

							for (int i = 0; i < statCount_var97 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var98 = 0;
								Read<short>("type", handler, type_var98, "\t\t\t\t\t\t");

								output0.ItemData.LimitBreak.Stats.Basic[i].Type = (Enum::StatAttributeBasic)type_var98;

								Read<int>("value", handler, output0.ItemData.LimitBreak.Stats.Basic[i].Value, "\t\t\t\t\t\t");

								float rate_var100 = 0;
								Read<float>("rate", handler, rate_var100, "\t\t\t\t\t\t");
							}

							Read<int>("statCount", handler, statCount_var97, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.LimitBreak.Stats.Special, statCount_var97);

							for (int i = 0; i < statCount_var97 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var101 = 0;
								Read<short>("type", handler, type_var101, "\t\t\t\t\t\t");

								output0.ItemData.LimitBreak.Stats.Special[i].Type = (Enum::StatAttributeSpecial)type_var101;

								Read<float>("value", handler, output0.ItemData.LimitBreak.Stats.Special[i].Value, "\t\t\t\t\t\t");
								Read<float>("rate", handler, output0.ItemData.LimitBreak.Stats.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}
					}

					unsigned char extraDataType_var104 = 0;

					extraDataType_var104 = handler.GetItemExtraDataType(itemId_var1);

					ValidateValues(stream, "extraDataType", "\t\t\t", extraDataType_var104, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					if (extraDataType_var104 == 1)
					{

						{
							long long unknown_var105 = 0;
							Read<long long>("unknown", handler, unknown_var105, "\t\t\t\t\t");
							Read<std::wstring>("fileName", handler, output0.ItemData.Template.FileName, "\t\t\t\t\t");
							Read<std::wstring>("name", handler, output0.ItemData.Template.Name, "\t\t\t\t\t");

							unsigned char unknown_var108 = 0;
							Read<unsigned char>("unknown", handler, unknown_var108, "\t\t\t\t\t");

							int unknown_var109 = 0;
							Read<int>("unknown", handler, unknown_var109, "\t\t\t\t\t");

							long long accountId_var110 = 0;
							Read<long long>("accountId", handler, accountId_var110, "\t\t\t\t\t");

							output0.ItemData.Template.AccountId = (Enum::AccountId)accountId_var110;

							long long characterId_var111 = 0;
							Read<long long>("characterId", handler, characterId_var111, "\t\t\t\t\t");

							output0.ItemData.Template.CharacterId = (Enum::CharacterId)characterId_var111;

							Read<std::wstring>("author", handler, output0.ItemData.Template.Author, "\t\t\t\t\t");

							long long creationTime_var113 = 0;
							Read<long long>("creationTime", handler, creationTime_var113, "\t\t\t\t\t");

							output0.ItemData.Template.CreationTime = (unsigned long long)creationTime_var113;

							Read<std::wstring>("url", handler, output0.ItemData.Template.Url, "\t\t\t\t\t");

							unsigned char unknown_var115 = 0;
							Read<unsigned char>("unknown", handler, unknown_var115, "\t\t\t\t\t");
						}

						{

							long long unknown_var116 = 0;
							Read<long long>("unknown", handler, unknown_var116, "\t\t\t\t\t");

							int unknown_var117 = 0;
							Read<int>("unknown", handler, unknown_var117, "\t\t\t\t\t");

							int unknown_var118 = 0;
							Read<int>("unknown", handler, unknown_var118, "\t\t\t\t\t");

							int unknown_var119 = 0;
							Read<int>("unknown", handler, unknown_var119, "\t\t\t\t\t");

							long long unknown_var120 = 0;
							Read<long long>("unknown", handler, unknown_var120, "\t\t\t\t\t");

							int unknown_var121 = 0;
							Read<int>("unknown", handler, unknown_var121, "\t\t\t\t\t");

							long long unknown_var122 = 0;
							Read<long long>("unknown", handler, unknown_var122, "\t\t\t\t\t");

							long long unknown_var123 = 0;
							Read<long long>("unknown", handler, unknown_var123, "\t\t\t\t\t");

							std::wstring unknown_var124;
							Read<std::wstring>("unknown", handler, unknown_var124, "\t\t\t\t\t");
						}
					}

					if (extraDataType_var104 == 2)
					{

						{
							Read<std::wstring>("name", handler, output0.ItemData.Pet.Name, "\t\t\t\t\t");

							long long exp_var126 = 0;
							Read<long long>("exp", handler, exp_var126, "\t\t\t\t\t");

							output0.ItemData.Pet.Exp = (unsigned long long)exp_var126;

							int evolvePoints_var127 = 0;
							Read<int>("evolvePoints", handler, evolvePoints_var127, "\t\t\t\t\t");

							output0.ItemData.Pet.EvolvePoints = (unsigned int)evolvePoints_var127;

							int level_var128 = 0;
							Read<int>("level", handler, level_var128, "\t\t\t\t\t");

							output0.ItemData.Pet.Level = (unsigned int)level_var128;

							Read<bool>("hasItems", handler, output0.ItemData.Pet.HasItems, "\t\t\t\t\t");

							ValidateValues(stream, "hasItems", "\t\t\t\t\t", output0.ItemData.Pet.HasItems, (bool)0, (bool)1);
						}
					}

					if (extraDataType_var104 == 3)
					{

						{
							int length_var130 = 0;
							Read<int>("length", handler, length_var130, "\t\t\t\t\t");

							output0.ItemData.Music.Length = (unsigned int)length_var130;

							int instrument_var131 = 0;
							Read<int>("instrument", handler, instrument_var131, "\t\t\t\t\t");

							output0.ItemData.Music.Instrument = (unsigned int)instrument_var131;

							Read<std::wstring>("title", handler, output0.ItemData.Music.Title, "\t\t\t\t\t");
							Read<std::wstring>("author", handler, output0.ItemData.Music.Author, "\t\t\t\t\t");

							int unknown_var134 = 0;
							Read<int>("unknown", handler, unknown_var134, "\t\t\t\t\t");

							ValidateValues(stream, "unknown", "\t\t\t\t\t", unknown_var134, (int)1);

							long long authorId_var135 = 0;
							Read<long long>("authorId", handler, authorId_var135, "\t\t\t\t\t");

							output0.ItemData.Music.AuthorId = (Enum::CharacterId)authorId_var135;

							Read<bool>("isLocked", handler, output0.ItemData.Music.IsLocked, "\t\t\t\t\t");

							ValidateValues(stream, "isLocked", "\t\t\t\t\t", output0.ItemData.Music.IsLocked, (bool)0, (bool)1);

							long long unknown_var137 = 0;
							Read<long long>("unknown", handler, unknown_var137, "\t\t\t\t\t");

							long long unknown_var138 = 0;
							Read<long long>("unknown", handler, unknown_var138, "\t\t\t\t\t");
						}
					}

					if (extraDataType_var104 == 4)
					{

						{
							unsigned char unknown_var139 = 0;
							Read<unsigned char>("unknown", handler, unknown_var139, "\t\t\t\t\t");

							ValidateValues(stream, "unknown", "\t\t\t\t\t", unknown_var139, (unsigned char)1);

							unsigned char type_var140 = 0;
							Read<unsigned char>("type", handler, type_var140, "\t\t\t\t\t");

							ValidateValues(stream, "type", "\t\t\t\t\t", type_var140, (unsigned char)1, (unsigned char)11);

							output0.ItemData.Badge.Type = (Enum::BadgeType)type_var140;

							int id_var141 = 0;
							Read<int>("id", handler, id_var141, "\t\t\t\t\t");

							output0.ItemData.Badge.BadgeId = (Enum::BadgeId)id_var141;

							if (type_var140 == 1)
							{
								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[0], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[0], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[1], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[1], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[2], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[2], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[3], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[3], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[4], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[4], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[5], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[5], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[6], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[6], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[7], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[7], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[8], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[8], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[9], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[9], (bool)0, (bool)1);
							}

							if (type_var140 == 11)
							{
								int petSkinId_var152 = 0;
								Read<int>("petSkinId", handler, petSkinId_var152, "\t\t\t\t\t\t");

								output0.ItemData.Badge.PetSkinId = (Enum::PetId)petSkinId_var152;
							}
						}
					}

					{

						int transferFlags_var153 = 0;
						Read<int>("transferFlags", handler, transferFlags_var153, "\t\t\t\t");

						output0.ItemData.ItemTransfer.TransferFlags = (unsigned int)transferFlags_var153;

						bool unknown_var154 = false;
						Read<bool>("unknown", handler, unknown_var154, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var154, (bool)0, (bool)1);

						int remainingTrades_var155 = 0;
						Read<int>("remainingTrades", handler, remainingTrades_var155, "\t\t\t\t");

						output0.ItemData.ItemTransfer.RemainingTrades = (unsigned int)remainingTrades_var155;

						int remainingPackages_var156 = 0;
						Read<int>("remainingPackages", handler, remainingPackages_var156, "\t\t\t\t");

						output0.ItemData.ItemTransfer.RemainingPackages = (unsigned int)remainingPackages_var156;

						unsigned char unknown_var157 = 0;
						Read<unsigned char>("unknown", handler, unknown_var157, "\t\t\t\t");

						bool unknown_var158 = false;
						Read<bool>("unknown", handler, unknown_var158, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var158, (bool)0, (bool)1);

						bool isBound_var159 = false;
						Read<bool>("isBound", handler, isBound_var159, "\t\t\t\t");

						ValidateValues(stream, "isBound", "\t\t\t\t", isBound_var159, (bool)0, (bool)1);

						output0.ItemData.ItemTransfer.IsBound = (bool)isBound_var159;

						if (isBound_var159)
						{

							{
								long long characterId_var160 = 0;
								Read<long long>("characterId", handler, characterId_var160, "\t\t\t\t\t\t");

								std::wstring name_var161;
								Read<std::wstring>("name", handler, name_var161, "\t\t\t\t\t\t");
							}
						}
					}

					{
						Read<unsigned char>("maxSlots", handler, output0.ItemData.ItemSocket.MaxSlots, "\t\t\t\t");

						unsigned char unlockedSlots_var163 = 0;
						Read<unsigned char>("unlockedSlots", handler, unlockedSlots_var163, "\t\t\t\t");

						output0.ItemData.ItemSocket.UnlockedSlots = (unsigned char)unlockedSlots_var163;

						ResizeVector(handler, output0.ItemData.ItemSocket.Sockets, unlockedSlots_var163);

						for (unsigned char i = 0; i < unlockedSlots_var163 && !handler.PacketStream.HasRecentlyFailed; ++i)
						{
							bool hasGem_var164 = false;
							Read<bool>("hasGem", handler, hasGem_var164, "\t\t\t\t\t");

							ValidateValues(stream, "hasGem", "\t\t\t\t\t", hasGem_var164, (bool)0, (bool)1);

							output0.ItemData.ItemSocket.Sockets[i].HasGem = (bool)hasGem_var164;

							if (hasGem_var164)
							{

								{
									int itemId_var165 = 0;
									Read<int>("itemId", handler, itemId_var165, "\t\t\t\t\t\t\t");

									output0.ItemData.ItemSocket.Sockets[i].Gem.ItemId = (Enum::ItemId)itemId_var165;

									bool isBound_var166 = false;
									Read<bool>("isBound", handler, isBound_var166, "\t\t\t\t\t\t\t");

									ValidateValues(stream, "isBound", "\t\t\t\t\t\t\t", isBound_var166, (bool)0, (bool)1);

									output0.ItemData.ItemSocket.Sockets[i].Gem.IsBound = (bool)isBound_var166;

									if (isBound_var166)
									{

										{
											long long characterId_var167 = 0;
											Read<long long>("characterId", handler, characterId_var167, "\t\t\t\t\t\t\t\t\t");

											std::wstring name_var168;
											Read<std::wstring>("name", handler, name_var168, "\t\t\t\t\t\t\t\t\t");
										}
									}
									Read<bool>("isLocked", handler, output0.ItemData.ItemSocket.Sockets[i].Gem.IsLocked, "\t\t\t\t\t\t\t");

									ValidateValues(stream, "isLocked", "\t\t\t\t\t\t\t", output0.ItemData.ItemSocket.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

									if (isLocked_var19)
									{
										unsigned char unknown_var170 = 0;
										Read<unsigned char>("unknown", handler, unknown_var170, "\t\t\t\t\t\t\t\t");

										long long unlockTime_var171 = 0;
										Read<long long>("unlockTime", handler, unlockTime_var171, "\t\t\t\t\t\t\t\t");

										output0.ItemData.ItemSocket.Sockets[i].Gem.UnlockTime = (unsigned long long)unlockTime_var171;
									}
								}
							}
						}
					}

					{

						long long characterId_var172 = 0;
						Read<long long>("characterId", handler, characterId_var172, "\t\t\t\t");

						output0.ItemData.ItemCouple.CharacterId = (Enum::CharacterId)characterId_var172;

						if (characterId_var172 != 0)
						{
							Read<std::wstring>("name", handler, output0.ItemData.ItemCouple.Name, "\t\t\t\t\t");
							Read<bool>("isCreator", handler, output0.ItemData.ItemCouple.IsCreator, "\t\t\t\t\t");

							ValidateValues(stream, "isCreator", "\t\t\t\t\t", output0.ItemData.ItemCouple.IsCreator, (bool)0, (bool)1);
						}
					}

					{

						long long characterId_var175 = 0;
						Read<long long>("characterId", handler, characterId_var175, "\t\t\t\t");

						std::wstring name_var176;
						Read<std::wstring>("name", handler, name_var176, "\t\t\t\t");
					}
				}
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<2486, ServerPacket, 0x3d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", handler, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				int casterId_var2 = 0;
				Read<int>("casterId", handler, casterId_var2, "\t\t");

				output0.CasterId = (Enum::ActorId)casterId_var2;

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", handler, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				if (skillId_var3 == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", handler, unknown_var4, "\t\t\t");
				}

				if (skillId_var3 != 0)
				{
					unsigned short skillLevel_var5 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var5, "\t\t\t");

					output0.SkillLevel = (Enum::SkillLevel)skillLevel_var5;

					Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t\t");

					short posX_var8 = 0;
					Read<short>("posX", handler, posX_var8, "\t\t\t");

					short posY_var9 = 0;
					Read<short>("posY", handler, posY_var9, "\t\t\t");

					short posZ_var10 = 0;
					Read<short>("posZ", handler, posZ_var10, "\t\t\t");
					Read<Vector3S>("direction", handler, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", handler, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					unsigned char count_var13 = 0;
					Read<unsigned char>("count", handler, count_var13, "\t\t\t");

					ResizeVector(handler, output0.Hits, count_var13);

					for (unsigned char i = 0; i < count_var13 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						long long hitId_var14 = 0;
						Read<long long>("hitId", handler, hitId_var14, "\t\t\t\t");

						int attackCount_var15 = 0;
						Read<int>("attackCount", handler, attackCount_var15, "\t\t\t\t");

						int casterId_var16 = 0;
						Read<int>("casterId", handler, casterId_var16, "\t\t\t\t");

						int targetId_var17 = 0;
						Read<int>("targetId", handler, targetId_var17, "\t\t\t\t");

						output0.Hits[i].TargetId = (Enum::ActorId)targetId_var17;

						Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				long long skillSn_var19 = 0;
				Read<long long>("skillSn", handler, skillSn_var19, "\t\t");

				output1.SkillSn = (Enum::SkillSn)skillSn_var19;

				long long hitId_var20 = 0;
				Read<long long>("hitId", handler, hitId_var20, "\t\t");

				int casterId_var21 = 0;
				Read<int>("casterId", handler, casterId_var21, "\t\t");

				output1.CasterId = (Enum::ActorId)casterId_var21;

				unsigned int skillId_var22 = 0;
				Read<unsigned int>("skillId", handler, skillId_var22, "\t\t");

				output1.SkillId = (Enum::SkillId)skillId_var22;

				unsigned short skillLevel_var23 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var23, "\t\t");

				output1.SkillLevel = (Enum::SkillLevel)skillLevel_var23;

				Read<unsigned char>("motionPoint", handler, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t");

				short posX_var26 = 0;
				Read<short>("posX", handler, posX_var26, "\t\t");

				short posY_var27 = 0;
				Read<short>("posY", handler, posY_var27, "\t\t");

				short posZ_var28 = 0;
				Read<short>("posZ", handler, posZ_var28, "\t\t");

				short dirX_var29 = 0;
				Read<short>("dirX", handler, dirX_var29, "\t\t");

				short dirY_var30 = 0;
				Read<short>("dirY", handler, dirY_var30, "\t\t");

				short dirZ_var31 = 0;
				Read<short>("dirZ", handler, dirZ_var31, "\t\t");

				unsigned char count_var32 = 0;
				Read<unsigned char>("count", handler, count_var32, "\t\t");

				ResizeVector(handler, output1.DamagedTargets, count_var32);

				for (unsigned char i = 0; i < count_var32 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var33 = 0;
					Read<int>("targetId", handler, targetId_var33, "\t\t\t");

					output1.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var33;

					unsigned char damageCount_var34 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var34, "\t\t\t");

					ResizeVector(handler, output1.DamagedTargets[i].Damages, damageCount_var34);

					for (unsigned char j = 0; j < damageCount_var34 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var35 = 0;
						Read<unsigned char>("hitType", handler, hitType_var35, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var35, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output1.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var35;

						Read<long long>("damage", handler, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				int casterId_var37 = 0;
				Read<int>("casterId", handler, casterId_var37, "\t\t");

				output2.CasterId = (Enum::ActorId)casterId_var37;

				int targetId_var38 = 0;
				Read<int>("targetId", handler, targetId_var38, "\t\t");

				output2.TargetId = (Enum::ActorId)targetId_var38;

				Read<int>("serverTick", handler, output2.ServerTick, "\t\t");

				unsigned char hitType_var40 = 0;
				Read<unsigned char>("hitType", handler, hitType_var40, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", hitType_var40, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				output2.HitType = (Enum::HitType)hitType_var40;

				int damage_var41 = 0;
				Read<int>("damage", handler, damage_var41, "\t\t");

				output2.Damage = (long long)damage_var41;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				int casterId_var42 = 0;
				Read<int>("casterId", handler, casterId_var42, "\t\t");

				output3.CasterId = (Enum::ActorId)casterId_var42;

				int targetId_var43 = 0;
				Read<int>("targetId", handler, targetId_var43, "\t\t");

				output3.TargetId = (Enum::ActorId)targetId_var43;

				Read<int>("serverTick", handler, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", handler, output3.HpAmount, "\t\t");
				Read<int>("spAmount", handler, output3.SpAmount, "\t\t");
				Read<int>("epAmount", handler, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", handler, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				long long skillSn_var49 = 0;
				Read<long long>("skillSn", handler, skillSn_var49, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var49;

				int casterId_var50 = 0;
				Read<int>("casterId", handler, casterId_var50, "\t\t");

				output4.CasterId = (Enum::ActorId)casterId_var50;

				int regionSkillObjectId_var51 = 0;
				Read<int>("regionSkillObjectId", handler, regionSkillObjectId_var51, "\t\t");

				output4.RegionSkillObjectId = (Enum::ActorId)regionSkillObjectId_var51;

				Read<unsigned char>("attackPoint", handler, output4.AttackPoint, "\t\t");

				unsigned char count_var53 = 0;
				Read<unsigned char>("count", handler, count_var53, "\t\t");

				ResizeVector(handler, output4.DamagedTargets, count_var53);

				for (unsigned char i = 0; i < count_var53 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var54 = 0;
					Read<int>("targetId", handler, targetId_var54, "\t\t\t");

					output4.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var54;

					unsigned char damageCount_var55 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var55, "\t\t\t");

					short posX_var56 = 0;
					Read<short>("posX", handler, posX_var56, "\t\t\t");

					short posY_var57 = 0;
					Read<short>("posY", handler, posY_var57, "\t\t\t");

					short posZ_var58 = 0;
					Read<short>("posZ", handler, posZ_var58, "\t\t\t");
					Read<Vector3S>("direction", handler, output4.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output4.DamagedTargets[i].Damages, damageCount_var55);

					for (unsigned char j = 0; j < damageCount_var55 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var60 = 0;
						Read<unsigned char>("hitType", handler, hitType_var60, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var60, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output4.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var60;

						Read<long long>("damage", handler, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				long long skillSn_var62 = 0;
				Read<long long>("skillSn", handler, skillSn_var62, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var62;

				unsigned int skillId_var63 = 0;
				Read<unsigned int>("skillId", handler, skillId_var63, "\t\t");

				output5.SkillId = (Enum::SkillId)skillId_var63;

				unsigned short skillLevel_var64 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var64, "\t\t");

				output5.SkillLevel = (Enum::SkillLevel)skillLevel_var64;

				unsigned char count_var65 = 0;
				Read<unsigned char>("count", handler, count_var65, "\t\t");

				ResizeVector(handler, output5.DamagedTargets, count_var65);

				for (unsigned char i = 0; i < count_var65 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var66 = 0;
					Read<int>("targetId", handler, targetId_var66, "\t\t\t");

					output5.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var66;

					unsigned char damageCount_var67 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var67, "\t\t\t");

					short posX_var68 = 0;
					Read<short>("posX", handler, posX_var68, "\t\t\t");

					short posY_var69 = 0;
					Read<short>("posY", handler, posY_var69, "\t\t\t");

					short posZ_var70 = 0;
					Read<short>("posZ", handler, posZ_var70, "\t\t\t");
					Read<Vector3S>("direction", handler, output5.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output5.DamagedTargets[i].Damages, damageCount_var67);

					for (unsigned char j = 0; j < damageCount_var67 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var72 = 0;
						Read<unsigned char>("hitType", handler, hitType_var72, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var72, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output5.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var72;

						Read<long long>("damage", handler, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var74 = 0;
				Read<int>("unknown", handler, unknown_var74, "\t\t");

				int count_var75 = 0;
				Read<int>("count", handler, count_var75, "\t\t");

				for (int i = 0; i < count_var75 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int unknown_var76 = 0;
					Read<int>("unknown", handler, unknown_var76, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var77 = 0;
				Read<long long>("skillSn", handler, skillSn_var77, "\t\t");

				bool hasTarget_var78 = false;
				Read<bool>("hasTarget", handler, hasTarget_var78, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var78, (bool)0, (bool)1);

				if (hasTarget_var78)
				{
					unsigned int skillId_var79 = 0;
					Read<unsigned int>("skillId", handler, skillId_var79, "\t\t\t");

					unsigned short skillLevel_var80 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var80, "\t\t\t");

					int unknown_var81 = 0;
					Read<int>("unknown", handler, unknown_var81, "\t\t\t");

					int npcId_var82 = 0;
					Read<int>("npcId", handler, npcId_var82, "\t\t\t");
				}
			}
		}

		template <>
		void ParsePacket<13, ClientPacket, 0x3>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			std::wstring auth1_var1;
			Read<std::wstring>("auth1", handler, auth1_var1, "\t");

			std::wstring auth2_var2;
			Read<std::wstring>("auth2", handler, auth2_var2, "\t");

			unsigned long long unknown_var3 = 0;
			Read<unsigned long long>("unknown", handler, unknown_var3, "\t");

			unsigned long long unknown_var4 = 0;
			Read<unsigned long long>("unknown", handler, unknown_var4, "\t");

			int unknown_var5 = 0;
			Read<int>("unknown", handler, unknown_var5, "\t");

			short unknown_var6 = 0;
			Read<short>("unknown", handler, unknown_var6, "\t");

			int unknown_var7 = 0;
			Read<int>("unknown", handler, unknown_var7, "\t");

			int unknown_var8 = 0;
			Read<int>("unknown", handler, unknown_var8, "\t");
		}

		template <>
		void ParsePacket<13, ServerPacket, 0x47>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::BuffPacket output0;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2);

			output0.Mode = (Server::BuffPacket::ModeEnum)mode_var0;

			int targetActor_var1 = 0;
			Read<int>("targetActor", handler, targetActor_var1, "\t");

			int instanceId_var2 = 0;
			Read<int>("instanceId", handler, instanceId_var2, "\t");

			output0.InstanceId = (Enum::EffectInstanceId)instanceId_var2;

			int sourceActor_var3 = 0;
			Read<int>("sourceActor", handler, sourceActor_var3, "\t");

			if (mode_var0 == 0)
			{
				Read<int>("startTime", handler, output0.StartTime, "\t\t");
				Read<int>("endTime", handler, output0.EndTime, "\t\t");

				int effectId_var6 = 0;
				Read<int>("effectId", handler, effectId_var6, "\t\t");

				output0.EffectId = (Enum::EffectId)effectId_var6;

				short effectLevel_var7 = 0;
				Read<short>("effectLevel", handler, effectLevel_var7, "\t\t");

				output0.EffectLevel = (Enum::EffectLevel)effectLevel_var7;

				Read<int>("stacks", handler, output0.Stacks, "\t\t");
				Read<bool>("hasShield", handler, output0.UpdateShield, "\t\t");

				ValidateValues(stream, "hasShield", "\t\t", output0.UpdateShield, (bool)0, (bool)1);

				Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t");
			}

			if (mode_var0 == 2)
			{
				int flags_var11 = 0;
				Read<int>("flags", handler, flags_var11, "\t\t");

				output0.UpdateEffect = GetBit(flags_var11, 0);
				output0.UpdateShield = GetBit(flags_var11, 1);

				if (GetBit(flags_var11, 0) == 1)
				{
					Read<int>("startTime", handler, output0.StartTime, "\t\t\t");
					Read<int>("endTime", handler, output0.EndTime, "\t\t\t");

					int effectId_var14 = 0;
					Read<int>("effectId", handler, effectId_var14, "\t\t\t");

					output0.EffectId = (Enum::EffectId)effectId_var14;

					short effectLevel_var15 = 0;
					Read<short>("effectLevel", handler, effectLevel_var15, "\t\t\t");

					output0.EffectLevel = (Enum::EffectLevel)effectLevel_var15;

					Read<int>("stacks", handler, output0.Stacks, "\t\t\t");
					Read<bool>("enabled", handler, output0.Enabled, "\t\t\t");

					ValidateValues(stream, "enabled", "\t\t\t", output0.Enabled, (bool)0, (bool)1);
				}

				if (GetBit(flags_var11, 1) == 1)
				{
					Read<long long>("shieldHealth", handler, output0.ShieldHealth, "\t\t\t");
				}
			}

			if (instanceId_var2 == 0)
			{
				int unknown_var19 = 0;
				Read<int>("unknown", handler, unknown_var19, "\t\t");
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::BuffPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<2497, ServerPacket, 0x2b>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			Server::FieldAddItemPacket output0;

			int objectId_var0 = 0;
			Read<int>("objectId", handler, objectId_var0, "\t");

			output0.ObjectId = (Enum::ItemEntityId)objectId_var0;

			int itemId_var1 = 0;
			Read<int>("itemId", handler, itemId_var1, "\t");

			output0.ItemId = (Enum::ItemId)itemId_var1;

			int amount_var2 = 0;
			Read<int>("amount", handler, amount_var2, "\t");

			output0.Amount = (unsigned int)amount_var2;

			long long uid_var3 = 0;
			Read<long long>("uid", handler, uid_var3, "\t");
			Read<Vector3S>("position", handler, output0.Position, "\t");

			int ownerId_var5 = 0;
			Read<int>("ownerId", handler, ownerId_var5, "\t");

			output0.OwnerId = (Enum::CharacterId)ownerId_var5;

			unsigned char unknown_var6 = 0;
			Read<unsigned char>("unknown", handler, unknown_var6, "\t");

			int rarity_var7 = 0;
			Read<int>("rarity", handler, rarity_var7, "\t");

			ValidateValues(stream, "rarity", "\t", rarity_var7, (int)0, (int)1, (int)2, (int)3, (int)4, (int)5, (int)6);

			output0.Rarity = (Enum::Rarity)rarity_var7;

			short unknown_var8 = 0;
			Read<short>("unknown", handler, unknown_var8, "\t");

			bool unknown_var9 = false;
			Read<bool>("unknown", handler, unknown_var9, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var9, (bool)0, (bool)1);

			bool unknown_var10 = false;
			Read<bool>("unknown", handler, unknown_var10, "\t");

			ValidateValues(stream, "unknown", "\t", unknown_var10, (bool)0, (bool)1);

			if (itemId_var1 < 90000001 || itemId_var1 > 90000003)
			{

				{
					int amount_var11 = 0;
					Read<int>("amount", handler, amount_var11, "\t\t\t");

					output0.ItemData.Amount = (unsigned int)amount_var11;

					int unknown_var12 = 0;
					Read<int>("unknown", handler, unknown_var12, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var12, (int)18446744073709551615);

					int unknown_var13 = 0;
					Read<int>("unknown", handler, unknown_var13, "\t\t\t");

					long long creationTime_var14 = 0;
					Read<long long>("creationTime", handler, creationTime_var14, "\t\t\t");

					output0.ItemData.CreationTime = (unsigned long long)creationTime_var14;

					long long expirationTime_var15 = 0;
					Read<long long>("expirationTime", handler, expirationTime_var15, "\t\t\t");

					output0.ItemData.ExpirationTime = (unsigned long long)expirationTime_var15;

					long long unknown_var16 = 0;
					Read<long long>("unknown", handler, unknown_var16, "\t\t\t");

					int timesChanged_var17 = 0;
					Read<int>("timesChanged", handler, timesChanged_var17, "\t\t\t");

					output0.ItemData.TimesChanged = (unsigned int)timesChanged_var17;

					int remainingUses_var18 = 0;
					Read<int>("remainingUses", handler, remainingUses_var18, "\t\t\t");

					output0.ItemData.RemainingUses = (unsigned int)remainingUses_var18;

					bool isLocked_var19 = false;
					Read<bool>("isLocked", handler, isLocked_var19, "\t\t\t");

					ValidateValues(stream, "isLocked", "\t\t\t", isLocked_var19, (bool)0, (bool)1);

					output0.ItemData.IsLocked = (bool)isLocked_var19;

					long long unlockTime_var20 = 0;
					Read<long long>("unlockTime", handler, unlockTime_var20, "\t\t\t");

					output0.ItemData.UnlockTime = (bool)unlockTime_var20;

					short glamorForges_var21 = 0;
					Read<short>("glamorForges", handler, glamorForges_var21, "\t\t\t");

					output0.ItemData.GlamorForges = (bool)glamorForges_var21;

					unsigned char unknownBool_var22 = 0;
					Read<unsigned char>("unknownBool", handler, unknownBool_var22, "\t\t\t");

					ValidateValues(stream, "unknownBool", "\t\t\t", unknownBool_var22, (unsigned char)0);

					{

						{

							Color4I_BGRA dyeColorPrimary_var23;
							Read<Color4I_BGRA>("dyeColorPrimary", handler, dyeColorPrimary_var23, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Primary = (Color4I)dyeColorPrimary_var23;

							Color4I_BGRA dyeColorSecondary_var24;
							Read<Color4I_BGRA>("dyeColorSecondary", handler, dyeColorSecondary_var24, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Secondary = (Color4I)dyeColorSecondary_var24;

							Color4I_BGRA dyeColorTertiary_var25;
							Read<Color4I_BGRA>("dyeColorTertiary", handler, dyeColorTertiary_var25, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Tertiary = (Color4I)dyeColorTertiary_var25;

							int dyeColorIndex_var26 = 0;
							Read<int>("dyeColorIndex", handler, dyeColorIndex_var26, "\t\t\t\t\t");

							output0.ItemData.Customization.DyeColor.Index = (unsigned int)dyeColorIndex_var26;

							int unknown_var27 = 0;
							Read<int>("unknown", handler, unknown_var27, "\t\t\t\t\t");
						}

						short itemCategory_var28 = 0;

						itemCategory_var28 = handler.GetItemCategory(itemId_var1);

						if (itemCategory_var28 == 113)
						{

							{
								Read<Vector3S>("position1", handler, output0.ItemData.Customization.Cap.Position1, "\t\t\t\t\t\t");
								Read<Vector3S>("position2", handler, output0.ItemData.Customization.Cap.Position2, "\t\t\t\t\t\t");
								Read<Vector3S>("position3", handler, output0.ItemData.Customization.Cap.Position3, "\t\t\t\t\t\t");
								Read<Vector3S>("position4", handler, output0.ItemData.Customization.Cap.Position4, "\t\t\t\t\t\t");

								float unknown_var33 = 0;
								Read<float>("unknown", handler, unknown_var33, "\t\t\t\t\t\t");
							}
						}

						if (itemCategory_var28 == 102)
						{

							{
								Read<float>("backLength", handler, output0.ItemData.Customization.Hair.BackLength, "\t\t\t\t\t\t");
								Read<Vector3S>("backPosition1", handler, output0.ItemData.Customization.Hair.BackPosition1, "\t\t\t\t\t\t");
								Read<Vector3S>("backPosition2", handler, output0.ItemData.Customization.Hair.BackPosition2, "\t\t\t\t\t\t");
								Read<float>("frontLength", handler, output0.ItemData.Customization.Hair.FrontLength, "\t\t\t\t\t\t");
								Read<Vector3S>("frontPosition1", handler, output0.ItemData.Customization.Hair.FrontPosition1, "\t\t\t\t\t\t");
								Read<Vector3S>("frontPosition2", handler, output0.ItemData.Customization.Hair.FrontPosition2, "\t\t\t\t\t\t");
							}
						}

						if (itemCategory_var28 == 104)
						{

							{
								Read<Vector3S>("position1", handler, output0.ItemData.Customization.Decal.Position1, "\t\t\t\t\t\t");
								Read<Vector3S>("position2", handler, output0.ItemData.Customization.Decal.Position2, "\t\t\t\t\t\t");
								Read<Vector3S>("position3", handler, output0.ItemData.Customization.Decal.Position3, "\t\t\t\t\t\t");
								Read<Vector3S>("position4", handler, output0.ItemData.Customization.Decal.Position4, "\t\t\t\t\t\t");
							}
						}
					}

					{

						{

							short statCount_var44 = 0;
							Read<short>("statCount", handler, statCount_var44, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Static.Basic, statCount_var44);

							for (short i = 0; i < statCount_var44 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var45 = 0;
								Read<short>("type", handler, type_var45, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Static.Basic[i].Type = (Enum::StatAttributeBasic)type_var45;

								Read<int>("value", handler, output0.ItemData.Stats.Static.Basic[i].Value, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var44, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Static.Special, statCount_var44);

							for (short i = 0; i < statCount_var44 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var47 = 0;
								Read<short>("type", handler, type_var47, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Static.Special[i].Type = (Enum::StatAttributeSpecial)type_var47;

								Read<float>("rate", handler, output0.ItemData.Stats.Static.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var49 = 0;
						Read<int>("unknown", handler, unknown_var49, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var49, (int)0);

						{

							short statCount_var50 = 0;
							Read<short>("statCount", handler, statCount_var50, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Random.Basic, statCount_var50);

							for (short i = 0; i < statCount_var50 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var51 = 0;
								Read<short>("type", handler, type_var51, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Random.Basic[i].Type = (Enum::StatAttributeBasic)type_var51;

								Read<int>("value", handler, output0.ItemData.Stats.Random.Basic[i].Value, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var50, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.Stats.Random.Special, statCount_var50);

							for (short i = 0; i < statCount_var50 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var53 = 0;
								Read<short>("type", handler, type_var53, "\t\t\t\t\t\t");

								output0.ItemData.Stats.Random.Special[i].Type = (Enum::StatAttributeSpecial)type_var53;

								Read<float>("rate", handler, output0.ItemData.Stats.Random.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}

						int unknown_var55 = 0;
						Read<int>("unknown", handler, unknown_var55, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var55, (int)0);

						{

							short statCount_var56 = 0;
							Read<short>("statCount", handler, statCount_var56, "\t\t\t\t\t");

							for (short i = 0; i < statCount_var56 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var57 = 0;
								Read<short>("type", handler, type_var57, "\t\t\t\t\t\t");

								int value_var58 = 0;
								Read<int>("value", handler, value_var58, "\t\t\t\t\t\t");
							}

							Read<short>("statCount", handler, statCount_var56, "\t\t\t\t\t");

							for (short i = 0; i < statCount_var56 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var59 = 0;
								Read<short>("type", handler, type_var59, "\t\t\t\t\t\t");

								float rate_var60 = 0;
								Read<float>("rate", handler, rate_var60, "\t\t\t\t\t\t");
							}
						}

						int unknown_var61 = 0;
						Read<int>("unknown", handler, unknown_var61, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var61, (int)0);
					}

					{

						int enchantLevel_var62 = 0;
						Read<int>("enchantLevel", handler, enchantLevel_var62, "\t\t\t\t");

						output0.ItemData.Enchantment.Level = (unsigned int)enchantLevel_var62;

						int enchantExp_var63 = 0;
						Read<int>("enchantExp", handler, enchantExp_var63, "\t\t\t\t");

						output0.ItemData.Enchantment.EnchantExp = (unsigned int)enchantExp_var63;

						Read<unsigned char>("enchantCharges", handler, output0.ItemData.Enchantment.EnchantCharges, "\t\t\t\t");

						long long unknown_var65 = 0;
						Read<long long>("unknown", handler, unknown_var65, "\t\t\t\t");

						int unknown_var66 = 0;
						Read<int>("unknown", handler, unknown_var66, "\t\t\t\t");

						int unknown_var67 = 0;
						Read<int>("unknown", handler, unknown_var67, "\t\t\t\t");
						Read<bool>("canRepackage", handler, output0.ItemData.Enchantment.CanRepackage, "\t\t\t\t");

						ValidateValues(stream, "canRepackage", "\t\t\t\t", output0.ItemData.Enchantment.CanRepackage, (bool)0, (bool)1);

						int charges_var69 = 0;
						Read<int>("charges", handler, charges_var69, "\t\t\t\t");

						output0.ItemData.Enchantment.Charges = (unsigned int)charges_var69;

						unsigned char basicStatCount_var70 = 0;
						Read<unsigned char>("basicStatCount", handler, basicStatCount_var70, "\t\t\t\t");

						ResizeVector(handler, output0.ItemData.Enchantment.Basic, basicStatCount_var70);

						for (unsigned char i = 0; i < basicStatCount_var70 && !handler.PacketStream.HasRecentlyFailed; ++i)
						{
							int type_var71 = 0;
							Read<int>("type", handler, type_var71, "\t\t\t\t\t");

							output0.ItemData.Enchantment.Basic[i].Type = (Enum::StatAttributeBasic)type_var71;

							Read<int>("value", handler, output0.ItemData.Enchantment.Basic[i].Value, "\t\t\t\t\t");
						}
					}

					{

						int limitBreakLevel_var73 = 0;
						Read<int>("limitBreakLevel", handler, limitBreakLevel_var73, "\t\t\t\t");

						output0.ItemData.LimitBreak.Level = (unsigned int)limitBreakLevel_var73;

						{

							int statCount_var74 = 0;
							Read<int>("statCount", handler, statCount_var74, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.LimitBreak.Stats.Basic, statCount_var74);

							for (int i = 0; i < statCount_var74 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var75 = 0;
								Read<short>("type", handler, type_var75, "\t\t\t\t\t\t");

								output0.ItemData.LimitBreak.Stats.Basic[i].Type = (Enum::StatAttributeBasic)type_var75;

								Read<int>("value", handler, output0.ItemData.LimitBreak.Stats.Basic[i].Value, "\t\t\t\t\t\t");
							}

							Read<int>("statCount", handler, statCount_var74, "\t\t\t\t\t");

							ResizeVector(handler, output0.ItemData.LimitBreak.Stats.Special, statCount_var74);

							for (int i = 0; i < statCount_var74 && !handler.PacketStream.HasRecentlyFailed; ++i)
							{
								short type_var77 = 0;
								Read<short>("type", handler, type_var77, "\t\t\t\t\t\t");

								output0.ItemData.LimitBreak.Stats.Special[i].Type = (Enum::StatAttributeSpecial)type_var77;

								Read<float>("rate", handler, output0.ItemData.LimitBreak.Stats.Special[i].Rate, "\t\t\t\t\t\t");
							}
						}
					}

					unsigned char extraDataType_var79 = 0;

					extraDataType_var79 = handler.GetItemExtraDataType(itemId_var1);

					ValidateValues(stream, "extraDataType", "\t\t\t", extraDataType_var79, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

					if (extraDataType_var79 == 1)
					{

						{
							long long unknown_var80 = 0;
							Read<long long>("unknown", handler, unknown_var80, "\t\t\t\t\t");
							Read<std::wstring>("fileName", handler, output0.ItemData.Template.FileName, "\t\t\t\t\t");
							Read<std::wstring>("name", handler, output0.ItemData.Template.Name, "\t\t\t\t\t");

							unsigned char unknown_var83 = 0;
							Read<unsigned char>("unknown", handler, unknown_var83, "\t\t\t\t\t");

							int unknown_var84 = 0;
							Read<int>("unknown", handler, unknown_var84, "\t\t\t\t\t");

							long long accountId_var85 = 0;
							Read<long long>("accountId", handler, accountId_var85, "\t\t\t\t\t");

							output0.ItemData.Template.AccountId = (Enum::AccountId)accountId_var85;

							long long characterId_var86 = 0;
							Read<long long>("characterId", handler, characterId_var86, "\t\t\t\t\t");

							output0.ItemData.Template.CharacterId = (Enum::CharacterId)characterId_var86;

							Read<std::wstring>("author", handler, output0.ItemData.Template.Author, "\t\t\t\t\t");

							long long creationTime_var88 = 0;
							Read<long long>("creationTime", handler, creationTime_var88, "\t\t\t\t\t");

							output0.ItemData.Template.CreationTime = (unsigned long long)creationTime_var88;

							Read<std::wstring>("url", handler, output0.ItemData.Template.Url, "\t\t\t\t\t");

							unsigned char unknown_var90 = 0;
							Read<unsigned char>("unknown", handler, unknown_var90, "\t\t\t\t\t");
						}

						{

							long long unknown_var91 = 0;
							Read<long long>("unknown", handler, unknown_var91, "\t\t\t\t\t");

							int unknown_var92 = 0;
							Read<int>("unknown", handler, unknown_var92, "\t\t\t\t\t");

							int unknown_var93 = 0;
							Read<int>("unknown", handler, unknown_var93, "\t\t\t\t\t");

							int unknown_var94 = 0;
							Read<int>("unknown", handler, unknown_var94, "\t\t\t\t\t");

							long long unknown_var95 = 0;
							Read<long long>("unknown", handler, unknown_var95, "\t\t\t\t\t");

							int unknown_var96 = 0;
							Read<int>("unknown", handler, unknown_var96, "\t\t\t\t\t");

							long long unknown_var97 = 0;
							Read<long long>("unknown", handler, unknown_var97, "\t\t\t\t\t");

							long long unknown_var98 = 0;
							Read<long long>("unknown", handler, unknown_var98, "\t\t\t\t\t");

							std::wstring unknown_var99;
							Read<std::wstring>("unknown", handler, unknown_var99, "\t\t\t\t\t");
						}
					}

					if (extraDataType_var79 == 2)
					{

						{
							Read<std::wstring>("name", handler, output0.ItemData.Pet.Name, "\t\t\t\t\t");

							long long exp_var101 = 0;
							Read<long long>("exp", handler, exp_var101, "\t\t\t\t\t");

							output0.ItemData.Pet.Exp = (unsigned long long)exp_var101;

							int evolvePoints_var102 = 0;
							Read<int>("evolvePoints", handler, evolvePoints_var102, "\t\t\t\t\t");

							output0.ItemData.Pet.EvolvePoints = (unsigned int)evolvePoints_var102;

							int level_var103 = 0;
							Read<int>("level", handler, level_var103, "\t\t\t\t\t");

							output0.ItemData.Pet.Level = (unsigned int)level_var103;

							Read<bool>("hasItems", handler, output0.ItemData.Pet.HasItems, "\t\t\t\t\t");

							ValidateValues(stream, "hasItems", "\t\t\t\t\t", output0.ItemData.Pet.HasItems, (bool)0, (bool)1);
						}
					}

					if (extraDataType_var79 == 3)
					{

						{
							int length_var105 = 0;
							Read<int>("length", handler, length_var105, "\t\t\t\t\t");

							output0.ItemData.Music.Length = (unsigned int)length_var105;

							int instrument_var106 = 0;
							Read<int>("instrument", handler, instrument_var106, "\t\t\t\t\t");

							output0.ItemData.Music.Instrument = (unsigned int)instrument_var106;

							Read<std::wstring>("title", handler, output0.ItemData.Music.Title, "\t\t\t\t\t");
							Read<std::wstring>("author", handler, output0.ItemData.Music.Author, "\t\t\t\t\t");

							int unknown_var109 = 0;
							Read<int>("unknown", handler, unknown_var109, "\t\t\t\t\t");

							ValidateValues(stream, "unknown", "\t\t\t\t\t", unknown_var109, (int)1);

							long long authorId_var110 = 0;
							Read<long long>("authorId", handler, authorId_var110, "\t\t\t\t\t");

							output0.ItemData.Music.AuthorId = (Enum::CharacterId)authorId_var110;

							Read<bool>("isLocked", handler, output0.ItemData.Music.IsLocked, "\t\t\t\t\t");

							ValidateValues(stream, "isLocked", "\t\t\t\t\t", output0.ItemData.Music.IsLocked, (bool)0, (bool)1);

							long long unknown_var112 = 0;
							Read<long long>("unknown", handler, unknown_var112, "\t\t\t\t\t");

							long long unknown_var113 = 0;
							Read<long long>("unknown", handler, unknown_var113, "\t\t\t\t\t");
						}
					}

					if (extraDataType_var79 == 4)
					{

						{
							unsigned char unknown_var114 = 0;
							Read<unsigned char>("unknown", handler, unknown_var114, "\t\t\t\t\t");

							ValidateValues(stream, "unknown", "\t\t\t\t\t", unknown_var114, (unsigned char)1);

							unsigned char type_var115 = 0;
							Read<unsigned char>("type", handler, type_var115, "\t\t\t\t\t");

							ValidateValues(stream, "type", "\t\t\t\t\t", type_var115, (unsigned char)1, (unsigned char)11);

							output0.ItemData.Badge.Type = (Enum::BadgeType)type_var115;

							int id_var116 = 0;
							Read<int>("id", handler, id_var116, "\t\t\t\t\t");

							output0.ItemData.Badge.BadgeId = (Enum::BadgeId)id_var116;

							if (type_var115 == 1)
							{
								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[0], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[0], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[1], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[1], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[2], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[2], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[3], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[3], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[4], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[4], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[5], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[5], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[6], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[6], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[7], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[7], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[8], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[8], (bool)0, (bool)1);

								Read<bool>("transparency", handler, output0.ItemData.Badge.Transparency[9], "\t\t\t\t\t\t");

								ValidateValues(stream, "transparency", "\t\t\t\t\t\t", output0.ItemData.Badge.Transparency[9], (bool)0, (bool)1);
							}

							if (type_var115 == 11)
							{
								int petSkinId_var127 = 0;
								Read<int>("petSkinId", handler, petSkinId_var127, "\t\t\t\t\t\t");

								output0.ItemData.Badge.PetSkinId = (Enum::PetId)petSkinId_var127;
							}
						}
					}

					{

						int transferFlags_var128 = 0;
						Read<int>("transferFlags", handler, transferFlags_var128, "\t\t\t\t");

						output0.ItemData.ItemTransfer.TransferFlags = (unsigned int)transferFlags_var128;

						bool unknown_var129 = false;
						Read<bool>("unknown", handler, unknown_var129, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var129, (bool)0, (bool)1);

						int remainingTrades_var130 = 0;
						Read<int>("remainingTrades", handler, remainingTrades_var130, "\t\t\t\t");

						output0.ItemData.ItemTransfer.RemainingTrades = (unsigned int)remainingTrades_var130;

						int remainingPackages_var131 = 0;
						Read<int>("remainingPackages", handler, remainingPackages_var131, "\t\t\t\t");

						output0.ItemData.ItemTransfer.RemainingPackages = (unsigned int)remainingPackages_var131;

						unsigned char unknown_var132 = 0;
						Read<unsigned char>("unknown", handler, unknown_var132, "\t\t\t\t");

						bool unknown_var133 = false;
						Read<bool>("unknown", handler, unknown_var133, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var133, (bool)0, (bool)1);

						bool isBound_var134 = false;
						Read<bool>("isBound", handler, isBound_var134, "\t\t\t\t");

						ValidateValues(stream, "isBound", "\t\t\t\t", isBound_var134, (bool)0, (bool)1);

						output0.ItemData.ItemTransfer.IsBound = (bool)isBound_var134;

						if (isBound_var134)
						{

							{
								long long characterId_var135 = 0;
								Read<long long>("characterId", handler, characterId_var135, "\t\t\t\t\t\t");

								std::wstring name_var136;
								Read<std::wstring>("name", handler, name_var136, "\t\t\t\t\t\t");
							}
						}
					}

					{
						Read<unsigned char>("maxSlots", handler, output0.ItemData.ItemSocket.MaxSlots, "\t\t\t\t");

						unsigned char unlockedSlots_var138 = 0;
						Read<unsigned char>("unlockedSlots", handler, unlockedSlots_var138, "\t\t\t\t");

						output0.ItemData.ItemSocket.UnlockedSlots = (unsigned char)unlockedSlots_var138;

						ResizeVector(handler, output0.ItemData.ItemSocket.Sockets, unlockedSlots_var138);

						for (unsigned char i = 0; i < unlockedSlots_var138 && !handler.PacketStream.HasRecentlyFailed; ++i)
						{
							bool hasGem_var139 = false;
							Read<bool>("hasGem", handler, hasGem_var139, "\t\t\t\t\t");

							ValidateValues(stream, "hasGem", "\t\t\t\t\t", hasGem_var139, (bool)0, (bool)1);

							output0.ItemData.ItemSocket.Sockets[i].HasGem = (bool)hasGem_var139;

							if (hasGem_var139)
							{

								{
									int itemId_var140 = 0;
									Read<int>("itemId", handler, itemId_var140, "\t\t\t\t\t\t\t");

									output0.ItemData.ItemSocket.Sockets[i].Gem.ItemId = (Enum::ItemId)itemId_var140;

									bool isBound_var141 = false;
									Read<bool>("isBound", handler, isBound_var141, "\t\t\t\t\t\t\t");

									ValidateValues(stream, "isBound", "\t\t\t\t\t\t\t", isBound_var141, (bool)0, (bool)1);

									output0.ItemData.ItemSocket.Sockets[i].Gem.IsBound = (bool)isBound_var141;

									if (isBound_var141)
									{

										{
											long long characterId_var142 = 0;
											Read<long long>("characterId", handler, characterId_var142, "\t\t\t\t\t\t\t\t\t");

											std::wstring name_var143;
											Read<std::wstring>("name", handler, name_var143, "\t\t\t\t\t\t\t\t\t");
										}
									}
									Read<bool>("isLocked", handler, output0.ItemData.ItemSocket.Sockets[i].Gem.IsLocked, "\t\t\t\t\t\t\t");

									ValidateValues(stream, "isLocked", "\t\t\t\t\t\t\t", output0.ItemData.ItemSocket.Sockets[i].Gem.IsLocked, (bool)0, (bool)1);

									if (isLocked_var19)
									{
										unsigned char unknown_var145 = 0;
										Read<unsigned char>("unknown", handler, unknown_var145, "\t\t\t\t\t\t\t\t");

										long long unlockTime_var146 = 0;
										Read<long long>("unlockTime", handler, unlockTime_var146, "\t\t\t\t\t\t\t\t");

										output0.ItemData.ItemSocket.Sockets[i].Gem.UnlockTime = (unsigned long long)unlockTime_var146;
									}
								}
							}
						}
					}

					{

						long long characterId_var147 = 0;
						Read<long long>("characterId", handler, characterId_var147, "\t\t\t\t");

						output0.ItemData.ItemCouple.CharacterId = (Enum::CharacterId)characterId_var147;

						if (characterId_var147 != 0)
						{
							Read<std::wstring>("name", handler, output0.ItemData.ItemCouple.Name, "\t\t\t\t\t");
							Read<bool>("isCreator", handler, output0.ItemData.ItemCouple.IsCreator, "\t\t\t\t\t");

							ValidateValues(stream, "isCreator", "\t\t\t\t\t", output0.ItemData.ItemCouple.IsCreator, (bool)0, (bool)1);
						}
					}

					{

						long long characterId_var150 = 0;
						Read<long long>("characterId", handler, characterId_var150, "\t\t\t\t");

						std::wstring name_var151;
						Read<std::wstring>("name", handler, name_var151, "\t\t\t\t");
					}
				}
			}

			if (stream.Succeeded())
			{
				handler.PacketParsed<Server::FieldAddItemPacket>(output0);

				return;
			}
		}

		template <>
		void ParsePacket<2503, ClientPacket, 0x20>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

			if (mode_var0 == 0)
			{
				Client::SkillCastPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", handler, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				Read<int>("serverTick", handler, output0.ServerTick, "\t\t");

				int skillId_var3 = 0;
				Read<int>("skillId", handler, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				short skillLevel_var4 = 0;
				Read<short>("skillLevel", handler, skillLevel_var4, "\t\t");

				output0.SkillLevel = (Enum::SkillLevel)skillLevel_var4;

				Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t");
				Read<Vector3S>("position", handler, output0.Position, "\t\t");
				Read<Vector3S>("direction", handler, output0.Direction, "\t\t");
				Read<Vector3S>("rotation", handler, output0.Rotation, "\t\t");

				float unknown_var9 = 0;
				Read<float>("unknown", handler, unknown_var9, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var9, (float)0);

				Read<int>("clientTick", handler, output0.ClientTick, "\t\t");

				bool unknown_var11 = false;
				Read<bool>("unknown", handler, unknown_var11, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var11, (bool)0, (bool)1);

				long long unknown_var12 = 0;
				Read<long long>("unknown", handler, unknown_var12, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var12, (long long)0);

				long long unknown_var13 = 0;
				Read<long long>("unknown", handler, unknown_var13, "\t\t");

				bool flag_var14 = false;
				Read<bool>("flag", handler, flag_var14, "\t\t");

				ValidateValues(stream, "flag", "\t\t", flag_var14, (bool)0, (bool)1);

				output0.Flag = (bool)flag_var14;

				if (flag_var14)
				{
					int unknown_var15 = 0;
					Read<int>("unknown", handler, unknown_var15, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var15, (int)0);

					std::string unknown_var16;
					Read<std::string>("unknown", handler, unknown_var16, "\t\t\t");
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCastPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				unsigned char damageMode_var17 = 0;
				Read<unsigned char>("damageMode", handler, damageMode_var17, "\t\t");

				ValidateValues(stream, "damageMode", "\t\t", damageMode_var17, (unsigned char)0, (unsigned char)1, (unsigned char)2);

				if (damageMode_var17 == 0)
				{
					Client::SkillSyncDamagePacket output1;

					long long skillSn_var18 = 0;
					Read<long long>("skillSn", handler, skillSn_var18, "\t\t\t");

					output1.SkillSn = (Enum::SkillSn)skillSn_var18;

					Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t\t");
					Read<Vector3S>("position", handler, output1.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output1.Rotation, "\t\t\t");

					unsigned char count_var22 = 0;
					Read<unsigned char>("count", handler, count_var22, "\t\t\t");

					int unknown_var23 = 0;
					Read<int>("unknown", handler, unknown_var23, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var23, (int)0);

					ResizeVector(handler, output1.Projectiles, count_var22);

					for (unsigned char i = 0; i < count_var22 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& projectile_array0 = output1.Projectiles[i];

						int attackCount_var24 = 0;
						Read<int>("attackCount", handler, attackCount_var24, "\t\t\t\t");

						int sourceId_var25 = 0;
						Read<int>("sourceId", handler, sourceId_var25, "\t\t\t\t");

						int targetId_var26 = 0;
						Read<int>("targetId", handler, targetId_var26, "\t\t\t\t");

						projectile_array0.TargetId = (Enum::ActorId)targetId_var26;

						Read<unsigned char>("index", handler, projectile_array0.Index, "\t\t\t\t");

						bool moreTargets_var28 = false;
						Read<bool>("moreTargets", handler, moreTargets_var28, "\t\t\t\t");

						ValidateValues(stream, "moreTargets", "\t\t\t\t", moreTargets_var28, (bool)0, (bool)1);

						size_t j = 0;

						while (moreTargets_var28 && !handler.PacketStream.HasRecentlyFailed)
						{
							projectile_array0.ChainTargets.push_back({});

							auto& nextTarget_array1 = projectile_array0.ChainTargets[j];

							int attackCount_var29 = 0;
							Read<int>("attackCount", handler, attackCount_var29, "\t\t\t\t\t");

							int sourceId_var30 = 0;
							Read<int>("sourceId", handler, sourceId_var30, "\t\t\t\t\t");

							int targetId_var31 = 0;
							Read<int>("targetId", handler, targetId_var31, "\t\t\t\t\t");

							nextTarget_array1.TargetId = (Enum::ActorId)targetId_var31;

							Read<unsigned char>("index", handler, nextTarget_array1.Index, "\t\t\t\t\t");

							unsigned char unknown_var33 = 0;
							Read<unsigned char>("unknown", handler, unknown_var33, "\t\t\t\t\t");

							Read<bool>("moreTargets", handler, moreTargets_var28, "\t\t\t\t\t");

							ValidateValues(stream, "moreTargets", "\t\t\t\t\t", moreTargets_var28, (bool)0, (bool)1);

							++j;
						}
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillSyncDamagePacket>(output1);

						return;
					}
				}

				if (damageMode_var17 == 1)
				{
					Client::SkillDamagePacket output2;

					long long skillSn_var34 = 0;
					Read<long long>("skillSn", handler, skillSn_var34, "\t\t\t");

					output2.SkillSn = (Enum::SkillSn)skillSn_var34;

					int attackCounter_var35 = 0;
					Read<int>("attackCounter", handler, attackCounter_var35, "\t\t\t");

					int sourceId_var36 = 0;
					Read<int>("sourceId", handler, sourceId_var36, "\t\t\t");
					Read<Vector3S>("position", handler, output2.Position, "\t\t\t");
					Read<Vector3S>("hitPoint", handler, output2.HitPoint, "\t\t\t");
					Read<Vector3S>("rotation", handler, output2.Rotation, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output2.AttackPoint, "\t\t\t");

					unsigned char count_var41 = 0;
					Read<unsigned char>("count", handler, count_var41, "\t\t\t");

					int unknown_var42 = 0;
					Read<int>("unknown", handler, unknown_var42, "\t\t\t");

					ValidateValues(stream, "unknown", "\t\t\t", unknown_var42, (int)0);

					ResizeVector(handler, output2.Hits, count_var41);

					for (unsigned char i = 0; i < count_var41 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						auto& hitActor_array2 = output2.Hits[i];

						int entityId_var43 = 0;
						Read<int>("entityId", handler, entityId_var43, "\t\t\t\t");

						hitActor_array2.EntityId = (Enum::ActorId)entityId_var43;

						unsigned char unknown_var44 = 0;
						Read<unsigned char>("unknown", handler, unknown_var44, "\t\t\t\t");

						ValidateValues(stream, "unknown", "\t\t\t\t", unknown_var44, (unsigned char)0);
					}

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillDamagePacket>(output2);

						return;
					}
				}

				if (damageMode_var17 == 2)
				{
					Client::SkillRegionSkillPacket output3;

					long long skillSn_var45 = 0;
					Read<long long>("skillSn", handler, skillSn_var45, "\t\t\t");

					output3.SkillSn = (Enum::SkillSn)skillSn_var45;

					Read<unsigned char>("attackPoint", handler, output3.AttackPoint, "\t\t\t");

					int unknown_var47 = 0;
					Read<int>("unknown", handler, unknown_var47, "\t\t\t");
					Read<int>("attackCounter", handler, output3.AttackCounter, "\t\t\t");
					Read<Vector3S>("position", handler, output3.Position, "\t\t\t");
					Read<Vector3S>("rotation", handler, output3.Rotation, "\t\t\t");

					if (stream.Succeeded())
					{
						handler.PacketParsed<Client::SkillRegionSkillPacket>(output3);

						return;
					}
				}
			}

			if (mode_var0 == 2)
			{
				Client::SkillSyncPacket output4;

				long long skillSn_var51 = 0;
				Read<long long>("skillSn", handler, skillSn_var51, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var51;

				int skillId_var52 = 0;
				Read<int>("skillId", handler, skillId_var52, "\t\t");

				output4.SkillId = (Enum::SkillId)skillId_var52;

				short skillLevel_var53 = 0;
				Read<short>("skillLevel", handler, skillLevel_var53, "\t\t");

				output4.SkillLevel = (Enum::SkillLevel)skillLevel_var53;

				Read<unsigned char>("motionPoint", handler, output4.MotionPoint, "\t\t");
				Read<Vector3S>("position", handler, output4.Position, "\t\t");

				Vector3S unknown_var56;
				Read<Vector3S>("unknown", handler, unknown_var56, "\t\t");
				Read<Vector3S>("rotation", handler, output4.Rotation, "\t\t");

				Vector3S unknown_var58;
				Read<Vector3S>("unknown", handler, unknown_var58, "\t\t");

				bool unknown_var59 = false;
				Read<bool>("unknown", handler, unknown_var59, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var59, (bool)0, (bool)1);

				int unknown_var60 = 0;
				Read<int>("unknown", handler, unknown_var60, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var60, (int)0);

				unsigned char unknown_var61 = 0;
				Read<unsigned char>("unknown", handler, unknown_var61, "\t\t");

				ValidateValues(stream, "unknown", "\t\t", unknown_var61, (unsigned char)0);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Client::SkillSyncTickPacket output5;

				long long skillSn_var62 = 0;
				Read<long long>("skillSn", handler, skillSn_var62, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var62;

				Read<int>("serverTick", handler, output5.ServerTick, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillSyncTickPacket>(output5);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Client::SkillCancelPacket output6;

				long long skillSn_var64 = 0;
				Read<long long>("skillSn", handler, skillSn_var64, "\t\t");

				output6.SkillSn = (Enum::SkillSn)skillSn_var64;

				if (stream.Succeeded())
				{
					handler.PacketParsed<Client::SkillCancelPacket>(output6);

					return;
				}
			}
		}

		template <>
		void ParsePacket<2503, ServerPacket, 0x3d>(PacketHandler& handler)
		{
			using namespace ParserUtils::Packets;

			ParserUtils::DataStream& stream = handler.PacketStream;

			unsigned char mode_var0 = 0;
			Read<unsigned char>("mode", handler, mode_var0, "\t");

			ValidateValues(stream, "mode", "\t", mode_var0, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)3, (unsigned char)4, (unsigned char)5, (unsigned char)6, (unsigned char)7);

			if (mode_var0 == 0)
			{
				Server::SkillDamageSyncPacket output0;

				long long skillSn_var1 = 0;
				Read<long long>("skillSn", handler, skillSn_var1, "\t\t");

				output0.SkillSn = (Enum::SkillSn)skillSn_var1;

				int casterId_var2 = 0;
				Read<int>("casterId", handler, casterId_var2, "\t\t");

				output0.CasterId = (Enum::ActorId)casterId_var2;

				unsigned int skillId_var3 = 0;
				Read<unsigned int>("skillId", handler, skillId_var3, "\t\t");

				output0.SkillId = (Enum::SkillId)skillId_var3;

				if (skillId_var3 == 0)
				{
					unsigned char unknown_var4 = 0;
					Read<unsigned char>("unknown", handler, unknown_var4, "\t\t\t");
				}

				if (skillId_var3 != 0)
				{
					unsigned short skillLevel_var5 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var5, "\t\t\t");

					output0.SkillLevel = (Enum::SkillLevel)skillLevel_var5;

					Read<unsigned char>("motionPoint", handler, output0.MotionPoint, "\t\t\t");
					Read<unsigned char>("attackPoint", handler, output0.AttackPoint, "\t\t\t");

					short posX_var8 = 0;
					Read<short>("posX", handler, posX_var8, "\t\t\t");

					short posY_var9 = 0;
					Read<short>("posY", handler, posY_var9, "\t\t\t");

					short posZ_var10 = 0;
					Read<short>("posZ", handler, posZ_var10, "\t\t\t");
					Read<Vector3S>("direction", handler, output0.Direction, "\t\t\t");
					Read<bool>("isChaining", handler, output0.IsChaining, "\t\t\t");

					ValidateValues(stream, "isChaining", "\t\t\t", output0.IsChaining, (bool)0, (bool)1);

					unsigned char count_var13 = 0;
					Read<unsigned char>("count", handler, count_var13, "\t\t\t");

					ResizeVector(handler, output0.Hits, count_var13);

					for (unsigned char i = 0; i < count_var13 && !handler.PacketStream.HasRecentlyFailed; ++i)
					{
						long long hitId_var14 = 0;
						Read<long long>("hitId", handler, hitId_var14, "\t\t\t\t");

						int attackCount_var15 = 0;
						Read<int>("attackCount", handler, attackCount_var15, "\t\t\t\t");

						int casterId_var16 = 0;
						Read<int>("casterId", handler, casterId_var16, "\t\t\t\t");

						int targetId_var17 = 0;
						Read<int>("targetId", handler, targetId_var17, "\t\t\t\t");

						output0.Hits[i].TargetId = (Enum::ActorId)targetId_var17;

						Read<short>("animation", handler, output0.Hits[i].Animation, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageSyncPacket>(output0);

					return;
				}
			}

			if (mode_var0 == 1)
			{
				Server::SkillDamagePacket output1;

				long long skillSn_var19 = 0;
				Read<long long>("skillSn", handler, skillSn_var19, "\t\t");

				output1.SkillSn = (Enum::SkillSn)skillSn_var19;

				long long hitId_var20 = 0;
				Read<long long>("hitId", handler, hitId_var20, "\t\t");

				int casterId_var21 = 0;
				Read<int>("casterId", handler, casterId_var21, "\t\t");

				output1.CasterId = (Enum::ActorId)casterId_var21;

				unsigned int skillId_var22 = 0;
				Read<unsigned int>("skillId", handler, skillId_var22, "\t\t");

				output1.SkillId = (Enum::SkillId)skillId_var22;

				unsigned short skillLevel_var23 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var23, "\t\t");

				output1.SkillLevel = (Enum::SkillLevel)skillLevel_var23;

				Read<unsigned char>("motionPoint", handler, output1.MotionPoint, "\t\t");
				Read<unsigned char>("attackPoint", handler, output1.AttackPoint, "\t\t");

				short posX_var26 = 0;
				Read<short>("posX", handler, posX_var26, "\t\t");

				short posY_var27 = 0;
				Read<short>("posY", handler, posY_var27, "\t\t");

				short posZ_var28 = 0;
				Read<short>("posZ", handler, posZ_var28, "\t\t");

				short dirX_var29 = 0;
				Read<short>("dirX", handler, dirX_var29, "\t\t");

				short dirY_var30 = 0;
				Read<short>("dirY", handler, dirY_var30, "\t\t");

				short dirZ_var31 = 0;
				Read<short>("dirZ", handler, dirZ_var31, "\t\t");

				unsigned char count_var32 = 0;
				Read<unsigned char>("count", handler, count_var32, "\t\t");

				ResizeVector(handler, output1.DamagedTargets, count_var32);

				for (unsigned char i = 0; i < count_var32 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var33 = 0;
					Read<int>("targetId", handler, targetId_var33, "\t\t\t");

					output1.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var33;

					unsigned char damageCount_var34 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var34, "\t\t\t");

					ResizeVector(handler, output1.DamagedTargets[i].Damages, damageCount_var34);

					for (unsigned char j = 0; j < damageCount_var34 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var35 = 0;
						Read<unsigned char>("hitType", handler, hitType_var35, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var35, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output1.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var35;

						Read<long long>("damage", handler, output1.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamagePacket>(output1);

					return;
				}
			}

			if (mode_var0 == 3)
			{
				Server::SkillDamageDotPacket output2;

				int casterId_var37 = 0;
				Read<int>("casterId", handler, casterId_var37, "\t\t");

				output2.CasterId = (Enum::ActorId)casterId_var37;

				int targetId_var38 = 0;
				Read<int>("targetId", handler, targetId_var38, "\t\t");

				output2.TargetId = (Enum::ActorId)targetId_var38;

				Read<int>("serverTick", handler, output2.ServerTick, "\t\t");

				unsigned char hitType_var40 = 0;
				Read<unsigned char>("hitType", handler, hitType_var40, "\t\t");

				ValidateValues(stream, "hitType", "\t\t", hitType_var40, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

				output2.HitType = (Enum::HitType)hitType_var40;

				Read<long long>("damage", handler, output2.Damage, "\t\t");

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageDotPacket>(output2);

					return;
				}
			}

			if (mode_var0 == 4)
			{
				Server::SkillDamageHealPacket output3;

				int casterId_var42 = 0;
				Read<int>("casterId", handler, casterId_var42, "\t\t");

				output3.CasterId = (Enum::ActorId)casterId_var42;

				int targetId_var43 = 0;
				Read<int>("targetId", handler, targetId_var43, "\t\t");

				output3.TargetId = (Enum::ActorId)targetId_var43;

				Read<int>("serverTick", handler, output3.ServerTick, "\t\t");
				Read<int>("hpAmount", handler, output3.HpAmount, "\t\t");
				Read<int>("spAmount", handler, output3.SpAmount, "\t\t");
				Read<int>("epAmount", handler, output3.EpAmount, "\t\t");
				Read<bool>("isVisible", handler, output3.IsVisible, "\t\t");

				ValidateValues(stream, "isVisible", "\t\t", output3.IsVisible, (bool)0, (bool)1);

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageHealPacket>(output3);

					return;
				}
			}

			if (mode_var0 == 5)
			{
				Server::SkillDamageRegionPacket output4;

				long long skillSn_var49 = 0;
				Read<long long>("skillSn", handler, skillSn_var49, "\t\t");

				output4.SkillSn = (Enum::SkillSn)skillSn_var49;

				int casterId_var50 = 0;
				Read<int>("casterId", handler, casterId_var50, "\t\t");

				output4.CasterId = (Enum::ActorId)casterId_var50;

				int regionSkillObjectId_var51 = 0;
				Read<int>("regionSkillObjectId", handler, regionSkillObjectId_var51, "\t\t");

				output4.RegionSkillObjectId = (Enum::ActorId)regionSkillObjectId_var51;

				Read<unsigned char>("attackPoint", handler, output4.AttackPoint, "\t\t");

				unsigned char count_var53 = 0;
				Read<unsigned char>("count", handler, count_var53, "\t\t");

				ResizeVector(handler, output4.DamagedTargets, count_var53);

				for (unsigned char i = 0; i < count_var53 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var54 = 0;
					Read<int>("targetId", handler, targetId_var54, "\t\t\t");

					output4.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var54;

					unsigned char damageCount_var55 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var55, "\t\t\t");

					short posX_var56 = 0;
					Read<short>("posX", handler, posX_var56, "\t\t\t");

					short posY_var57 = 0;
					Read<short>("posY", handler, posY_var57, "\t\t\t");

					short posZ_var58 = 0;
					Read<short>("posZ", handler, posZ_var58, "\t\t\t");
					Read<Vector3S>("direction", handler, output4.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output4.DamagedTargets[i].Damages, damageCount_var55);

					for (unsigned char j = 0; j < damageCount_var55 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var60 = 0;
						Read<unsigned char>("hitType", handler, hitType_var60, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var60, (unsigned char)0, (unsigned char)8, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output4.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var60;

						Read<long long>("damage", handler, output4.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageRegionPacket>(output4);

					return;
				}
			}

			if (mode_var0 == 6)
			{
				Server::SkillDamageTilePacket output5;

				long long skillSn_var62 = 0;
				Read<long long>("skillSn", handler, skillSn_var62, "\t\t");

				output5.SkillSn = (Enum::SkillSn)skillSn_var62;

				unsigned int skillId_var63 = 0;
				Read<unsigned int>("skillId", handler, skillId_var63, "\t\t");

				output5.SkillId = (Enum::SkillId)skillId_var63;

				unsigned short skillLevel_var64 = 0;
				Read<unsigned short>("skillLevel", handler, skillLevel_var64, "\t\t");

				output5.SkillLevel = (Enum::SkillLevel)skillLevel_var64;

				unsigned char count_var65 = 0;
				Read<unsigned char>("count", handler, count_var65, "\t\t");

				ResizeVector(handler, output5.DamagedTargets, count_var65);

				for (unsigned char i = 0; i < count_var65 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int targetId_var66 = 0;
					Read<int>("targetId", handler, targetId_var66, "\t\t\t");

					output5.DamagedTargets[i].TargetId = (Enum::ActorId)targetId_var66;

					unsigned char damageCount_var67 = 0;
					Read<unsigned char>("damageCount", handler, damageCount_var67, "\t\t\t");

					short posX_var68 = 0;
					Read<short>("posX", handler, posX_var68, "\t\t\t");

					short posY_var69 = 0;
					Read<short>("posY", handler, posY_var69, "\t\t\t");

					short posZ_var70 = 0;
					Read<short>("posZ", handler, posZ_var70, "\t\t\t");
					Read<Vector3S>("direction", handler, output5.DamagedTargets[i].Direction, "\t\t\t");

					ResizeVector(handler, output5.DamagedTargets[i].Damages, damageCount_var67);

					for (unsigned char j = 0; j < damageCount_var67 && !handler.PacketStream.HasRecentlyFailed; ++j)
					{
						unsigned char hitType_var72 = 0;
						Read<unsigned char>("hitType", handler, hitType_var72, "\t\t\t\t");

						ValidateValues(stream, "hitType", "\t\t\t\t", hitType_var72, (unsigned char)8, (unsigned char)0, (unsigned char)1, (unsigned char)2, (unsigned char)3, (unsigned char)4);

						output5.DamagedTargets[i].Damages[j].HitType = (Enum::HitType)hitType_var72;

						Read<long long>("damage", handler, output5.DamagedTargets[i].Damages[j].Damage, "\t\t\t\t");
					}
				}

				if (stream.Succeeded())
				{
					handler.PacketParsed<Server::SkillDamageTilePacket>(output5);

					return;
				}
			}

			if (mode_var0 == 7)
			{
				int unknown_var74 = 0;
				Read<int>("unknown", handler, unknown_var74, "\t\t");

				int count_var75 = 0;
				Read<int>("count", handler, count_var75, "\t\t");

				for (int i = 0; i < count_var75 && !handler.PacketStream.HasRecentlyFailed; ++i)
				{
					int unknown_var76 = 0;
					Read<int>("unknown", handler, unknown_var76, "\t\t\t");
				}
			}

			if (mode_var0 == 8)
			{
				long long skillSn_var77 = 0;
				Read<long long>("skillSn", handler, skillSn_var77, "\t\t");

				bool hasTarget_var78 = false;
				Read<bool>("hasTarget", handler, hasTarget_var78, "\t\t");

				ValidateValues(stream, "hasTarget", "\t\t", hasTarget_var78, (bool)0, (bool)1);

				if (hasTarget_var78)
				{
					unsigned int skillId_var79 = 0;
					Read<unsigned int>("skillId", handler, skillId_var79, "\t\t\t");

					unsigned short skillLevel_var80 = 0;
					Read<unsigned short>("skillLevel", handler, skillLevel_var80, "\t\t\t");

					int unknown_var81 = 0;
					Read<int>("unknown", handler, unknown_var81, "\t\t\t");

					int npcId_var82 = 0;
					Read<int>("npcId", handler, npcId_var82, "\t\t\t");
				}
			}
		}

	}
}
