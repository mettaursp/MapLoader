#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

namespace Maple
{
	namespace Game
	{
		struct ItemBinding
		{
			Enum::CharacterId CharacterId;
			std::wstring Name;
		};
	}
}
