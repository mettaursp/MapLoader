#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadItemsPacket>(const Server::ShopLoadItemsPacket& packet)
		{
			
		}
	}
}
