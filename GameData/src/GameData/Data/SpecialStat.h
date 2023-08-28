#pragma once

#include <GameData/Enums/StatAttributeSpecial.h>

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
