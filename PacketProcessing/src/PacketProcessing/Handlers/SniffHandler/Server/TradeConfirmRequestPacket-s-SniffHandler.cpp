#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeConfirmRequestPacket>(const Server::TradeConfirmRequestPacket& packet)
		{
			
		}
	}
}
