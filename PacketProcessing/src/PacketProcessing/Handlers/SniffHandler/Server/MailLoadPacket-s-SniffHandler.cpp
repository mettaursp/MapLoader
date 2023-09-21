#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailLoadPacket>(const Server::MailLoadPacket& packet)
		{
			
		}
	}
}
