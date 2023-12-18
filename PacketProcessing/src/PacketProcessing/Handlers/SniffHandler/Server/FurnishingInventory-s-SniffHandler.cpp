#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FurnishingInventoryData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FurnishingInventoryUnknownPacket>(const Server::FurnishingInventoryUnknownPacket& packet)
		{
			
		}
	}
}
