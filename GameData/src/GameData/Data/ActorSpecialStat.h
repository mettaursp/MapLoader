#pragma once

#include <GameData/Enums/Stats.h>

namespace Maple
{
	namespace Game
	{
		struct ActorSpecialStat
		{
			Enum::StatAttributeSpecial Type;
			float Rate = 0;
			float Value = 0;
		};
	}
}
