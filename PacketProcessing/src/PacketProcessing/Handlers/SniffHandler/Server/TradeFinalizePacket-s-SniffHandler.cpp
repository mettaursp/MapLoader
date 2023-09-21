#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizePacket>(const Server::TradeFinalizePacket& packet)
		{
			
		}
	}
}
