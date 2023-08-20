#pragma once

#include <GameData/Enums/AccountId.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct ResponseKeyPacket
			{
				Enum::AccountId AccountId;
				int TokenA = 0;
				int TokenB = 0;
				unsigned long long MachineHigh = 0;
				unsigned long long MachineLow = 0;
			};
		}
	}
}
