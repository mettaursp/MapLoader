#pragma once

#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/UserChatItemLinkPacket.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct UserChatItemLinkPacket
			{
				struct UnknownEntry
				{
				};
				
				struct ItemEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<ItemEntry> Items;
				std::vector<UnknownEntry> Unknown;
			};
		}
	}
}
