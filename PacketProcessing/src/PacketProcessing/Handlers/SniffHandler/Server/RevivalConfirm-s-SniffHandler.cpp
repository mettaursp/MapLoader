#include "./../SniffHandler.h"

#include <GameData/Packets\Server/RevivalConfirmData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::RevivalConfirmPacket>(const Server::RevivalConfirmPacket& packet)
		{
			
		}
	}
}
