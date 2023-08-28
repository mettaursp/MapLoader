#pragma once

#include <GameData/Data/BonusStats.h>

namespace Maple
{
	namespace Game
	{
		struct ItemStats
		{
			BonusStats Constant;
			BonusStats Static;
			BonusStats Random;
			BonusStats Title;
			BonusStats Empowerment1;
			BonusStats Empowerment2;
			BonusStats Empowerment3;
			BonusStats Empowerment4;
			BonusStats Empowerment5;
		};
	}
}
