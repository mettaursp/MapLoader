#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemSkinPutOffData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemSkinPutOffPacket>(const Server::ItemSkinPutOffPacket& packet)
		{
			
		}
	}
}
