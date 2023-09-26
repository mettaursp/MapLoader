#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkCinematicPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				int Index = 0;
			};
		}
	}
}
