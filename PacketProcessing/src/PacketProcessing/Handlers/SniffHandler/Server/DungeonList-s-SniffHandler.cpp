#include "./../SniffHandler.h"

#include <GameData/Packets\Server/DungeonListData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::DungeonListEntriesPacket>(const Server::DungeonListEntriesPacket& packet)
		{
			
		}
	}
}
