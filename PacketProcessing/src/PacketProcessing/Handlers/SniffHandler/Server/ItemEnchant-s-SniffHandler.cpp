#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemEnchantData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantBeginPacket>(const Server::ItemEnchantBeginPacket& packet)
		{
			Item* item = RegisterItem(packet.ItemInstanceId, packet.ItemId);

			item->Amount = 1;
			item->Rarity = packet.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "enchanting item " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateExpPacket>(const Server::ItemEnchantUpdateExpPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateChargesPacket>(const Server::ItemEnchantUpdateChargesPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantUpdateIngredientsPacket>(const Server::ItemEnchantUpdateIngredientsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ItemEnchantSuccessPacket>(const Server::ItemEnchantSuccessPacket& packet)
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
		void SniffHandler::PacketParsed<Server::ItemEnchantFailPacket>(const Server::ItemEnchantFailPacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "failed to enchanted item " << PrintItem{ Field, packet.ItemInstanceId } << " with " << packet.FailStacks << " fail stacks " << std::endl;
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
		void SniffHandler::PacketParsed<Server::ItemEnchantErrorPacket>(const Server::ItemEnchantErrorPacket& packet)
		{
			
		}
	}
}
