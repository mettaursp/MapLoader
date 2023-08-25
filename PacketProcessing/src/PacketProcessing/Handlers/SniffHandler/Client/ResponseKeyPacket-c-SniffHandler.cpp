#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::ResponseKeyPacket>(const Client::ResponseKeyPacket& packet)
		{
			
		}
	}
}
