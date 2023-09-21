#pragma once

#include <GameData/Enums/Item.h>
#include <vector>
#include <GameData/Packets\Server/PetLoadCollectionPacket.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetLoadCollectionPacket
			{
				struct PetEntry
				{
					Enum::PetId PetId = (Enum::PetId)0;
					Enum::Rarity PetRarity = (Enum::Rarity)0;
				};
				
				std::vector<PetEntry> Pets;
			};
		}
	}
}
