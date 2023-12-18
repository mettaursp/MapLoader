#pragma once

#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FurnishingInventoryUnknownPacket
			{
				Maple::Game::ItemUgc Ugc;
			};
		}
	}
}
