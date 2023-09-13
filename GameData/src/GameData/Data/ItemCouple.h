#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

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
