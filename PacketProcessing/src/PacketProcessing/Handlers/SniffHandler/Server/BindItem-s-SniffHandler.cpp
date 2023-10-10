#include "./../SniffHandler.h"

#include <GameData/Packets\Server/BindItemData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::BindItemPacket>(const Server::BindItemPacket& packet)
		{
			Item* item = GetItem(packet.ItemInstanceId);

			if (item)
			{
				*item->Data = packet.ItemData;

				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << (item->Data->Binding.CharacterId != Enum::CharacterId::Null ? "binding item " : "unbinding item ") << PrintItem{ Field, packet.ItemInstanceId };

					std::cout << std::endl;
					std::cout << PrintItemStats{ Field, packet.ItemInstanceId };
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "attempting to changing binding on unregistered item instance " << packet.ItemInstanceId << std::endl;
				}
			}
		}
	}
}
