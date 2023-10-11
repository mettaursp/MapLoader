#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemLockData.h>
#include <ParserUtils/PacketParsing.h>

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
			for (const auto& entry : packet.Items)
			{
				Item* item = GetItem(entry.ItemInstanceId);

				if (item)
				{
					*item->Data = entry.ItemData;

					if constexpr (ParserUtils::Packets::PrintPacketOutput)
					{
						std::cout << TimeStamp << (item->Data->IsLocked ? "locked item " : "unlocked item ") << PrintItem{Field, entry.ItemInstanceId} << std::endl;
					}
				}
				else
				{
					if constexpr (ParserUtils::Packets::PrintUnknownValues)
					{
						FoundUnknownValue();

						std::cout << TimeStamp << "attempting to lock/unlock item " << entry.ItemInstanceId << std::endl;
					}
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemLockErrorPacket>(const Server::ItemLockErrorPacket& packet)
		{
			
		}
	}
}
