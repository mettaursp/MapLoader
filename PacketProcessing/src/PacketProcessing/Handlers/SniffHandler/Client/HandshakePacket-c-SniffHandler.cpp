#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::HandshakePacket>(const Client::HandshakePacket& packet)
		{
			
		}
	}
}
