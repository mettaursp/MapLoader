#pragma once

#include <string>
#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FittingDollRemoveItemPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				std::wstring SlotName;
				unsigned char Slot = 0;
			};
			
			struct FittingDollPutOnItemPacket
			{
				Enum::DollInstanceId DollInstanceId = (Enum::DollInstanceId)0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				std::wstring SlotName;
				unsigned char Slot = 0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Maple::Game::ItemData ItemData;
			};
			
			struct FittingDollRemovePacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
			
			struct FittingDollLoadPacket
			{
				struct ItemEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
					std::wstring SlotName;
					unsigned char Slot = 0;
					Enum::Rarity Rarity = (Enum::Rarity)0;
					Maple::Game::ItemData ItemData;
				};
				
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Enum::DollInstanceId DollInstanceId = (Enum::DollInstanceId)0;
				Enum::ItemId DollItemId = (Enum::ItemId)0;
				Vector3S Position;
				Vector3S Rotation;
				bool HasItems = false;
				std::vector<ItemEntry> Items;
			};
			
			struct FittingDollErrorPacket
			{
				unsigned int ErrorCode = 0;
			};
		}
	}
}
