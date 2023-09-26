#include "./../SniffHandler.h"

#include <GameData/Packets\Server/CharacterListLoadPacket.h>
#include <GameData/Packets\Server/CharacterListAddPacket.h>
#include <GameData/Packets\Server/CharacterListDeletePacket.h>
#include <GameData/Packets\Server/CharacterListDeletePendingPacket.h>
#include <GameData/Packets\Server/CharacterListCancelDeletePacket.h>
#include <GameData/Packets\Server/CharacterListChangeNamePacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::CharacterListLoadPacket>(const Server::CharacterListLoadPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::CharacterListAddPacket>(const Server::CharacterListAddPacket& packet)
		{
			
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
