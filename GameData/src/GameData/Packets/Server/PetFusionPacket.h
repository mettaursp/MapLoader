#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetFusionPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				unsigned long long Exp = 0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
		}
	}
}
