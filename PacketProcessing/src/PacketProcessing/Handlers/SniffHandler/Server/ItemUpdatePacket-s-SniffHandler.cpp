#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemUpdatePacket>(const Server::ItemUpdatePacket& packet)
		{
			
		}
	}
}
