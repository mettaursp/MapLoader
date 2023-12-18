#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ServerListData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ServerListPacket>(const Server::ServerListPacket& packet)
		{
			
		}
	}
}
