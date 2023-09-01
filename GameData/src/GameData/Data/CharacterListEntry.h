#pragma once

#include <string>
#include <GameData/Data/CharacterData.h>
#include <vector>
#include <GameData/Data/EquipmentData.h>

namespace Maple
{
	namespace Game
	{
		struct CharacterListEntry
		{
			CharacterData Character;
			std::wstring ProfileUrl;
			unsigned long long DeleteTime = 0;
			std::vector<EquipmentData> Equipment;
			std::vector<EquipmentData> Badges;
			bool HasSkin = false;
			std::vector<EquipmentData> Skins;
		};
	}
}
