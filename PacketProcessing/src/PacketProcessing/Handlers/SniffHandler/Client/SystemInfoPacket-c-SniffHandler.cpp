#include "./../SniffHandler.h"

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
