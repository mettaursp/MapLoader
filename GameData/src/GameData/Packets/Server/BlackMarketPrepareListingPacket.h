#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketPrepareListingPacket
			{
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				unsigned int ShopPrice = 0;
			};
		}
	}
}
