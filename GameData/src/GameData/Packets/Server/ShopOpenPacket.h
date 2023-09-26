#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/ShopOpenPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopOpenPacket
			{
				enum class ShopTypeEnum
				{
				};
				
				Enum::NpcId NpcId = (Enum::NpcId)0;
				Enum::ShopId ShopId = (Enum::ShopId)0;
				unsigned long long ResetTime = 0;
				unsigned int RemainingSeconds = 0;
				unsigned short ItemCount = 0;
				bool CanRestock = false;
				std::string ShopName;
				unsigned int InstantRestockCost = 0;
				ShopTypeEnum ShopType = (ShopTypeEnum)0;
			};
		}
	}
}
