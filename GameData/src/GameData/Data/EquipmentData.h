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
			Enum::SlotType Slot = (Enum::SlotType)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			std::wstring SlotName;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			ItemData Data;
		};
	}
}
