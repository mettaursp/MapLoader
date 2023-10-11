#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>
#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetInventoryStartListPacket
			{
			};
			
			struct PetInventoryListItemsPacket
			{
				struct SlotEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
					unsigned short Slot = 0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					Maple::Game::ItemData ItemData;
				};
				
				std::vector<SlotEntry> Slots;
			};
			
			struct PetInventoryMoveItemPacket
			{
				Enum::ItemInstanceId SourceItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short SourceSlot = 0;
				Enum::ItemInstanceId DestinationItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short DestinationSlot = 0;
			};
			
			struct PetInventoryRemoveItemPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct PetInventoryStoreItemPacket
			{
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short Slot = 0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
