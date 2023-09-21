#include "./../SniffHandler.h"

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemLockAddItemPacket>(const Server::ItemLockAddItemPacket& packet)
		{
			
		}
	}
}
