#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::UserChatItemLinkPacket>(const Server::UserChatItemLinkPacket& packet)
		{
			
		}
	}
}
