#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Maple
{
	namespace Game
	{
		struct EffectStats
		{
			unsigned int StartTime = 0;
			unsigned int EndTime = 0;
			Enum::EffectId EffectId = (Enum::EffectId)0;
			Enum::EffectLevel EffectLevel = (Enum::EffectLevel)0;
			unsigned int Stacks = 0;
		};
	}
}
