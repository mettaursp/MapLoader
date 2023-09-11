#include "./../SniffHandler.h"

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldAddPlayerPacket>(const Server::FieldAddPlayerPacket& packet)
		{
			if (packet.Character.AccountId == AccountId)
			{
				CharacterId = packet.Character.CharacterId;
				PlayerId = packet.ActorId;
			}

			if (!Field.CurrentMap)
			{
				return;
			}

			const auto actorEntry = Field.Actors.find(packet.ActorId);

			if (actorEntry != Field.Actors.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;

						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}

					PacketStream().FoundUnknownValue = true;

					std::cout << "adding player with id thats already in use: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			unsigned short jobId = (unsigned short)packet.Character.JobCode;
			unsigned short jobRank = (jobId >= 10 && jobId <= 110) ? ((unsigned short)packet.Character.Job % 10) : 0;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				const auto jobEntry = JobNames.find(jobId);

				std::string jobName = jobEntry != JobNames.end() ? jobEntry->second : "<unknown>";

				std::cout << "adding player '" << packet.Character.Name << "' [" << jobName << JobSuffixes[jobRank] << "] Lv" << packet.Character.Level << " as actor " << (unsigned int)packet.ActorId << std::endl;
			}

			auto& actor = Field.Actors[packet.ActorId];

			actor.ActorId = packet.ActorId;
			actor.Level = packet.Character.Level;

			auto& player = Field.Players[packet.ActorId];

			player.Name = packet.Character.Name;
			player.Job = packet.Character.Job;
			player.JobCode = packet.Character.JobCode;
			player.Actor = &actor;

			CheckBaseStats(player.JobCode, actor.Level, packet.Stats, Version != 12);

			if (packet.HasPet)
			{
				const auto petEntry = Field.Pets.find(packet.Pet.ActorId);

				if (petEntry != Field.Pets.end())
				{
					player.Pet = &petEntry->second;

					if (player.Pet->Owner)
					{
						player.Pet->Owner->Pet = nullptr;
					}

					player.Pet->Owner = &player;

					if constexpr (ParserUtils::Packets::PrintPacketOutput)
					{
						const auto & pet = *player.Pet;

						bool hasSkin = pet.SkinNpcId != Enum::NpcId::Null && pet.SkinNpcId != pet.NpcId;

						std::cout << "with pet '";

						if (pet.Name.size())
							std::cout << pet.Name;
						else
							std::cout << pet.NpcName;

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

						std::cout << " Lv" << pet.Actor->Level << " as actor " << (unsigned int)packet.ActorId;

						if (pet.Owner)
						{
							std::cout << " belonging to player '" << pet.Owner->Name << "' (" << (unsigned int)pet.Owner->Actor->ActorId << ")";
						}

						std::cout << std::endl;
					}
				}
			}
		}
	}
}
