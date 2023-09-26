#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FittingDollRemovePacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
		}
	}
}
