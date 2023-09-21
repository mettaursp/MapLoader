#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

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
