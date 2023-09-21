#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryStartListPacket>(const Server::PetInventoryStartListPacket& packet)
		{
			
		}
	}
}
