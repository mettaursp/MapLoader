#include "./../SniffHandler.h"

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
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;

						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}

					PacketStream().FoundUnknownValue = true;

					std::cout << "removing unknown pet: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			const auto& pet = entry->second;

			bool hasSkin = pet.SkinNpcId != Enum::NpcId::Null && pet.SkinNpcId != pet.NpcId;

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << (pet.ItemId != Enum::ItemInstanceId::Null ? "removing pet '" : "removing hungry '");
				
				if (pet.Name.size())
					std::cout << pet.Name;
				else
					std::cout << pet.NpcName;

				std::cout << "' '";

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
