#include "./../SniffHandler.h"

#include <GameData/Packets\Client/RequestQuitData.h>

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
