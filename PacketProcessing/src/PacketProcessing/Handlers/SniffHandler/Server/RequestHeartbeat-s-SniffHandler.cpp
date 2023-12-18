#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RequestHeartbeatData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RequestHeartbeatPacket>(const Server::RequestHeartbeatPacket& packet)
		{
			
		}
	}
}
