#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemUpdatePacket.h>

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
