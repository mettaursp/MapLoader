#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TrophyStartPacket>(const Server::TrophyStartPacket& packet)
		{
			
		}
	}
}
