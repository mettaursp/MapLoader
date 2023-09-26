#pragma once

#include <GameData/Packets\Server/BlackMarketEntryData.h>

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
