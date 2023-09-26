#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemSkinPutOffPacket.h>

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
