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
				Enum::ActorId ObjectId;
				int Index = 0;
			};
		}
	}
}
