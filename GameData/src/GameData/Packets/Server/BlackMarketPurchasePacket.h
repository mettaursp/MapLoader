#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketPurchasePacket
			{
				Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
				unsigned int Amount = 0;
			};
		}
	}
}
