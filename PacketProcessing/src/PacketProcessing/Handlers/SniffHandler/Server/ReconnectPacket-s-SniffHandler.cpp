#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ReconnectPacket>(const Server::ReconnectPacket& packet)
		{
		}
	}
}
