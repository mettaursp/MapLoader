#pragma once

#include <GameData/Packets\Server/EnchantScrollResultPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct EnchantScrollResultPacket
			{
				enum class ResultTypeEnum
				{
					Success = 0,
					InvalidScroll = 1,
					InvalidItem = 2,
					BreakingItem = 3,
					InvalidLevel = 4,
					InvalidSlot = 5,
					InvalidRank = 6,
					InvalidGrade = 7,
					NotBreaking = 8
				};
				
				ResultTypeEnum Result = (ResultTypeEnum)0;
			};
		}
	}
}
