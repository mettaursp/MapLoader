#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FurnishingStorageStartListPacket.h>
#include <GameData/Packets\Server/FurnishingStorageCountPacket.h>
#include <GameData/Packets\Server/FurnishingStorageAddPacket.h>
#include <GameData/Packets\Server/FurnishingStorageRemovePacket.h>
#include <GameData/Packets\Server/FurnishingStoragePurchasePacket.h>
#include <GameData/Packets\Server/FurnishingStorageUpdatePacket.h>
#include <GameData/Packets\Server/FurnishingStorageEndListPacket.h>

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
