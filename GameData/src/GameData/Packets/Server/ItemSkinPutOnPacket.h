#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemSkinPutOnPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Enum::SlotType Slot = (Enum::SlotType)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
