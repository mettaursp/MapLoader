#include "./../SniffHandler.h"

#include <GameData/Packets\Server/AdventurerBarData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::AdventurerBarPacket>(const Server::AdventurerBarPacket& packet)
		{
			
		}
	}
}
