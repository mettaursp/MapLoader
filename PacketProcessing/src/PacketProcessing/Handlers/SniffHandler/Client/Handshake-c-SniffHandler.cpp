#include "./../SniffHandler.h"

#include <GameData/Packets\Client/HandshakeData.h>

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
