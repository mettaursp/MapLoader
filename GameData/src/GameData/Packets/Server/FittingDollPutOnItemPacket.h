#pragma once

#include <GameData/Data/ItemData.h>
#include <string>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
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
		}
	}
}
