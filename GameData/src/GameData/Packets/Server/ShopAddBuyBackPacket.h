#pragma once

#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/ShopAddBuyBackPacket.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
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
		}
	}
}
