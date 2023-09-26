#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldAddItemPacket.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldAddItemPacket>(const Server::FieldAddItemPacket& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}

			Item* item = RegisterItem(packet.ItemInstanceId, packet.ItemId);

			item->Amount = packet.Amount;
			item->Rarity = packet.Rarity;

			if ((unsigned int)packet.ItemId < 90000001 || (unsigned int)packet.ItemId > 90000003)
			{
				*item->Data = packet.ItemData;
			}

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "adding field item " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
			}
		}
	}
}
