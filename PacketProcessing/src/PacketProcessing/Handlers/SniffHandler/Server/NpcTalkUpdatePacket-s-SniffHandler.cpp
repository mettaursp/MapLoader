#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkUpdatePacket>(const Server::NpcTalkUpdatePacket& packet)
		{
			
		}
	}
}
