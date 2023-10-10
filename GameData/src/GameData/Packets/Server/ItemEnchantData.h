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
			struct ItemEnchantFailPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
				unsigned int FailStacks = 0;
			};
			
			struct ItemEnchantUpdateIngredientsPacket
			{
				struct CatalystEntry
				{
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				};
				
				unsigned int CatalystWeight = 0;
				std::vector<CatalystEntry> Catalysts;
			};
			
			struct ItemEnchantSuccessPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
				std::vector<Maple::Game::BasicStat> Stats;
			};
			
			struct ItemEnchantUpdateChargesPacket
			{
				struct CatalystEntry
				{
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				};
				
				unsigned int ChargeCount = 0;
				unsigned int CatalystWeight = 0;
				std::vector<CatalystEntry> Catalysts;
				float SuccessRate = 0;
				float UnknownRate2 = 0;
				float UnknownRate3 = 0;
				float CatalystTotalRate = 0;
				float ChargeTotalRate = 0;
			};
			
			struct ItemEnchantErrorPacket
			{
				unsigned short Code = 0;
			};
			
			struct ItemEnchantUpdateExpPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned int EnchantExp = 0;
			};
			
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
