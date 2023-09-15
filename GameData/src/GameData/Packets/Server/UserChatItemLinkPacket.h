#pragma once

#include <GameData/Enums/Item.h>
#include <vector>
#include <GameData/Packets\Server/UserChatItemLinkPacket.h>
#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>

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
