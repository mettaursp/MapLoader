#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkAlliancePacket>(const Server::NpcTalkAlliancePacket& packet)
		{
			
		}
	}
}
