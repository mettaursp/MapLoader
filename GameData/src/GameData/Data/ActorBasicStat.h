#pragma once

#include <GameData/Enums/Stats.h>

namespace Maple
{
	namespace Game
	{
		struct ActorBasicStat
		{
			Enum::StatAttributeBasic Type = (Enum::StatAttributeBasic)0;
			unsigned long long Max = 0;
			unsigned long long Base = 0;
			unsigned long long Current = 0;
			float Rate = 0;
		};
	}
}
