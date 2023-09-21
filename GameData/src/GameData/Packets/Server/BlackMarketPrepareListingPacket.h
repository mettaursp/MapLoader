#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Item.h>

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
