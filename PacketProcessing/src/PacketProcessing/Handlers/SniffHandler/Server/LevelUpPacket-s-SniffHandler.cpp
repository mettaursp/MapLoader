#include "./../SniffHandler.h"

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
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;

						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}

					PacketStream().FoundUnknownValue = true;

					std::cout << "leveling up unknown actor: " << (unsigned int)packet.ActorId << std::endl;
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
			bool printOldLevel = packet.Level - 1 == oldLevel;

			if (Field.Players.contains(packet.ActorId))
			{
				const Player& player = Field.Players[packet.ActorId];

				unsigned short jobId = (unsigned short)player.JobCode;
				unsigned short jobRank = (jobId >= 10 && jobId <= 110) ? ((unsigned short)player.Job % 10) : 0;

				const auto jobEntry = JobNames.find(jobId);

				std::string jobName = jobEntry != JobNames.end() ? jobEntry->second : "<unknown>";

				std::cout << "player '" << player.Name << "' [" << jobName << JobSuffixes[jobRank] << "]";
			}
			else if (Field.Pets.contains(packet.ActorId))
			{
				const Pet& pet = Field.Pets[packet.ActorId];

				bool hasSkin = pet.SkinNpcId != Enum::NpcId::Null && pet.SkinNpcId != pet.NpcId;

				std::cout << (pet.ItemId != Enum::ItemInstanceId::Null ? "pet '" : "hungry '");

				if (pet.Name.size())
					std::cout << pet.Name;
				else
					std::cout << pet.NpcName;

				std::cout << "' '";

				if (pet.NpcName.size())
					std::cout << pet.NpcName;
				else
					std::cout << (unsigned int)pet.NpcId;

				if (hasSkin && pet.Npc)
				{
					std::cout << "' (Skin: '";

					if (pet.Npc->Name.size())
						std::cout << pet.Npc->Name;
					else
						std::cout << (unsigned int)pet.SkinNpcId;

					std::cout << "')";
				}
				else
				{
					std::cout << "'";
				}

				if (pet.Owner)
				{
					std::cout << " owned by '" << pet.Owner->Name << "'";
				}
			}
			else if (Field.Npcs.contains(packet.ActorId))
			{
				const Npc& npc = Field.Npcs[packet.ActorId];

				std::cout << "npc [" << (unsigned int)npc.NpcId << "] '" << (npc.Data ? npc.Data->Name : "<unknown>") << "'";
			}
			else
			{
				std::cout << "unknown actor type ";
			}

			std::cout << (unsigned int)packet.ActorId << levelMessage << " to " << packet.Level;

			if (printOldLevel)
			{
				std::cout << " from " << oldLevel;
			}

			std::cout << std::endl;
		}
	}
}
