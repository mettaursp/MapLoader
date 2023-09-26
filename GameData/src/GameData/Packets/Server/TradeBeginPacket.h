#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TradeBeginPacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			};
		}
	}
}
