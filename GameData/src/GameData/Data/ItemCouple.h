#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>

namespace Maple
{
	namespace Game
	{
		struct ItemCouple
		{
			Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			std::wstring Name;
			bool IsCreator = false;
		};
	}
}
