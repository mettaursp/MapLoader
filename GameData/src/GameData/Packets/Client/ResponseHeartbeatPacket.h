#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct ResponseHeartbeatPacket
			{
				int ServerTick = 0;
				int ClientTick = 0;
			};
		}
	}
}
