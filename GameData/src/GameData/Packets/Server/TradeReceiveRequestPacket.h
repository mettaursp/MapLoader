#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

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
