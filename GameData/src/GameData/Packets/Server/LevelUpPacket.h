#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct LevelUpPacket
			{
				Enum::ActorId ActorId;
				unsigned int Level = 0;
			};
		}
	}
}
