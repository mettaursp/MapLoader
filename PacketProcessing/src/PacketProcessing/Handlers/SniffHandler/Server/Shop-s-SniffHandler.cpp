#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ShopData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopOpenPacket>(const Server::ShopOpenPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadItemsPacket>(const Server::ShopLoadItemsPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopUpdatePacket>(const Server::ShopUpdatePacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopBuyPacket>(const Server::ShopBuyPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopBuyBackItemCountPacket>(const Server::ShopBuyBackItemCountPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopAddBuyBackPacket>(const Server::ShopAddBuyBackPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopRemoveBuyBackPacket>(const Server::ShopRemoveBuyBackPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopInstantRestockPacket>(const Server::ShopInstantRestockPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopMeretItemCountPacket>(const Server::ShopMeretItemCountPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadMeretItemPacket>(const Server::ShopLoadMeretItemPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadNewPacket>(const Server::ShopLoadNewPacket& packet)
		{
			
		}
	

		template <>
		void SniffHandler::PacketParsed<Server::ShopErrorPacket>(const Server::ShopErrorPacket& packet)
		{
			
		}
	}
}
