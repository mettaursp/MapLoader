#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TradeFinalizeConfirmPacket>(const Server::TradeFinalizeConfirmPacket& packet)
		{
			
		}
	}
}
