#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemLockRemoveItemPacket>(const Server::ItemLockRemoveItemPacket& packet)
		{
			
		}
	}
}
