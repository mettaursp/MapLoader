#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::Reconnect7Packet>(const Server::Reconnect7Packet& packet)
		{
		}
	}
}
