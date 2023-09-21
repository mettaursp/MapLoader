#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopErrorPacket>(const Server::ShopErrorPacket& packet)
		{
			
		}
	}
}
