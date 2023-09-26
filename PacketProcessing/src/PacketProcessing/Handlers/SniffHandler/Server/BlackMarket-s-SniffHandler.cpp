#include "./../SniffHandler.h"

#include <GameData/Packets\Server/BlackMarketErrorPacket.h>
#include <GameData/Packets\Server/BlackMarketMyListingsPacket.h>
#include <GameData/Packets\Server/BlackMarketCreateListingPacket.h>
#include <GameData/Packets\Server/BlackMarketCancelListingPacket.h>
#include <GameData/Packets\Server/BlackMarketSearchResultsPacket.h>
#include <GameData/Packets\Server/BlackMarketPurchasePacket.h>
#include <GameData/Packets\Server/BlackMarketSoldPacket.h>
#include <GameData/Packets\Server/BlackMarketPrepareListingPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketErrorPacket>(const Server::BlackMarketErrorPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketMyListingsPacket>(const Server::BlackMarketMyListingsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCreateListingPacket>(const Server::BlackMarketCreateListingPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCancelListingPacket>(const Server::BlackMarketCancelListingPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSearchResultsPacket>(const Server::BlackMarketSearchResultsPacket& packet)
		{
			
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
