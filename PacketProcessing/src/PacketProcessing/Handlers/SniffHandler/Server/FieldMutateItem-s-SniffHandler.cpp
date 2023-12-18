#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldPickUpItemData.h>
#include <GameData/Packets\Server/FieldMutateItemData.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldMutateItemPacket>(const Server::FieldMutateItemPacket& packet)
		{
			
		}
	}
}
