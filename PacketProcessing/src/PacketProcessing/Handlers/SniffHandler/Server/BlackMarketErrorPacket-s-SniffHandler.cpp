#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BlackMarketErrorPacket>(const Server::BlackMarketErrorPacket& packet)
		{
			
		}
	}
}
