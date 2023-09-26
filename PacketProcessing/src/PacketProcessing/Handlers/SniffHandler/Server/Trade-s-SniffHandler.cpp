#include "./../SniffHandler.h"

#include <GameData/Packets\Server/TradeReceiveRequestPacket.h>
#include <GameData/Packets\Server/TradeErrorPacket.h>
#include <GameData/Packets\Server/TradeConfirmRequestPacket.h>
#include <GameData/Packets\Server/TradeDeclinedPacket.h>
#include <GameData/Packets\Server/TradeBeginPacket.h>
#include <GameData/Packets\Server/TradeEndPacket.h>
#include <GameData/Packets\Server/TradeAddItemPacket.h>
#include <GameData/Packets\Server/TradeRemoveItemPacket.h>
#include <GameData/Packets\Server/TradeSetMoneyPacket.h>
#include <GameData/Packets\Server/TradeFinalizePacket.h>
#include <GameData/Packets\Server/TradeChangeOfferPacket.h>
#include <GameData/Packets\Server/TradeFinalizeConfirmPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeReceiveRequestPacket>(const Server::TradeReceiveRequestPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeErrorPacket>(const Server::TradeErrorPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeConfirmRequestPacket>(const Server::TradeConfirmRequestPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeDeclinedPacket>(const Server::TradeDeclinedPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeBeginPacket>(const Server::TradeBeginPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeEndPacket>(const Server::TradeEndPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeAddItemPacket>(const Server::TradeAddItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeRemoveItemPacket>(const Server::TradeRemoveItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeSetMoneyPacket>(const Server::TradeSetMoneyPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizePacket>(const Server::TradeFinalizePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeChangeOfferPacket>(const Server::TradeChangeOfferPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizeConfirmPacket>(const Server::TradeFinalizeConfirmPacket& packet)
		{
			
		}
	}
}
