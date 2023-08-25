#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BuffPacket>(const Server::BuffPacket& packet)
		{
			
		}
	}
}
