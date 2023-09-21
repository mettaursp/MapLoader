#pragma once

#include <GameData/Enums/Handles.h>

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
