#pragma once

#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Item.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TradeAddItemPacket
			{
				unsigned char Index = 0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				unsigned int TradeSlot = 0;
				unsigned int Amount = 0;
				unsigned int TradeSlot2 = 0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
