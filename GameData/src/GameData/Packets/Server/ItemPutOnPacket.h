#pragma once

#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <string>
#include <GameData/Enums/Item.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemPutOnPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				std::wstring SlotName;
				Enum::SlotType Slot = (Enum::SlotType)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				Enum::EquipTab EquipTab = (Enum::EquipTab)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
