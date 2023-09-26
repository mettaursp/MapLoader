#include "./../SniffHandler.h"

#include <GameData/Packets\Server/BindItemPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BindItemPacket>(const Server::BindItemPacket& packet)
		{
			
		}
	}
}
