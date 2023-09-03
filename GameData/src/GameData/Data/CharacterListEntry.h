#pragma once

#include <string>
#include <GameData/Data/CharacterEquipment.h>
#include <GameData/Data/CharacterData.h>

namespace Maple
{
	namespace Game
	{
		struct CharacterListEntry
		{
			CharacterData Character;
			std::wstring ProfileUrl;
			unsigned long long DeleteTime = 0;
			CharacterEquipment CharacterEquipment;
		};
	}
}
