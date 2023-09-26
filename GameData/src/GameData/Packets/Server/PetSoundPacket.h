#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetSoundPacket
			{
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
			};
		}
	}
}
