#include "./../SniffHandler.h"

#include <GameData/Packets\Server/ItemSkinPutOnData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::ItemSkinPutOnPacket>(const Server::ItemSkinPutOnPacket& packet)
		{
			Item* item = RegisterItem(packet.ItemInstanceId, packet.ItemId);

			item->Amount = 1;
			item->Rarity = packet.Rarity;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "putting on skin item " << PrintItem{ Field, packet.ItemInstanceId } << std::endl;
				std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
			}
		}
	}
}
