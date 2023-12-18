#pragma once

#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ServerListPacket
			{
				struct ServerData
				{
				};
				
				struct ChannelData
				{
				};
				
				std::vector<ServerData> Servers;
				std::vector<ChannelData> Channels;
			};
		}
	}
}
