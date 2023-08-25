#pragma once

#include <GameData/Enums/ActorId.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkCinematicPacket
			{
				Enum::ActorId ActorId;
				int Index = 0;
			};
		}
	}
}
