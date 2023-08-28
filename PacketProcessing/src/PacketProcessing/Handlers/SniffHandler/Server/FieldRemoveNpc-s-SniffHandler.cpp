#include "./../SniffHandler.h"
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveNpc>(const Server::FieldRemoveNpc& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}
		
			const auto entry = Field.Npcs.find((unsigned int)packet.ActorId);
		
			if (entry == Field.Npcs.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;
		
						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}
		
					PacketStream.FoundUnknownValue = true;
		
					std::cout << "removing unknown npc: " << (unsigned int)packet.ActorId << std::endl;
				}
		
				return;
			}
		
			if (entry->second.Data == nullptr)
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;
		
						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}
		
					PacketStream.FoundUnknownValue = true;
		
					std::cout << "removing npc with unknown id " << (unsigned int)entry->second.NpcId << "' as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintOutput)
				{
					std::cout << "removing npc [" << (unsigned int)entry->second.NpcId << "] '" << entry->second.Data->Name << "' as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
		
			Field.Npcs.erase(entry);
		}
	}
}
