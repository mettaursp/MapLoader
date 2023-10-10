#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemPutOnData.h>

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
