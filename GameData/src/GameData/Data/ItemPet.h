#pragma once

#include <string>

namespace Maple
{
	namespace Game
	{
		struct ItemPet
		{
			std::wstring Name;
			unsigned long long Exp = 0;
			unsigned int EvolvePoints = 0;
			unsigned int Level = 0;
			bool HasItems = false;
		};
	}
}
