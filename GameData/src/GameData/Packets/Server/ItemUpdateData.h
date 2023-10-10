#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemUpdatePacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
