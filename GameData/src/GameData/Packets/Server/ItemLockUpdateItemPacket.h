#pragma once

#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/ItemLockUpdateItemPacket.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemLockUpdateItemPacket
			{
				struct ItemEntry
				{
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<ItemEntry> Items;
			};
		}
	}
}
