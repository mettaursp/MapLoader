#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PetInventoryData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStoreItemPacket>(const Server::PetInventoryStoreItemPacket& packet)
		{
			Item* item = RegisterItem(packet.ItemInstanceId, packet.ItemId);

			item->Amount = 1;
			item->Rarity = packet.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "storing item in pet " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
			}
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
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				if (packet.Slots.size())
				{
					std::cout << TimeStamp << "listing items in pet inventory" << std::endl;
				}
			}

			for (const auto& entry : packet.Slots)
			{
				Item* item = RegisterItem(entry.ItemInstanceId, entry.ItemId);

				item->Amount = 1;
				item->Rarity = entry.Rarity;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << "\tdisplaying item in pet " << PrintItem{ Field, entry.ItemInstanceId } << std::endl;
					std::cout << PrintItemStats{ Field, entry.ItemInstanceId };
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStartListPacket>(const Server::PetInventoryStartListPacket& packet)
		{
			
		}
	}
}
