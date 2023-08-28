#pragma once

#include <Engine/Math/Vector3S.h>

namespace Maple
{
	namespace Game
	{
		struct ItemHairCustomization
		{
			float BackLength = 0;
			Vector3S BackPosition1;
			Vector3S BackPosition2;
			float FrontLength = 0;
			Vector3S FrontPosition1;
			Vector3S FrontPosition2;
		};
	}
}
