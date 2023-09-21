#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ShopUpdatePacket>(const Server::ShopUpdatePacket& packet)
		{
			
		}
	}
}
