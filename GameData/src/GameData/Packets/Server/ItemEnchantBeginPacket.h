#pragma once

#include <GameData/Enums/Item.h>
#include <vector>
#include <GameData/Packets\Server/ItemEnchantBeginPacket.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Data/BasicStat.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemEnchantBeginPacket
			{
				enum class CatalystTypeEnum
				{
					CrystalFrag = 100,
					Onyx = 101,
					ChaosOnyx = 102
				};
				
				enum class EnchantTypeEnum
				{
					Ophelia = 1,
					Peachy = 2
				};
				
				struct CatalystEntry
				{
					CatalystTypeEnum RequiredItem = (CatalystTypeEnum)0;
					unsigned int Amount = 0;
				};
				
				EnchantTypeEnum EnchantType = (EnchantTypeEnum)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				std::vector<CatalystEntry> Ingredients;
				std::vector<Maple::Game::BasicStat> Stats;
				float SuccessRate = 0;
				float UnknownRate2 = 0;
				float UnknownRate3 = 0;
				float CatalystTotalRate = 0;
				float ChargeTotalRate = 0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				unsigned int Amount = 0;
			};
		}
	}
}
