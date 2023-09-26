#pragma once

#include <string>

namespace Maple
{
	namespace Game
	{
		struct PetProfileData
		{
			std::wstring Name;
			unsigned long long Exp = 0;
			unsigned short Level = 0;
		};
	}
}
