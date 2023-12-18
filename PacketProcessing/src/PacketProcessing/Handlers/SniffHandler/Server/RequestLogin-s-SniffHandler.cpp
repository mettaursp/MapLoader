#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RequestLoginData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RequestLoginPacket>(const Server::RequestLoginPacket& packet)
		{
			
		}
	}
}
