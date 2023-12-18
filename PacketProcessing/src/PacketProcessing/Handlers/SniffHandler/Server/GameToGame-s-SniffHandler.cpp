#include "./../SniffHandler.h"

#include <GameData/Packets\Server/GameToGameData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::GameToGamePacket>(const Server::GameToGamePacket& packet)
		{
			
		}
	}
}
