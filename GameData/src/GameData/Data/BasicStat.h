#pragma once

#include <GameData/Enums/StatAttributeBasic.h>

namespace Maple
{
	namespace Game
	{
		struct BasicStat
		{
			Enum::StatAttributeBasic Type;
			int Value = 0;
			float Rate = 0;
		};
	}
}
