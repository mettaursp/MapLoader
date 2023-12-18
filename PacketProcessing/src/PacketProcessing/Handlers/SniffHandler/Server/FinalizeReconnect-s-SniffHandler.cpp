#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FinalizeReconnectData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FinalizeReconnectPacket>(const Server::FinalizeReconnectPacket& packet)
		{
			
		}
	}
}
