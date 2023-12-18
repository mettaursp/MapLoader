#include "./../SniffHandler.h"

#include <GameData/Packets\Server/MeretData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MeretPacket>(const Server::MeretPacket& packet)
		{
			
		}
	}
}
