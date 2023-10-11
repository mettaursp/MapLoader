#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FurnishingStorageData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageStartListPacket>(const Server::FurnishingStorageStartListPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageCountPacket>(const Server::FurnishingStorageCountPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageAddPacket>(const Server::FurnishingStorageAddPacket& packet)
		{
			Item* item = RegisterItem(packet.ItemInstanceId, packet.ItemId);

			item->Amount = 1;
			item->Rarity = packet.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "added item to furnishing storage " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageRemovePacket>(const Server::FurnishingStorageRemovePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStoragePurchasePacket>(const Server::FurnishingStoragePurchasePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageUpdatePacket>(const Server::FurnishingStorageUpdatePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FurnishingStorageEndListPacket>(const Server::FurnishingStorageEndListPacket& packet)
		{
			
		}
	}
}
