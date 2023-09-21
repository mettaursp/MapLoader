#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopBuyPacket>(const Server::ShopBuyPacket& packet)
		{
			
		}
	}
}
