#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCancelListingPacket>(const Server::BlackMarketCancelListingPacket& packet)
		{
			
		}
	}
}
