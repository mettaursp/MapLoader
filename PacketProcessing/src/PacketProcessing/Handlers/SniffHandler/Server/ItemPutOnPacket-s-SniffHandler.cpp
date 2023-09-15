#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemPutOnPacket>(const Server::ItemPutOnPacket& packet)
		{
			
		}
	}
}
