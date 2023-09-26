#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TradeReceiveRequestPacket
			{
				std::wstring PlayerName;
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			};
		}
	}
}
