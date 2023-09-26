#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>

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
			Enum::CharacterId AuthorId = (Enum::CharacterId)0;
			bool IsLocked = false;
		};
	}
}
