#pragma once

#include <vector>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct UserSyncPacket
			{
				std::vector<Maple::Game::StateSyncData> StateData;
			};
		}
	}
}
