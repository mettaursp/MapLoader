#pragma once

#include <GameData/Data/ItemDecalCustomization.h>
#include <GameData/Data/DyeColor.h>
#include <GameData/Data/ItemCapCustomization.h>
#include <GameData/Data/ItemHairCustomization.h>

namespace Maple
{
	namespace Game
	{
		struct ItemCustomization
		{
			DyeColor DyeColor;
			ItemCapCustomization Cap;
			ItemHairCustomization Hair;
			ItemDecalCustomization Decal;
		};
	}
}
