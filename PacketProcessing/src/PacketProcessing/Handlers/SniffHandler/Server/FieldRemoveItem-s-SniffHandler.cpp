#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldRemoveItemData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveItemPacket>(const Server::FieldRemoveItemPacket& packet)
		{
			
		}
	}
}
