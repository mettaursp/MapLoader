#pragma once

#include <string>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TradeDeclinedPacket
			{
				std::wstring PlayerName;
			};
		}
	}
}
