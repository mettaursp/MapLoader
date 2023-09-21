#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSearchResultsPacket>(const Server::BlackMarketSearchResultsPacket& packet)
		{
			
		}
	}
}
