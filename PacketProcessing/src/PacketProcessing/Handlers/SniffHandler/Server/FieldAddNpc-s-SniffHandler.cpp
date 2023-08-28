#include "./../SniffHandler.h"
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldAddNpc>(const Server::FieldAddNpc& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}
		
			const auto actorEntry = Field.Npcs.find((unsigned int)packet.ActorId);
		
			if (actorEntry != Field.Npcs.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;
		
						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}
		
					PacketStream.FoundUnknownValue = true;
		
					std::cout << "adding npc with id thats already in use: " << (unsigned int)packet.ActorId << std::endl;
				}
		
				return;
			}
		
			const auto npcEntry = Data->Npcs.find((unsigned int)packet.NpcId);
		
			if (npcEntry == Data->Npcs.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;
		
						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}
		
					PacketStream.FoundUnknownValue = true;
		
					std::cout << "adding npc with unknown id " << (unsigned int)packet.NpcId << "' as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintOutput)
				{
					std::cout << "adding npc [" << (unsigned int)packet.NpcId << "] '" << npcEntry->second.Name << "' as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
		
			unsigned int id = (unsigned int)packet.ActorId;
		
			auto& actor = Field.Actors[id];
		
			actor.ActorId = id;
		
			auto& npc = Field.Npcs[id];
		
			npc.Data = &npcEntry->second;
			npc.NpcId = (unsigned int)packet.NpcId;
			npc.Actor = &actor;
		}
	}
}
