#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeAddItemPacket>(const Server::TradeAddItemPacket& packet)
		{
			
		}
	}
}
