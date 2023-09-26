#include "./../SniffHandler.h"

#include <GameData/Packets\Client/ResponseKeyPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::ResponseKeyPacket>(const Client::ResponseKeyPacket& packet)
		{
			AccountId = packet.AccountId;
		}
	}
}
