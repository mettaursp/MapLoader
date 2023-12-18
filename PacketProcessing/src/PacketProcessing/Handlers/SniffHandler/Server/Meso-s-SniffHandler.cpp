#include "./../SniffHandler.h"

#include <GameData/Packets\Server/MesoData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MesoPacket>(const Server::MesoPacket& packet)
		{
			
		}
	}
}
