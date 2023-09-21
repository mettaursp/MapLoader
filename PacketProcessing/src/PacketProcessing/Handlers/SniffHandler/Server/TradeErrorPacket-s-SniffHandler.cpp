#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeErrorPacket>(const Server::TradeErrorPacket& packet)
		{
			
		}
	}
}
