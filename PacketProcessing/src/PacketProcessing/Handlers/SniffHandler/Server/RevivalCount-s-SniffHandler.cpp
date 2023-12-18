#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RevivalCountData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RevivalCountPacket>(const Server::RevivalCountPacket& packet)
		{
			
		}
	}
}
