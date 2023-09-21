#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

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
