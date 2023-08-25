#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::ResponseHeartbeatPacket>(const Client::ResponseHeartbeatPacket& packet)
		{
			
		}
	}
}
