#pragma once

#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/BasicStat.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct EnchantScrollRewardPacket
			{
				struct DataEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
				};
				
				std::vector<DataEntry> Data;
			};
			
			struct EnchantScrollSuccessPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct EnchantScrollStatUiPacket
			{
				enum class ScrollTypeEnum
				{
					EnchantLevel = 1,
					StatReroller = 2,
					RandomEnchant = 3,
					Rune = 4
				};
				
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				ScrollTypeEnum ScrollType = (ScrollTypeEnum)0;
				std::vector<Maple::Game::BasicStat> MinStats;
				std::vector<Maple::Game::BasicStat> MaxStats;
				std::vector<Maple::Game::BasicStat> Stats;
			};
			
			struct EnchantScrollEnchantUiPacket
			{
				enum class ScrollTypeEnum
				{
					EnchantLevel = 1,
					StatReroller = 2,
					RandomEnchant = 3,
					Rune = 4
				};
				
				struct ItemTypeEntry
				{
					Enum::ItemType ItemType = (Enum::ItemType)0;
				};
				
				struct ItemRarityEntry
				{
					Enum::Rarity ItemRarity = (Enum::Rarity)0;
				};
				
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				ScrollTypeEnum ScrollType = (ScrollTypeEnum)0;
				bool UntradeableReminder = false;
				unsigned int EnchantLevel = 0;
				unsigned int EnchantRate = 0;
				unsigned short MinLevel = 0;
				unsigned short MaxLevel = 0;
				std::vector<ItemTypeEntry> ItemTypes;
				std::vector<ItemRarityEntry> ItemRarities;
				unsigned int MinEnchant = 0;
				unsigned int MaxEnchant = 0;
			};
			
			struct EnchantScrollResultPacket
			{
				enum class ResultTypeEnum
				{
					Success = 0,
					InvalidScroll = 1,
					InvalidItem = 2,
					BreakingItem = 3,
					InvalidLevel = 4,
					InvalidSlot = 5,
					InvalidRank = 6,
					InvalidGrade = 7,
					NotBreaking = 8
				};
				
				ResultTypeEnum Result = (ResultTypeEnum)0;
			};
		}
	}
}
