#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryListItemsPacket>(const Server::PetInventoryListItemsPacket& packet)
		{
			
		}
	}
}
