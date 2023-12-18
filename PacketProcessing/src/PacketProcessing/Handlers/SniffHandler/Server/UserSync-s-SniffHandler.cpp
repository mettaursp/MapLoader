#include "./../SniffHandler.h"

#include <GameData/Packets\Server/UserSyncData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::UserSyncPacket>(const Server::UserSyncPacket& packet)
		{
			
		}
	}
}
