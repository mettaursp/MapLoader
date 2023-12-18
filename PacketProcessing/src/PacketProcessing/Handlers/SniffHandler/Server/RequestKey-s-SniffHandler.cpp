#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RequestKeyData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RequestKeyPacket>(const Server::RequestKeyPacket& packet)
		{
			
		}
	}
}
