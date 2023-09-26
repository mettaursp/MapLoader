#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemLockAddItemPacket.h>
#include <GameData/Packets\Server/ItemLockRemoveItemPacket.h>
#include <GameData/Packets\Server/ItemLockUpdateItemPacket.h>
#include <GameData/Packets\Server/ItemLockErrorPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemLockAddItemPacket>(const Server::ItemLockAddItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockRemoveItemPacket>(const Server::ItemLockRemoveItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockUpdateItemPacket>(const Server::ItemLockUpdateItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockErrorPacket>(const Server::ItemLockErrorPacket& packet)
		{
			
		}
	}
}
