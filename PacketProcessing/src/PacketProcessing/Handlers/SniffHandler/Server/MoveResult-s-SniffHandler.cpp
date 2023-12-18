#include "./../SniffHandler.h"

#include <GameData/Packets\Server/MoveResultData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MoveResultPacket>(const Server::MoveResultPacket& packet)
		{
			
		}
	}
}
