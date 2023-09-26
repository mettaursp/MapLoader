#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldRemovePlayerPacket.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldRemovePlayerPacket>(const Server::FieldRemovePlayerPacket& packet)
		{
			if (!Field.CurrentMap || packet.ActorId == Enum::ActorId::Null)
			{
				return;
			}

			const auto entry = Field.Players.find(packet.ActorId);

			if (entry == Field.Players.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "removing " << PrintActor{ Field, packet.ActorId, ActorType::Player } << std::endl;
				}

				return;
			}

			const auto& player = entry->second;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "removing " << PrintActor{ Field, packet.ActorId, ActorType::Player } << std::endl;
			}

			if (player.Pet)
			{
				player.Pet->Owner = nullptr;
			}

			Field.Players.erase(entry);
			Field.Actors.erase(packet.ActorId);
		}
	}
}
