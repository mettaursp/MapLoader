#pragma once

#include <GameData/Enums/Item.h>

namespace Maple
{
	namespace Game
	{
		struct PetLootSettingsData
		{
			bool Mesos = false;
			bool Merets = false;
			bool Other = false;
			bool Currency = false;
			bool Equipment = false;
			bool Consumable = false;
			bool Gemstone = false;
			bool Dropped = false;
			Enum::Rarity MinRarity = (Enum::Rarity)0;
			bool Enabled = false;
		};
	}
}
