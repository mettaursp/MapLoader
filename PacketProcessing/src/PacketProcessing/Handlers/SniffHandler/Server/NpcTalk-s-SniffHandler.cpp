#include "./../SniffHandler.h"

#include <GameData/Packets\Server/NpcTalkEndPacket.h>
#include <GameData/Packets\Server/NpcTalkRespondPacket.h>
#include <GameData/Packets\Server/NpcTalkContinuePacket.h>
#include <GameData/Packets\Server/NpcTalkActionMovePlayerPacket.h>
#include <GameData/Packets\Server/NpcTalkActionOpenDialogPacket.h>
#include <GameData/Packets\Server/NpcTalkActionRewardItemPacket.h>
#include <GameData/Packets\Server/NpcTalkActionRewardExpPacket.h>
#include <GameData/Packets\Server/NpcTalkActionRewardMesoPacket.h>
#include <GameData/Packets\Server/NpcTalkActionAddOptionPacket.h>
#include <GameData/Packets\Server/NpcTalkActionCutscenePacket.h>
#include <GameData/Packets\Server/NpcTalkUpdatePacket.h>
#include <GameData/Packets\Server/NpcTalkAlliancePacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkEndPacket>(const Server::NpcTalkEndPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkRespondPacket>(const Server::NpcTalkRespondPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkContinuePacket>(const Server::NpcTalkContinuePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionMovePlayerPacket>(const Server::NpcTalkActionMovePlayerPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionOpenDialogPacket>(const Server::NpcTalkActionOpenDialogPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardItemPacket>(const Server::NpcTalkActionRewardItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardExpPacket>(const Server::NpcTalkActionRewardExpPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionRewardMesoPacket>(const Server::NpcTalkActionRewardMesoPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionAddOptionPacket>(const Server::NpcTalkActionAddOptionPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionCutscenePacket>(const Server::NpcTalkActionCutscenePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkUpdatePacket>(const Server::NpcTalkUpdatePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkAlliancePacket>(const Server::NpcTalkAlliancePacket& packet)
		{
			
		}
	}
}
