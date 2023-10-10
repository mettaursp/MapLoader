#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemUpdateData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemUpdatePacket>(const Server::ItemUpdatePacket& packet)
		{
			
		}
	}
}
