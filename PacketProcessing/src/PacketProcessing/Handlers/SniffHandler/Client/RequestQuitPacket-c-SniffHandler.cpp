#include "./../SniffHandler.h"

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
