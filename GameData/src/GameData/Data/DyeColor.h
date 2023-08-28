#pragma once

#include <Engine/Math/Color4I.h>

namespace Maple
{
	namespace Game
	{
		struct DyeColor
		{
			Color4I Primary;
			Color4I Secondary;
			Color4I Tertiary;
			unsigned int Index = 0;
		};
	}
}
