#pragma once

#include <GameData/Enums/MapleStats.h>

namespace Maple
{
	namespace Game
	{
		struct ActorSpecialStat
		{
			Enum::StatAttributeSpecial Type = (Enum::StatAttributeSpecial)0;
			float Rate = 0;
			float Value = 0;
		};
	}
}
