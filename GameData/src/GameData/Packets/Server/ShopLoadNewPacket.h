#pragma once

#include <GameData/Enums/Item.h>
#include <vector>
#include <GameData/Packets\Server/ShopLoadNewPacket.h>
#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Data/BuyPeriodData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
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
		}
	}
}
