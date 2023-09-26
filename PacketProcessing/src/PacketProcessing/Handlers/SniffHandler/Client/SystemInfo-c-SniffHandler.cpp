#include "./../SniffHandler.h"

#include <GameData/Packets\Client/SystemInfoPacket.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Client::SystemInfoPacket>(const Client::SystemInfoPacket& packet)
		{
			
		}
	}
}
