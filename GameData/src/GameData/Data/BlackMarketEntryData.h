#pragma once

#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Item.h>

namespace Maple
{
	namespace Game
	{
		struct BlackMarketEntryData
		{
			Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
			unsigned long long TimeListed = 0;
			unsigned long long TimeListed2 = 0;
			unsigned long long TimeExpires = 0;
			unsigned int Amount = 0;
			unsigned long long CostPerItem = 0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			Enum::AccountId ListerAccountId = (Enum::AccountId)0;
			ItemData ItemData;
		};
	}
}
