#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PetInventoryStoreItemPacket.h>
#include <GameData/Packets\Server/PetInventoryRemoveItemPacket.h>
#include <GameData/Packets\Server/PetInventoryUpdateAmountPacket.h>
#include <GameData/Packets\Server/PetInventoryMoveItemPacket.h>
#include <GameData/Packets\Server/PetInventoryListItemsPacket.h>
#include <GameData/Packets\Server/PetInventoryStartListPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStoreItemPacket>(const Server::PetInventoryStoreItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryRemoveItemPacket>(const Server::PetInventoryRemoveItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryUpdateAmountPacket>(const Server::PetInventoryUpdateAmountPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryMoveItemPacket>(const Server::PetInventoryMoveItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryListItemsPacket>(const Server::PetInventoryListItemsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStartListPacket>(const Server::PetInventoryStartListPacket& packet)
		{
			
		}
	}
}
