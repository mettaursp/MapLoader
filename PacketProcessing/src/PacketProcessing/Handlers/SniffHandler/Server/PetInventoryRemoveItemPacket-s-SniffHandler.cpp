#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryRemoveItemPacket>(const Server::PetInventoryRemoveItemPacket& packet)
		{
			
		}
	}
}
