#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TradeErrorPacket
			{
				unsigned int Message = 0;
				std::wstring Name;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				unsigned int Level = 0;
			};
		}
	}
}
