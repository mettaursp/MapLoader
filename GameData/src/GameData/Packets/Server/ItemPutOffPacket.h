#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemPutOffPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
		}
	}
}
