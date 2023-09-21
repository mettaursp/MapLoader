#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailReadPacket>(const Server::MailReadPacket& packet)
		{
			
		}
	}
}
