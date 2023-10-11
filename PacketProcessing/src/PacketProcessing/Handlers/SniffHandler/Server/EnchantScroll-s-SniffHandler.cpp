#include "./../SniffHandler.h"

#include <GameData/Packets\Server/EnchantScrollData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollEnchantUiPacket>(const Server::EnchantScrollEnchantUiPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollStatUiPacket>(const Server::EnchantScrollStatUiPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollSuccessPacket>(const Server::EnchantScrollSuccessPacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "successfully enchanted item " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "attempting to enchant unregistered item instance " << packet.ItemInstanceId << std::endl;
				}
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollResultPacket>(const Server::EnchantScrollResultPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::EnchantScrollRewardPacket>(const Server::EnchantScrollRewardPacket& packet)
		{
			
		}
	}
}
