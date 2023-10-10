#include "./../SniffHandler.h"

#include <GameData/Packets\Client/ResponseHeartbeatData.h>

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
