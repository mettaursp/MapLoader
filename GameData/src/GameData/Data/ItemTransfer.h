#pragma once

#include <GameData/Data/ItemBinding.h>

namespace Maple
{
	namespace Game
	{
		struct ItemTransfer
		{
			unsigned int TransferFlags = 0;
			unsigned int RemainingTrades = 0;
			unsigned int RemainingPackages = 0;
			bool IsBound = false;
			ItemBinding ItemBinding;
		};
	}
}
