#pragma once

#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <string>
#include <GameData/Enums/Item.h>

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
