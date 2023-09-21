#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailError2Packet>(const Server::MailError2Packet& packet)
		{
			
		}
	}
}
