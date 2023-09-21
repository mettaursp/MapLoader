#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkRespondPacket>(const Server::NpcTalkRespondPacket& packet)
		{
			
		}
	}
}
