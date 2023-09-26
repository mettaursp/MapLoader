#include "./../SniffHandler.h"

#include <GameData/Packets\Server/LevelUpPacket.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::LevelUpPacket>(const Server::LevelUpPacket& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}

			const auto entry = Field.Actors.find(packet.ActorId);

			if (entry == Field.Actors.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "leveling up unknown actor: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			Actor& actor = entry->second;

			unsigned short oldLevel = actor.Level;

			actor.Level = packet.Level;

			if constexpr (!ParserUtils::Packets::PrintPacketOutput)
			{
				return;
			}

			if (oldLevel == actor.Level)
			{
				return;
			}

			const char* levelMessage = packet.Level > oldLevel ? " leveled up" : " changed level";
			bool printOldLevel = (packet.Level - 1) != oldLevel;

			std::cout << TimeStamp << PrintActor{ Field, packet.ActorId } << levelMessage << " to " << packet.Level;

			if (printOldLevel)
			{
				std::cout << " from " << oldLevel;
			}

			std::cout << std::endl;
		}
	}
}
