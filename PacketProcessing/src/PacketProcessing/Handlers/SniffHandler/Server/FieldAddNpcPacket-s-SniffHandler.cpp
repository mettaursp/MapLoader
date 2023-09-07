#include "./../SniffHandler.h"

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
		
						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}
		
					PacketStream().FoundUnknownValue = true;
		
					std::cout << "adding npc with id thats already in use: " << (unsigned int)packet.ActorId << std::endl;
				}
		
				return;
			}
		
			const auto npcEntry = Data->Npcs.find(packet.NpcId);
		
			if (npcEntry == Data->Npcs.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;
		
						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}
		
					PacketStream().FoundUnknownValue = true;
		
					std::cout << "adding npc with unknown id " << (unsigned int)packet.NpcId << "' Lv" << packet.Level << " as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << "adding npc [" << (unsigned int)packet.NpcId << "] '" << npcEntry->second.Name << "' Lv" << packet.Level << " as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
		
			auto& actor = Field.Actors[packet.ActorId];
		
			actor.ActorId = packet.ActorId;
			actor.Level = packet.Level;
		
			auto& npc = Field.Npcs[packet.ActorId];
		
			npc.Name = npcEntry->second.Name;
			npc.Data = &npcEntry->second;
			npc.NpcId = packet.NpcId;
			npc.Actor = &actor;
		}
	}
}
