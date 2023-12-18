#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RequestVersionData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RequestVersionPacket>(const Server::RequestVersionPacket& packet)
		{
			
		}
	}
}
