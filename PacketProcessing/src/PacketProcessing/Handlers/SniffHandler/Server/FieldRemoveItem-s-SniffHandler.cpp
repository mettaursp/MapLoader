#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldRemoveItemData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveItemPacket>(const Server::FieldRemoveItemPacket& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}

			if (Field.FieldItems.contains(packet.ObjectId))
			{
				Field.FieldItems.erase(packet.ObjectId);
			}
		}
	}
}
