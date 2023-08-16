#pragma once

#include "PacketParserBase.h"

#include <GameData/Packets\Client/ResponseVersionPacket.h>
#include <GameData/Packets\Client/SkillSyncDamagePacket.h>
#include <GameData/Packets\Client/ResponseKeyPacket.h>
#include <GameData/Packets\Client/SkillDamagePacket.h>
#include <GameData/Packets\Client/ResponseHeartbeatPacket.h>
#include <GameData/Packets\Client/RequestQuitPacket.h>
#include <GameData/Packets\Client/SkillCastPacket.h>
#include <GameData/Packets\Client/SkillRegionSkillPacket.h>
#include <GameData/Packets\Client/SkillSyncPacket.h>
#include <GameData/Packets\Client/SkillSyncTickPacket.h>
#include <GameData/Packets\Client/SkillCancelPacket.h>
#include <GameData/Packets\Client/SystemInfoPacket.h>
#include <GameData/Packets\Server/UserChatPacket.h>
#include <GameData/Packets\Server/BuffPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void PacketParsed<Client::ResponseVersionPacket>(const Client::ResponseVersionPacket& packet);

		template <>
		void PacketParsed<Client::SkillSyncDamagePacket>(const Client::SkillSyncDamagePacket& packet);

		template <>
		void PacketParsed<Client::ResponseKeyPacket>(const Client::ResponseKeyPacket& packet);

		template <>
		void PacketParsed<Client::SkillDamagePacket>(const Client::SkillDamagePacket& packet);

		template <>
		void PacketParsed<Client::ResponseHeartbeatPacket>(const Client::ResponseHeartbeatPacket& packet);

		template <>
		void PacketParsed<Client::RequestQuitPacket>(const Client::RequestQuitPacket& packet);

		template <>
		void PacketParsed<Client::SkillCastPacket>(const Client::SkillCastPacket& packet);

		template <>
		void PacketParsed<Client::SkillRegionSkillPacket>(const Client::SkillRegionSkillPacket& packet);

		template <>
		void PacketParsed<Client::SkillSyncPacket>(const Client::SkillSyncPacket& packet);

		template <>
		void PacketParsed<Client::SkillSyncTickPacket>(const Client::SkillSyncTickPacket& packet);

		template <>
		void PacketParsed<Client::SkillCancelPacket>(const Client::SkillCancelPacket& packet);

		template <>
		void PacketParsed<Client::SystemInfoPacket>(const Client::SystemInfoPacket& packet);

		template <>
		void PacketParsed<Server::UserChatPacket>(const Server::UserChatPacket& packet);

		template <>
		void PacketParsed<Server::BuffPacket>(const Server::BuffPacket& packet);

	}
}
