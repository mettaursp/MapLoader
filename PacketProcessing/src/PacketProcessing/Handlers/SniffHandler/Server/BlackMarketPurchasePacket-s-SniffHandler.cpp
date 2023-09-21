#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPurchasePacket>(const Server::BlackMarketPurchasePacket& packet)
		{
			
		}
	}
}
