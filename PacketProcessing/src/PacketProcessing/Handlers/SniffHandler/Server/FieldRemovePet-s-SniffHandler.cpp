#include "./../SniffHandler.h"

#include <GameData/Packets\Server/FieldRemovePetPacket.h>
#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldRemovePetPacket>(const Server::FieldRemovePetPacket& packet)
		{
			if (!Field.CurrentMap)
			{
				return;
			}

			const auto entry = Field.Pets.find(packet.ActorId);

			if (entry == Field.Pets.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					FoundUnknownValue();

					std::cout << TimeStamp << "removing unknown pet: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			const auto& pet = entry->second;

			bool hasSkin = pet.SkinNpcId != Enum::NpcId::Null && pet.SkinNpcId != pet.NpcId;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << TimeStamp << "removing " << PrintActor{ Field, packet.ActorId, ActorType::Pet } << std::endl;
			}

			if (pet.Owner)
			{
				pet.Owner->Pet = nullptr;
			}

			Field.Pets.erase(entry);
			Field.Npcs.erase(packet.ActorId);
			Field.Actors.erase(packet.ActorId);
		}
	}
}
