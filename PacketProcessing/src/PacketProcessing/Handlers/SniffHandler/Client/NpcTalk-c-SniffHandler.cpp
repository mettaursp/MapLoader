#include "./../SniffHandler.h"

#include <GameData/Packets\Client/NpcTalkClosePacket.h>
#include <GameData/Packets\Client/NpcTalkBeginPacket.h>
#include <GameData/Packets\Client/NpcTalkContinuePacket.h>
#include <GameData/Packets\Client/NpcTalkEnchantUnknownPacket.h>
#include <GameData/Packets\Client/NpcTalkEnchantPacket.h>
#include <GameData/Packets\Client/NpcTalkNextQuestPacket.h>
#include <GameData/Packets\Client/NpcTalkAllianceQuestAcceptPacket.h>
#include <GameData/Packets\Client/NpcTalkAllianceQuestTalkPacket.h>
#include <GameData/Packets\Client/NpcTalkCinematicPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkClosePacket>(const Client::NpcTalkClosePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkBeginPacket>(const Client::NpcTalkBeginPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkContinuePacket>(const Client::NpcTalkContinuePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantUnknownPacket>(const Client::NpcTalkEnchantUnknownPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkEnchantPacket>(const Client::NpcTalkEnchantPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkNextQuestPacket>(const Client::NpcTalkNextQuestPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkAllianceQuestAcceptPacket>(const Client::NpcTalkAllianceQuestAcceptPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkAllianceQuestTalkPacket>(const Client::NpcTalkAllianceQuestTalkPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Client::NpcTalkCinematicPacket>(const Client::NpcTalkCinematicPacket& packet)
		{
			
		}
	}
}
