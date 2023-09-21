#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::PetInventoryUpdateAmountPacket>(const Server::PetInventoryUpdateAmountPacket& packet)
		{
			
		}
	}
}
