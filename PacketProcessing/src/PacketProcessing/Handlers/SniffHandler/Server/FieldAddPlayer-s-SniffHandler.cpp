#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldAddPlayerData.h>
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
					FoundUnknownValue();

					std::cout << TimeStamp << "adding player with id thats already in use: " << PrintActor{ Field, packet.ActorId, ActorType::Player } << std::endl;
				}

				return;
			}

			auto& actor = Field.Actors[packet.ActorId];

			actor.Field = &Field;
			actor.ActorId = packet.ActorId;
			actor.Level = packet.Character.Level;
			actor.Type = ActorType::Player;

			auto& player = Field.Players[packet.ActorId];

			player.Name = packet.Character.Name;
			player.Job = packet.Character.Job;
			player.JobCode = packet.Character.JobCode;
			player.Actor = &actor;
			player.IsCurrentPlayer = PlayerId == packet.ActorId;

			CheckBaseStats(player.JobCode, actor.Level, packet.Stats, Version != 12);

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "adding " << PrintActor{ Field, packet.ActorId, ActorType::Player } << std::endl;
			}

			actor.AddEffects(*this, packet.Effects);
			player.AddSkills(*this, packet.SkillTree);

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
						const auto& pet = *player.Pet;

						bool hasSkin = pet.SkinNpcId != Enum::NpcId::Null && pet.SkinNpcId != pet.NpcId;

						std::cout << "with " << PrintActor{ Field, pet.Actor->ActorId, ActorType::Pet } << std::endl;
					}
				}
			}
		}
	}
}
