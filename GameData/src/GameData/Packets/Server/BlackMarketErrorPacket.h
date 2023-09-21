#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketErrorPacket
			{
				unsigned int ErrorCode = 0;
				Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
			};
		}
	}
}
