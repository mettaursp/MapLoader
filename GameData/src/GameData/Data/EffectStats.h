#pragma once

#include <GameData/Enums/Handles.h>

namespace Maple
{
	namespace Game
	{
		struct EffectStats
		{
			unsigned int StartTime = 0;
			unsigned int EndTime = 0;
			Enum::EffectId EffectId;
			Enum::EffectLevel EffectLevel;
			unsigned int Stacks = 0;
		};
	}
}
