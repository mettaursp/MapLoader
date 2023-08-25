#pragma once

#include <GameData/Enums/StatAttributeBasic.h>

namespace Maple
{
	namespace Game
	{
		struct StatLong
		{
			Enum::StatAttributeBasic Type;
			unsigned long long Max = 0;
			unsigned long long Base = 0;
			unsigned long long Current = 0;
		};
	}
}
