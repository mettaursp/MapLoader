#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/ItemData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PlayInstrumentCreateScoreResponsePacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
			};
		}
	}
}
