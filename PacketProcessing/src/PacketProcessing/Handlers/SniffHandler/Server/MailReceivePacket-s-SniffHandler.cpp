#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailReceivePacket>(const Server::MailReceivePacket& packet)
		{
			
		}
	}
}
