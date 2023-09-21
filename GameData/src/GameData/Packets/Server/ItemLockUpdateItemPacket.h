#pragma once

#include <vector>
#include <GameData/Packets\Server/ItemLockUpdateItemPacket.h>
#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>

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
