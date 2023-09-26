#pragma once

#include <vector>
#include <GameData/Packets\Server/ShopLoadNewPacket.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Packets\Server/BuyPeriodData.h>
#include <GameData/Data/ItemData.h>

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
