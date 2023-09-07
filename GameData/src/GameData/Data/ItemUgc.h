#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

namespace Maple
{
	namespace Game
	{
		struct ItemUgc
		{
			std::wstring FileName;
			std::wstring Name;
			Enum::AccountId AccountId;
			Enum::CharacterId CharacterId;
			std::wstring Author;
			unsigned long long CreationTime = 0;
			std::wstring Url;
		};
	}
}
