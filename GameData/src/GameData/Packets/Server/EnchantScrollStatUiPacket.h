#pragma once

#include <vector>
#include <GameData/Packets\Server/EnchantScrollStatUiPacket.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Data/BasicStat.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct EnchantScrollStatUiPacket
			{
				enum class ScrollTypeEnum
				{
					EnchantLevel = 1,
					StatReroller = 2,
					RandomEnchant = 3,
					Rune = 4
				};
				
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				ScrollTypeEnum ScrollType = (ScrollTypeEnum)0;
				std::vector<Maple::Game::BasicStat> MinStats;
				std::vector<Maple::Game::BasicStat> MaxStats;
				std::vector<Maple::Game::BasicStat> Stats;
			};
		}
	}
}
