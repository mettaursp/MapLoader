#include "./../SniffHandler.h"

#include <GameData/Packets\Client/HandshakePacket.h>

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
