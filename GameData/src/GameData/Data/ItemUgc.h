#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>

namespace Maple
{
	namespace Game
	{
		struct ItemUgc
		{
			std::wstring FileName;
			std::wstring Name;
			Enum::AccountId AccountId = (Enum::AccountId)0;
			Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			std::wstring Author;
			unsigned long long CreationTime = 0;
			std::wstring Url;
		};
	}
}
