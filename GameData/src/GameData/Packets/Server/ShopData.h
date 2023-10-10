#pragma once

#include <vector>
#include <string>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MaplePlayer.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>

namespace Maple
{
	namespace Game
	{
		struct BuyPeriodData
		{
			enum class DayOfWeekEnum : unsigned char
			{
				Sunday = 1,
				Monday = 2,
				Tuesday = 3,
				Wednesday = 4,
				Thursday = 5,
				Friday = 6,
				Saturday = 7
			};
			
			struct DayTimeEntry
			{
				unsigned int StartTime = 0;
				unsigned int EndTime = 0;
			};
			
			struct DayEntry
			{
				DayOfWeekEnum DayOfWeek = (DayOfWeekEnum)0;
			};
			
			bool HasSpecificTime = false;
			unsigned long long StartTime = 0;
			unsigned long long EndTime = 0;
			bool HasSpecificDays = false;
			std::vector<DayTimeEntry> DayTimes;
			std::vector<DayEntry> Days;
		};
		
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
namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopErrorPacket
			{
				unsigned int Message = 0;
				unsigned int StringId = 0;
			};
			
			struct ShopLoadNewPacket
			{
				struct ItemEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					bool HasBuyPeriod = false;
					Maple::Game::BuyPeriodData BuyPeriod;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<ItemEntry> Items;
			};
			
			struct ShopLoadMeretItemPacket
			{
				struct ItemEntry
				{
					Maple::Game::MeretShopPremiumItemEntryData MeretItemEntry;
				};
				
				std::vector<ItemEntry> Items;
			};
			
			struct ShopMeretItemCountPacket
			{
				unsigned short Count = 0;
			};
			
			struct ShopAddBuyBackPacket
			{
				struct ItemEntry
				{
					Enum::ShopRepurchaseId RepurchaseId = (Enum::ShopRepurchaseId)0;
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					unsigned long long Price = 0;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<ItemEntry> Items;
			};
			
			struct ShopBuyBackItemCountPacket
			{
				unsigned short ItemCount = 0;
			};
			
			struct ShopUpdatePacket
			{
				Enum::ShopEntryId EntryId = (Enum::ShopEntryId)0;
				unsigned int BuyCount = 0;
			};
			
			struct ShopRemoveBuyBackPacket
			{
				Enum::ShopRepurchaseId RepurchaseId = (Enum::ShopRepurchaseId)0;
			};
			
			struct ShopBuyPacket
			{
				enum class FontColorEnum
				{
				};
				
				Enum::ItemId ItemId = (Enum::ItemId)0;
				unsigned int BuyCount = 0;
				unsigned int TotalPrice = 0;
				FontColorEnum FontColor = (FontColorEnum)0;
				bool ToGuildStorage = false;
			};
			
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
			
			struct ShopInstantRestockPacket
			{
				bool Restock = false;
			};
			
			struct ShopOpenPacket
			{
				enum class ShopTypeEnum
				{
				};
				
				Enum::NpcId NpcId = (Enum::NpcId)0;
				Enum::ShopId ShopId = (Enum::ShopId)0;
				unsigned long long ResetTime = 0;
				unsigned int RemainingSeconds = 0;
				unsigned short ItemCount = 0;
				bool CanRestock = false;
				std::string ShopName;
				unsigned int InstantRestockCost = 0;
				ShopTypeEnum ShopType = (ShopTypeEnum)0;
			};
		}
	}
}
