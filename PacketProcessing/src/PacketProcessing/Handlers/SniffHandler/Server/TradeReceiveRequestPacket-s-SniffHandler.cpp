#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeReceiveRequestPacket>(const Server::TradeReceiveRequestPacket& packet)
		{
			
		}
	}
}
