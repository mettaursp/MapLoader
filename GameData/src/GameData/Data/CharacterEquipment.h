#pragma once

#include <vector>
#include <GameData/Data/EquipmentData.h>

namespace Maple
{
	namespace Game
	{
		struct CharacterEquipment
		{
			std::vector<EquipmentData> Equipment;
			std::vector<EquipmentData> Badges;
			bool HasSkin = false;
			std::vector<EquipmentData> Skins;
		};
	}
}
