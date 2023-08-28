#pragma once

#include <vector>
#include <GameData/Data/BasicStat.h>
#include <GameData/Data/SpecialStat.h>

namespace Maple
{
	namespace Game
	{
		struct BonusStats
		{
			std::vector<BasicStat> Basic;
			std::vector<SpecialStat> Special;
		};
	}
}
