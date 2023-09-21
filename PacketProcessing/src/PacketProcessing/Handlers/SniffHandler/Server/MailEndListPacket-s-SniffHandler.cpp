#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailEndListPacket>(const Server::MailEndListPacket& packet)
		{
			
		}
	}
}
