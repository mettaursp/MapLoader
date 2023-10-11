#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FittingDollData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FittingDollLoadPacket>(const Server::FittingDollLoadPacket& packet)
		{
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "loading fitting doll with items:" << std::endl;
			}

			for (const auto& entry : packet.Items)
			{
				Item* item = RegisterItem(entry.ItemInstanceId, entry.ItemId);

				item->Amount = 1;
				item->Rarity = entry.Rarity;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << "\titem " << PrintItem{ Field, entry.ItemInstanceId } << std::endl;
					std::cout << PrintItemStats{ Field, entry.ItemInstanceId };
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollRemovePacket>(const Server::FittingDollRemovePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollPutOnItemPacket>(const Server::FittingDollPutOnItemPacket& packet)
		{
			Item* item = RegisterItem(packet.ItemInstanceId, packet.ItemId);

			item->Amount = 1;
			item->Rarity = packet.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "putting item " << PrintItem{ Field, packet.ItemInstanceId } << " on fitting doll" << std::endl;
				std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollRemoveItemPacket>(const Server::FittingDollRemoveItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::FittingDollErrorPacket>(const Server::FittingDollErrorPacket& packet)
		{
			
		}
	}
}
