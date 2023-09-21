#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketMyListingsPacket>(const Server::BlackMarketMyListingsPacket& packet)
		{
			
		}
	}
}
