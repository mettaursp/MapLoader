#pragma once

#include <GameData/Data/BlackMarketEntryData.h>
#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketMyListingsPacket
			{
				std::vector<Maple::Game::BlackMarketEntryData> Entries;
			};
		}
	}
}
