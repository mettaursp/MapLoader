#pragma once

#include <vector>
#include <GameData/Packets\Server/EnchantScrollRewardPacket.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct EnchantScrollRewardPacket
			{
				struct DataEntry
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
				};
				
				std::vector<DataEntry> Data;
			};
		}
	}
}
