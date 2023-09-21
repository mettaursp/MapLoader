#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkEndPacket>(const Server::NpcTalkEndPacket& packet)
		{
			
		}
	}
}
