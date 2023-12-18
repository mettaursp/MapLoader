#include "./../SniffHandler.h"

#include <GameData/Packets\Server/SyncNumberData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::SyncNumberPacket>(const Server::SyncNumberPacket& packet)
		{
			
		}
	}
}
