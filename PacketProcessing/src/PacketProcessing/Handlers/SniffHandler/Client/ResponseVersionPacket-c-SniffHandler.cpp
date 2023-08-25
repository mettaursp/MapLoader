#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::ResponseVersionPacket>(const Client::ResponseVersionPacket& packet)
		{
			
		}
	}
}
