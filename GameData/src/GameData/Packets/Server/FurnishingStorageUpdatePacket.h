#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FurnishingStorageUpdatePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned int Count = 0;
			};
		}
	}
}
