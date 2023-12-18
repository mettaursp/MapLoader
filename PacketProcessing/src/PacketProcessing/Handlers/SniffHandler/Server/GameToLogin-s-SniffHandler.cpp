#include "./../SniffHandler.h"

#include <GameData/Packets\Server/GameToLoginData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::GameToLoginPacket>(const Server::GameToLoginPacket& packet)
		{
			
		}
	}
}
