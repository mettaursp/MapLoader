#pragma once

#include <GameData/Data/BonusStats.h>

namespace Maple
{
	namespace Game
	{
		struct ItemLimitBreak
		{
			unsigned int Level = 0;
			BonusStats Stats;
		};
	}
}
