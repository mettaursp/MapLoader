#include "./../SniffHandler.h"

#include <GameData/Packets\Server/BlackMarketData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		void printListing(SniffHandler* handler, const Maple::Game::BlackMarketEntryData& listing)
		{
			Item* item = handler->RegisterItem(listing.ItemInstanceId, listing.ItemId);

			item->Amount = listing.Amount;
			item->Rarity = listing.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << handler->TimeStamp << "listing black market item " << PrintItem{ handler->Field, listing.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ handler->Field, listing.ItemInstanceId };
			}
		}

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketErrorPacket>(const Server::BlackMarketErrorPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketMyListingsPacket>(const Server::BlackMarketMyListingsPacket& packet)
		{
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << "displaying players black market listings" << std::endl;
			}

			for (const auto& listing : packet.Entries)
			{
				printListing(this, listing);
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCreateListingPacket>(const Server::BlackMarketCreateListingPacket& packet)
		{
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << "creating black market listing" << std::endl;
			}

			printListing(this, packet.Listing);
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCancelListingPacket>(const Server::BlackMarketCancelListingPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSearchResultsPacket>(const Server::BlackMarketSearchResultsPacket& packet)
		{
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << "displaying black market search results" << std::endl;
			}

			for (const auto& listing : packet.Entries)
			{
				printListing(this, listing);
			}
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPurchasePacket>(const Server::BlackMarketPurchasePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSoldPacket>(const Server::BlackMarketSoldPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPrepareListingPacket>(const Server::BlackMarketPrepareListingPacket& packet)
		{
			
		}
	}
}
