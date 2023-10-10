#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldRemoveNpcData.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldRemoveNpcPacket>(const Server::FieldRemoveNpcPacket& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}

			const auto entry = Field.Npcs.find(packet.ActorId);

			if (entry == Field.Npcs.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "removing unknown npc: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			if (entry->second.Data == nullptr)
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "removing npc with unknown id " << PrintActor{ Field, packet.ActorId, ActorType::Npc } << std::endl;
				}
			}
			else
			{
				if constexpr (ParserUtils::Packets::PrintPacketOutput)
				{
					std::cout << TimeStamp << "removing " << PrintActor{ Field, packet.ActorId, ActorType::Npc } << std::endl;
				}
			}

			Field.Npcs.erase(entry);
			Field.Actors.erase(packet.ActorId);
		}
	}
}
