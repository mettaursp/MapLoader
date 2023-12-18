#pragma once

#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct DungeonListEntriesPacket
			{
				struct DungeonEntry
				{
				};
				
				std::vector<DungeonEntry> Dungeons;
			};
		}
	}
}
