#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeRemoveItemPacket>(const Server::TradeRemoveItemPacket& packet)
		{
			
		}
	}
}
