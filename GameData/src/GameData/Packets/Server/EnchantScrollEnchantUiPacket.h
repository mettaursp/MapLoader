#pragma once

#include <GameData/Enums/Item.h>
#include <vector>
#include <GameData/Enums/Handles.h>
#include <GameData/Packets\Server/EnchantScrollEnchantUiPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
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
		}
	}
}
