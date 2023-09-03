#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::JobPacket>(const Server::JobPacket& packet)
		{
			
		}
	}
}
