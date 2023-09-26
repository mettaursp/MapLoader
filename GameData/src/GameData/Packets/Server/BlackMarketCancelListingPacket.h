#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketCancelListingPacket
			{
				Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
			};
		}
	}
}
