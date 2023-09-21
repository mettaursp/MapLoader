#pragma once

#include <vector>
#include <GameData/Data/ItemData.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Data/BasicStat.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemEnchantSuccessPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Maple::Game::ItemData ItemData;
				std::vector<Maple::Game::BasicStat> Stats;
			};
		}
	}
}
