#pragma once

#include <GameData/Enums/StatAttributeBasic.h>

namespace Maple
{
	namespace Game
	{
		struct Stat
		{
			Enum::StatAttributeBasic Type = Enum::StatAttributeBasic::Hp;
			unsigned int Max = 0;
			unsigned int Base = 0;
			unsigned int Current = 0;
		};
	}
}
