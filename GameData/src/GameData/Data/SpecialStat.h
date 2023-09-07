#pragma once

#include <GameData/Enums/Stats.h>

namespace Maple
{
	namespace Game
	{
		struct SpecialStat
		{
			Enum::StatAttributeSpecial Type;
			float Value = 0;
			float Rate = 0;
		};
	}
}
