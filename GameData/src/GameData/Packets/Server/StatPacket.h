#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/ActorStats.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct StatPacket
			{
				Enum::ActorId ActorId;
				Maple::Game::ActorStats Stats;
			};
		}
	}
}
