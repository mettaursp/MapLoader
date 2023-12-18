#include "./../SniffHandler.h"

#include <GameData/Packets\Server/UserStateData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::UserStatePacket>(const Server::UserStatePacket& packet)
		{
			
		}
	}
}
