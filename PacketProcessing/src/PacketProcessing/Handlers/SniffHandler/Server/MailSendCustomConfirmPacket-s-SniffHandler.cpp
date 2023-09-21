#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::MailSendCustomConfirmPacket>(const Server::MailSendCustomConfirmPacket& packet)
		{
			
		}
	}
}
