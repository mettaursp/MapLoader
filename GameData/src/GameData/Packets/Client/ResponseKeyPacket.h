#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct ResponseKeyPacket
			{
				long long AccountId = 0;
				int TokenA = 0;
				int TokenB = 0;
				unsigned long long MachineHigh = 0;
				unsigned long long MachineLow = 0;
			};
		}
	}
}
