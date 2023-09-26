#pragma once

#include <GameData/Data/ItemData.h>
#include <string>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/ShopLoadItemsPacket.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Packets\Server/BuyPeriodData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopLoadItemsPacket
			{
				enum class CurrencyIdEnum
				{
				};
				
				struct ItemEntry
				{
					Enum::ShopEntryId EntryId = (Enum::ShopEntryId)0;
					Enum::ItemId ItemId = (Enum::ItemId)0;
					CurrencyIdEnum CurrencyId = (CurrencyIdEnum)0;
					unsigned int Price = 0;
					unsigned int Price2 = 0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					unsigned int MaxStock = 0;
					unsigned int TotalSold = 0;
					std::string ShopCategory;
					Enum::TrophyId AchievementRequired = (Enum::TrophyId)0;
					unsigned short BundleSize = 0;
					std::string CurrencyIdString;
					bool HasBuyPeriod = false;
					Maple::Game::BuyPeriodData BuyPeriod;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<ItemEntry> Items;
			};
		}
	}
}
