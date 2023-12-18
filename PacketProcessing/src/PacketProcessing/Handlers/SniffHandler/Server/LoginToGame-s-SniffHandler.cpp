#include "./../SniffHandler.h"

#include <GameData/Packets\Server/LoginToGameData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::LoginToGamePacket>(const Server::LoginToGamePacket& packet)
		{
			
		}
	}
}
