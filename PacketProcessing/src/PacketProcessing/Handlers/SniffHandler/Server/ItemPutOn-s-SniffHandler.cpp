#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemPutOnPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemPutOnPacket>(const Server::ItemPutOnPacket& packet)
		{
			
		}
	}
}
