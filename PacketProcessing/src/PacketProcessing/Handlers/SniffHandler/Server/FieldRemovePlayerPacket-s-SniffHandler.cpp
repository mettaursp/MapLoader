#include "./../SniffHandler.h"

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
				const auto jobEntry = JobNames.find(jobId);

				std::string jobName = jobEntry != JobNames.end() ? jobEntry->second : "<unknown>";

				std::cout << "removing player '" << player.Name << "' [" << jobName << JobSuffixes[jobRank] << "] Lv" << player.Actor->Level << " as actor " << (unsigned int)packet.ActorId << std::endl;
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
