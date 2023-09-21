#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopOpenPacket>(const Server::ShopOpenPacket& packet)
		{
			
		}
	}
}
