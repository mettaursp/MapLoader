#include "./../SniffHandler.h"

#include <GameData/Packets\Server/UserChatItemLinkData.h>

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
