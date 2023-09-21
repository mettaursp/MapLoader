#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TradeSetMoneyPacket
			{
				unsigned char Index = 0;
				unsigned long long Mesos = 0;
			};
		}
	}
}
