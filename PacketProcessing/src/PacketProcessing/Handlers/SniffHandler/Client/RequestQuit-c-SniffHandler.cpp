#include "./../SniffHandler.h"

#include <GameData/Packets\Client/RequestQuitPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::RequestQuitPacket>(const Client::RequestQuitPacket& packet)
		{
			
		}
	}
}
