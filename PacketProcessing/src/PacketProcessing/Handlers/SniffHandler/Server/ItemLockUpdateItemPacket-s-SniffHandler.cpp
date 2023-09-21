#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemLockUpdateItemPacket>(const Server::ItemLockUpdateItemPacket& packet)
		{
			
		}
	}
}
