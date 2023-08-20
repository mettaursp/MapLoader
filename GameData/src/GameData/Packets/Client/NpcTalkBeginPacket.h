#pragma once

#include <GameData/Enums/ActorId.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkBeginPacket
			{
				Enum::ActorId ObjectId;
			};
		}
	}
}
