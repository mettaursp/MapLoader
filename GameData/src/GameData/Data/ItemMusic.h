#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

namespace Maple
{
	namespace Game
	{
		struct ItemMusic
		{
			unsigned int Length = 0;
			unsigned int Instrument = 0;
			std::wstring Title;
			std::wstring Author;
			Enum::CharacterId AuthorId;
			bool IsLocked = false;
		};
	}
}
