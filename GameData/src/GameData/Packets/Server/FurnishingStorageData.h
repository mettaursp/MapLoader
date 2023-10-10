#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FurnishingStorageEndListPacket
			{
			};
			
			struct FurnishingStoragePurchasePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned int Count = 0;
			};
			
			struct FurnishingStorageRemovePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct FurnishingStorageCountPacket
			{
				unsigned int Count = 0;
			};
			
			struct FurnishingStorageAddPacket
			{
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Enum::SlotType Slot = (Enum::SlotType)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct FurnishingStorageUpdatePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned int Count = 0;
			};
			
			struct FurnishingStorageStartListPacket
			{
			};
		}
	}
}
