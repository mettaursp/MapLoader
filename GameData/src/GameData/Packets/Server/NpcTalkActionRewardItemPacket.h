#pragma once

#include <GameData/Packets\Server/NpcTalkActionRewardItemPacket.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkActionRewardItemPacket
			{
				struct ItemEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					unsigned int Amount = 0;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<ItemEntry> Items;
			};
		}
	}
}
