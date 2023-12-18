#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RevivalData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RevivalPacket>(const Server::RevivalPacket& packet)
		{
			
		}
	}
}
