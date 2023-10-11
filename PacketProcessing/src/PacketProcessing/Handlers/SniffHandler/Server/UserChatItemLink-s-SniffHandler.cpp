#include "./../SniffHandler.h"

#include <GameData/Packets\Server/UserChatItemLinkData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::UserChatItemLinkPacket>(const Server::UserChatItemLinkPacket& packet)
		{
			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				if (packet.Items.size())
				{
					std::cout << TimeStamp << "user linking items " << std::endl;
				}
			}

			for (const auto& entry : packet.Items)
			{
				Item* item = RegisterItem(entry.ItemInstanceId, entry.ItemId);

				item->Amount = 1;
				item->Rarity = entry.Rarity;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout <<  "\tlinked item " << PrintItem{ Field, entry.ItemInstanceId } << std::endl;
					std::cout << PrintItemStats{ Field, entry.ItemInstanceId, 2 };
				}
			}
		}
	}
}
