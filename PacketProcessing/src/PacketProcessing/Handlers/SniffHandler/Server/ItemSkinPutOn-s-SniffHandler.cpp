#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemSkinPutOnPacket.h>

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
