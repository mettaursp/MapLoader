#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RequestClientTickSyncData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RequestClientTickSyncPacket>(const Server::RequestClientTickSyncPacket& packet)
		{
			
		}
	}
}
