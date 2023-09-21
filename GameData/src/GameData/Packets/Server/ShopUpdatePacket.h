#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopUpdatePacket
			{
				Enum::ShopEntryId EntryId = (Enum::ShopEntryId)0;
				unsigned int BuyCount = 0;
			};
		}
	}
}
