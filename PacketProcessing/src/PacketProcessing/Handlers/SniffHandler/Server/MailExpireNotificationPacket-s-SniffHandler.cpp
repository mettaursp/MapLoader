#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailExpireNotificationPacket>(const Server::MailExpireNotificationPacket& packet)
		{
			
		}
	}
}
