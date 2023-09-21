#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailReceiveGiftNotificationPacket>(const Server::MailReceiveGiftNotificationPacket& packet)
		{
			
		}
	}
}
