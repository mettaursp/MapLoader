#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Item.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetAddCollectionPacket
			{
				Enum::PetId PetId = (Enum::PetId)0;
				Enum::Rarity PetRarity = (Enum::Rarity)0;
			};
		}
	}
}
