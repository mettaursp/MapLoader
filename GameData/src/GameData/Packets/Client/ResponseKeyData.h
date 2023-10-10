#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct ResponseKeyPacket
			{
				Enum::AccountId AccountId = (Enum::AccountId)0;
				int TokenA = 0;
				int TokenB = 0;
				unsigned long long MachineHigh = 0;
				unsigned long long MachineLow = 0;
			};
		}
	}
}
