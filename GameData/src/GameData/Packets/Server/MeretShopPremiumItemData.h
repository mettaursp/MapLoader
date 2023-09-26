#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/MeretShopPremiumItemData.h>
#include <GameData/Enums/MaplePlayer.h>
#include <GameData/Enums/MapleItem.h>

namespace Maple
{
	namespace Game
	{
		struct MeretShopPremiumItemData
		{
			enum class MarketItemLabelEnum : unsigned char
			{
			};
			
			enum class CurrencyTypeEnum : unsigned char
			{
			};
			
			enum class TabIdEnum : unsigned char
			{
			};
			
			enum class MarketBannerLabelEnum : unsigned char
			{
			};
			
			Enum::ShopEntryId EntryId = (Enum::ShopEntryId)0;
			std::wstring Name;
			Enum::ShopEntryId ParentId = (Enum::ShopEntryId)0;
			MarketItemLabelEnum MarketItemLabel = (MarketItemLabelEnum)0;
			CurrencyTypeEnum CurrencyType = (CurrencyTypeEnum)0;
			unsigned long long Price = 0;
			unsigned long long SalePrice = 0;
			unsigned long long SellBeginTime = 0;
			unsigned long long SellEndTime = 0;
			bool RestockUnavailable = false;
			unsigned short RequiredMinLevel = 0;
			unsigned short RequiredMaxLevel = 0;
			Enum::JobFlags RequiredJob = (Enum::JobFlags)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			unsigned int Amount = 0;
			unsigned int ItemDuration = 0;
			unsigned int BonusQuantity = 0;
			TabIdEnum TabId = (TabIdEnum)0;
			MarketBannerLabelEnum MarketBannerLabel = (MarketBannerLabelEnum)0;
			std::string BannerName;
			Enum::TrophyId RequiredAchievementId = (Enum::TrophyId)0;
			unsigned int RequiredAchievementRank = 0;
			bool PcCafe = false;
		};
	}
}
