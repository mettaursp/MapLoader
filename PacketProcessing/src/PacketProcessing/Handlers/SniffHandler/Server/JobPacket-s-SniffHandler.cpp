#include "./../SniffHandler.h"

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::JobPacket>(const Server::JobPacket& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}

			const auto playerEntry = Field.Players.find(packet.ActorId);

			if (playerEntry == Field.Players.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "changing skill tree with unrecognized player: " << PrintActor{ Field, packet.ActorId, ActorType::Player } << std::endl;
				}

				return;
			}

			Player& player = playerEntry->second;

			if (packet.Mode == Server::JobPacket::ModeEnum::Reset)
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "resetting skill tree of " << PrintActor{ Field, packet.ActorId, ActorType::Player } << std::endl;
				}

				player.Skills = {};

				return;
			}

			player.AddSkills(*this, packet.SkillTree);
		}
	}
}
