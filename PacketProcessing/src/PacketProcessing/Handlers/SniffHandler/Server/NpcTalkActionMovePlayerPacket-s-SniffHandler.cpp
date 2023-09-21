#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::NpcTalkActionMovePlayerPacket>(const Server::NpcTalkActionMovePlayerPacket& packet)
		{
			
		}
	}
}
