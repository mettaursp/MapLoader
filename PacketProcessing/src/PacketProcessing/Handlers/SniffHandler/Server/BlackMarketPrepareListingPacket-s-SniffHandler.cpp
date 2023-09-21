#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketPrepareListingPacket>(const Server::BlackMarketPrepareListingPacket& packet)
		{
			
		}
	}
}
