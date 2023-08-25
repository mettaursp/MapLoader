#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TrophyContentPacket>(const Server::TrophyContentPacket& packet)
		{
			
		}
	}
}
