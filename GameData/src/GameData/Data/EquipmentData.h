#pragma once

#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <string>
#include <GameData/Enums/SlotType.h>
#include <GameData/Enums/Rarity.h>

namespace Maple
{
	namespace Game
	{
		struct EquipmentData
		{
			Enum::SlotType Slot;
			Enum::ItemId ItemId;
			Enum::ItemInstanceId ItemInstanceId;
			std::wstring SlotName;
			Enum::Rarity Rarity;
			ItemData Data;
		};
	}
}
