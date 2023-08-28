#pragma once

#include <vector>
#include <GameData/Data/BasicStat.h>

namespace Maple
{
	namespace Game
	{
		struct ItemEnchantment
		{
			unsigned int Level = 0;
			unsigned int EnchantExp = 0;
			unsigned char EnchantCharges = 0;
			bool CanRepackage = false;
			unsigned int Charges = 0;
			std::vector<BasicStat> Basic;
		};
	}
}
