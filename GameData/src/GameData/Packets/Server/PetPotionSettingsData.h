#pragma once

#include <GameData/Packets\Server/PetPotionSettingsData.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>

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
