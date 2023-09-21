#pragma once

#include <GameData/Data/BlackMarketEntryData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketCreateListingPacket
			{
				Maple::Game::BlackMarketEntryData Listing;
			};
		}
	}
}
