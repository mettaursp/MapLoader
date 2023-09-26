#pragma once

#include <GameData/Packets\Server/BlackMarketEntryData.h>
#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketSearchResultsPacket
			{
				std::vector<Maple::Game::BlackMarketEntryData> Entries;
			};
		}
	}
}
