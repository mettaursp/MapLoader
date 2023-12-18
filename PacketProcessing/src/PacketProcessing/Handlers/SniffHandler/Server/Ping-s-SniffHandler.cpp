#include "./../SniffHandler.h"

#include <GameData/Packets\Server/PingData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PingPacket>(const Server::PingPacket& packet)
		{
			
		}
	}
}
