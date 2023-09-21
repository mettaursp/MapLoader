#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketCreateListingPacket>(const Server::BlackMarketCreateListingPacket& packet)
		{
			
		}
	}
}
