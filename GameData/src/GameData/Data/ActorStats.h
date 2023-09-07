#pragma once

#include <vector>
#include <GameData/Data/ActorBasicStat.h>
#include <GameData/Data/ActorSpecialStat.h>

namespace Maple
{
	namespace Game
	{
		struct ActorStats
		{
			std::vector<ActorBasicStat> Basic;
			std::vector<ActorSpecialStat> Special;
		};
	}
}
