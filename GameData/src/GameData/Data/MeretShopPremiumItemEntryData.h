#pragma once

#include <GameData/Enums/Player.h>
#include <GameData/Enums/Handles.h>
#include <string>
#include <GameData/Data/MeretShopPremiumItemData.h>
#include <GameData/Enums/Item.h>
#include <GameData/Data/MeretShopPremiumItemEntryData.h>
#include <vector>

namespace Maple
{
	namespace Game
	{
		struct MeretShopPremiumItemEntryData
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
			
			struct QuantityEntry
			{
				bool HasEntry = false;
				MeretShopPremiumItemData EntryData;
				bool HasUnknown = false;
			};
			
			Enum::ShopEntryId EntryId = (Enum::ShopEntryId)0;
			std::wstring Name;
			MarketItemLabelEnum MarketItemLabel = (MarketItemLabelEnum)0;
			CurrencyTypeEnum CurrencyType = (CurrencyTypeEnum)0;
			unsigned long long Price = 0;
			unsigned long long SalePrice = 0;
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
			std::vector<QuantityEntry> AdditionalQuantities;
		};
	}
}
