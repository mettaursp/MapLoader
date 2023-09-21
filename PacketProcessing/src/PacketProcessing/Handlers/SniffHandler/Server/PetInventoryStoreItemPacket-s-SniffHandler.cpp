#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStoreItemPacket>(const Server::PetInventoryStoreItemPacket& packet)
		{
			
		}
	}
}
