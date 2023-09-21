#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketSoldPacket>(const Server::BlackMarketSoldPacket& packet)
		{
			
		}
	}
}
