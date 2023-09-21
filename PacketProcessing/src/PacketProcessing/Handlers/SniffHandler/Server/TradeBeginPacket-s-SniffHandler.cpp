#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeBeginPacket>(const Server::TradeBeginPacket& packet)
		{
			
		}
	}
}
