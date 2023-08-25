#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::LogInAuthTokenPacket>(const Client::LogInAuthTokenPacket& packet)
		{
			
		}
	}
}
