#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetEvolvePointsPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				unsigned int Points = 0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
		}
	}
}
