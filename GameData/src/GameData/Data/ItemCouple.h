#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

namespace Maple
{
	namespace Game
	{
		struct ItemCouple
		{
			Enum::CharacterId CharacterId;
			std::wstring Name;
			bool IsCreator = false;
		};
	}
}
