#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/ActorStats.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct StatPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Maple::Game::ActorStats Stats;
			};
		}
	}
}
