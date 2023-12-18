#include "./../SniffHandler.h"

#include <GameData/Packets\Server/LoginResultData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::LoginResultPacket>(const Server::LoginResultPacket& packet)
		{
			
		}
	}
}
