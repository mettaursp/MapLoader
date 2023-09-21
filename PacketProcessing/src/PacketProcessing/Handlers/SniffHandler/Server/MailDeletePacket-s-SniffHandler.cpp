#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailDeletePacket>(const Server::MailDeletePacket& packet)
		{
			
		}
	}
}
