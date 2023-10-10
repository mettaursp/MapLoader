#pragma once

namespace Enum
{
	enum class HitType
	{
		Normal = 0,
		Critical = 1,
		Miss = 2,
		Block = 3,
		Unknown4 = 4,
		Unknown8 = 8
	};
	
	enum class NpcType : unsigned long long
	{
		Enemy = 0,
		Ally = 1,
		Friendly = 2
	};
}
