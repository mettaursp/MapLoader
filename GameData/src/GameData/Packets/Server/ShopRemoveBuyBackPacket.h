#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopRemoveBuyBackPacket
			{
				Enum::ShopRepurchaseId RepurchaseId = (Enum::ShopRepurchaseId)0;
			};
		}
	}
}
