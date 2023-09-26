#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FittingDollRemoveItemPacket
			{
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				std::wstring SlotName;
				unsigned char Slot = 0;
			};
		}
	}
}
