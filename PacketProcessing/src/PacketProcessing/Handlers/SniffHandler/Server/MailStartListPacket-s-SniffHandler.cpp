#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailStartListPacket>(const Server::MailStartListPacket& packet)
		{
			
		}
	}
}
