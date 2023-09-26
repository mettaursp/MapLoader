#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldAddNpcPacket.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldAddNpcPacket>(const Server::FieldAddNpcPacket& packet)
		{
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

						std::cout << TimeStamp << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}

					PacketStream().FoundUnknownValue = true;

					std::cout << TimeStamp << "adding npc with id thats already in use: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			const auto npcEntry = Data->Npcs.find(packet.NpcId);

			auto& actor = Field.Actors[packet.ActorId];

			actor.Field = &Field;
			actor.ActorId = packet.ActorId;
			actor.Level = packet.Level;
			actor.Type = ActorType::Npc;

			auto& npc = Field.Npcs[packet.ActorId];

			if (npcEntry != Data->Npcs.end())
			{
				npc.Name = npcEntry->second.Name;
				npc.Data = &npcEntry->second;
			}

			npc.NpcId = packet.NpcId;
			npc.Actor = &actor;

			actor.AddEffects(*this, packet.Effects);

			if (npcEntry == Data->Npcs.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "adding npc with unknown id " << (unsigned int)packet.NpcId << "' Lv" << packet.Level << " as actor " << (unsigned int)packet.ActorId << std::endl;
				}

				std::stringstream name;
				name << (unsigned int)packet.NpcId;
				npc.Name = name.str();
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "adding " << PrintActor{ Field, packet.ActorId, ActorType::Npc } << std::endl;
				}
			}
		}
	}
}
