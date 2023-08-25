#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::TrophyUpdatePacket>(const Server::TrophyUpdatePacket& packet)
		{
			
		}
	}
}
