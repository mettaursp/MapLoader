#include "./../SniffHandler.h"

#include <GameData/Packets\Server/SkillDamageSyncPacket.h>
#include <GameData/Packets\Server/SkillDamagePacket.h>
#include <GameData/Packets\Server/SkillDamageDotPacket.h>
#include <GameData/Packets\Server/SkillDamageHealPacket.h>
#include <GameData/Packets\Server/SkillDamageRegionPacket.h>
#include <GameData/Packets\Server/SkillDamageTilePacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageSyncPacket>(const Server::SkillDamageSyncPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamagePacket>(const Server::SkillDamagePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageDotPacket>(const Server::SkillDamageDotPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageHealPacket>(const Server::SkillDamageHealPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageRegionPacket>(const Server::SkillDamageRegionPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::SkillDamageTilePacket>(const Server::SkillDamageTilePacket& packet)
		{
			
		}
	}
}
