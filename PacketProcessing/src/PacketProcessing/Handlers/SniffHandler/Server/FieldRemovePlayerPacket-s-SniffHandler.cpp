#include "./../SniffHandler.h"

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		const std::string jobSuffixes[3] = { "", " II" };
		const std::unordered_map<unsigned short, std::string> jobNames = {
			{ 1, "Beginner" },
			{ 10, "Knight" },
			{ 20, "Berserker" },
			{ 30, "Wizard" },
			{ 40, "Priest" },
			{ 50, "Archer" },
			{ 60, "HeavyGunner" },
			{ 70, "Thief" },
			{ 80, "Assassin" },
			{ 90, "Runeblade" },
			{ 100, "Striker" },
			{ 110, "Soulbinder" },
			{ 999, "GameMaster" },
		};

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
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;

						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}

					PacketStream().FoundUnknownValue = true;

					std::cout << "removing unknown player: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			const auto& player = entry->second;

			unsigned short jobId = (unsigned short)player.JobCode;
			unsigned short jobRank = (jobId >= 10 && jobId <= 110) ? ((unsigned short)player.Job % 10) : 0;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				const auto jobEntry = jobNames.find(jobId);

				std::string jobName = jobEntry != jobNames.end() ? jobEntry->second : "<unknown>";

				std::cout << "removing player '" << player.Name << "' [" << jobName << jobSuffixes[jobRank] << "] Lv" << player.Actor->Level << " as actor " << (unsigned int)packet.ActorId << std::endl;
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
