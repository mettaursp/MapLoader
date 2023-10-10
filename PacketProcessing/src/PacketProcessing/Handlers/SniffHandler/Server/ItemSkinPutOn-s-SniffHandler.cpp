#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemSkinPutOnData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemSkinPutOnPacket>(const Server::ItemSkinPutOnPacket& packet)
		{
			
		}
	}
}
