#pragma once

#include <GameData/Packets\Server/MeretShopPremiumItemEntryData.h>
#include <vector>
#include <GameData/Packets\Server/ShopLoadMeretItemPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopLoadMeretItemPacket
			{
				struct ItemEntry
				{
					Maple::Game::MeretShopPremiumItemEntryData MeretItemEntry;
				};
				
				std::vector<ItemEntry> Items;
			};
		}
	}
}
