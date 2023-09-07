#include "./../SniffHandler.h"

#include <ParserUtils/PacketParsing.h>

namespace Networking
{
	namespace Packets
	{
		template <>
		void SniffHandler::PacketParsed<Server::FieldAddPetPacket>(const Server::FieldAddPetPacket& packet)
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

					std::cout << "adding pet with id thats already in use: " << (unsigned int)packet.ActorId << std::endl;
				}

				return;
			}

			Enum::NpcId petSkinId = packet.PetSkinId;

			if (petSkinId == (Enum::NpcId)61000152)
			{
				petSkinId = (Enum::NpcId)60000064;
			}

			const auto npcEntry = Data->Npcs.find(packet.PetNpcId);
			const auto skinEntry = Data->Npcs.find(petSkinId);

			unsigned int npcId = (unsigned int)packet.PetNpcId;
			unsigned int skinId = (unsigned int)petSkinId;
			unsigned int ownerId = (unsigned int)packet.OwnerActorId;
			std::string npcName = "";
			std::string skinName = "";
			std::wstring ownerName = L"";

			bool hasSkin = petSkinId != Enum::NpcId::Null && petSkinId != packet.PetNpcId;

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

					std::cout << "adding pet with unknown npc id " << npcId << "' as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
			else
			{
				npcName = npcEntry->second.Name;
			}

			if (hasSkin && skinEntry == Data->Npcs.end())
			{
				if constexpr (ParserUtils::Packets::PrintUnknownValues)
				{
					if (!Field.PrintedMap)
					{
						Field.PrintedMap = true;

						std::cout << "entered map [" << (unsigned int)Field.MapId << "] '" << Field.CurrentMap->Name << "'" << std::endl;
					}

					PacketStream().FoundUnknownValue = true;

					std::cout << "adding pet with unknown skin id " << skinId << "' as actor " << (unsigned int)packet.ActorId << std::endl;
				}
			}
			else
			{
				skinName = skinEntry->second.Name;
			}

			const auto ownerEntry = Field.Players.find(packet.OwnerActorId);

			if (ownerEntry != Field.Players.end())
			{
				ownerName = ownerEntry->second.Name;
			}

			if constexpr (ParserUtils::Packets::PrintPacketOutput)
			{
				std::cout << (packet.PetItemInstanceId == Enum::ItemInstanceId::Null ? "adding hungry '" : "adding pet '");

				if (packet.Name.size())
					std::cout << packet.Name;
				else
					std::cout << npcName;

				std::cout << "' '";

				if (npcName.size())
					std::cout << npcName;
				else
					std::cout << skinId;

				if (hasSkin && skinEntry != Data->Npcs.end())
				{
					std::cout << "' (Skin: '";

					if (skinName.size())
						std::cout << skinName;
					else
						std::cout << skinId;

					std::cout << "')";
				}
				else
				{
					std::cout << "'";
				}

				std::cout << " Lv" << packet.Level << " as actor " << (unsigned int)packet.ActorId;

				if (ownerEntry != Field.Players.end())
				{
					std::cout << " belonging to player '" << ownerName << "' (" << ownerId << ")";
				}

				std::cout << std::endl;
			}


			auto& actor = Field.Actors[packet.ActorId];

			actor.ActorId = packet.ActorId;
			actor.Level = packet.Level;

			auto& npc = Field.Npcs[packet.ActorId];

			npc.Name = skinName;
			npc.Data = skinEntry == Data->Npcs.end() ? nullptr : &skinEntry->second;
			npc.NpcId = petSkinId;
			npc.Actor = &actor;

			auto& pet = Field.Pets[packet.ActorId];

			pet.Name = packet.Name;
			pet.NpcName = npcName;
			pet.NpcId = packet.PetNpcId;
			pet.SkinNpcId = petSkinId;
			pet.Actor = &actor;
			pet.Npc = &npc;
			pet.Owner = ownerEntry == Field.Players.end() ? nullptr : &ownerEntry->second;
			pet.ItemId = packet.PetItemInstanceId;

			if (pet.Owner)
			{
				if (pet.Owner->Pet)
				{
					pet.Owner->Pet->Owner = nullptr;
				}

				pet.Owner->Pet = &pet;
			}
		}
	}
}
