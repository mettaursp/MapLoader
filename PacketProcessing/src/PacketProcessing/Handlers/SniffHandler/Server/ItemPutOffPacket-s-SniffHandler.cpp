#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemPutOffPacket>(const Server::ItemPutOffPacket& packet)
		{
			
		}
	}
}
