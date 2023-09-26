#pragma once

#include <vector>
#include <GameData/Packets\Server/PetLoadCollectionPacket.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>

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
