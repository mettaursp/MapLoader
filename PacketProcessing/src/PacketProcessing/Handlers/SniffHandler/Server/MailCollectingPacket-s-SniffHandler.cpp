#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailCollectingPacket>(const Server::MailCollectingPacket& packet)
		{
			
		}
	}
}
