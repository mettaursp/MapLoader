#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/ShopBuyPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopBuyPacket
			{
				enum class FontColorEnum
				{
				};
				
				Enum::ItemId ItemId = (Enum::ItemId)0;
				unsigned int BuyCount = 0;
				unsigned int TotalPrice = 0;
				FontColorEnum FontColor = (FontColorEnum)0;
				bool ToGuildStorage = false;
			};
		}
	}
}
