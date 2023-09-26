#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkBeginPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
		}
	}
}
