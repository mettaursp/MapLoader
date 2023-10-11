#include "./../SniffHandler.h"

#include <GameData/Packets\Server/CharacterListData.h>
#include <PacketProcessing/PacketLogging.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		void logEntry(SniffHandler* handler, const Maple::Game::CharacterListEntry& entry)
		{
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler->TimeStamp << "logging equipment for character " << entry.Character.Name << std::endl;
			}

			LogEquipment(handler, entry.Equipment);
		}

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListLoadPacket>(const Server::CharacterListLoadPacket& packet)
		{
			for (const auto& entry : packet.Characters)
			{
				logEntry(this, entry);
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListAddPacket>(const Server::CharacterListAddPacket& packet)
		{
			logEntry(this, packet.Character);
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePacket>(const Server::CharacterListDeletePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListDeletePendingPacket>(const Server::CharacterListDeletePendingPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListCancelDeletePacket>(const Server::CharacterListCancelDeletePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListChangeNamePacket>(const Server::CharacterListChangeNamePacket& packet)
		{
			
		}
	}
}
