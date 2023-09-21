#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeSetMoneyPacket>(const Server::TradeSetMoneyPacket& packet)
		{
			
		}
	}
}
