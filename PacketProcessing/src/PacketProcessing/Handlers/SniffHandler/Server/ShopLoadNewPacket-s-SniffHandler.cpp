#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopLoadNewPacket>(const Server::ShopLoadNewPacket& packet)
		{
			
		}
	}
}
