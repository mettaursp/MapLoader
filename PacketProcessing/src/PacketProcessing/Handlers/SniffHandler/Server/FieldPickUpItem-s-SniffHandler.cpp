#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldPickUpItemData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldPickUpItemPacket>(const Server::FieldPickUpItemPacket& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}

			//if (Field.FieldItems.contains(packet.ObjectId))
			//{
			//	Field.FieldItems.erase(packet.ObjectId);
			//}
		}
	}
}
