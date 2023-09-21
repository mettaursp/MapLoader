#pragma once

#include <GameData/Data/PetPotionSettingsData.h>
#include <vector>
#include <GameData/Enums/Handles.h>

namespace Maple
{
	namespace Game
	{
		struct PetPotionSettingsData
		{
			struct SlotEntry
			{
				unsigned int ThresholdIndex = 0;
				float Threshold = 0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
			};
			
			std::vector<SlotEntry> Slots;
		};
	}
}
