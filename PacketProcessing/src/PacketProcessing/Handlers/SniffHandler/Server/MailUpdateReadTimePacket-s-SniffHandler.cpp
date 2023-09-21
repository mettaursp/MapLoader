#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailUpdateReadTimePacket>(const Server::MailUpdateReadTimePacket& packet)
		{
			
		}
	}
}
