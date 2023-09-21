#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopInstantRestockPacket>(const Server::ShopInstantRestockPacket& packet)
		{
			
		}
	}
}
