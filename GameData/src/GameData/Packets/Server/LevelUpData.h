#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct LevelUpPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				unsigned int Level = 0;
			};
		}
	}
}
