#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetInventoryMoveItemPacket
			{
				Enum::ItemInstanceId SourceItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short SourceSlot = 0;
				Enum::ItemInstanceId DestinationItemInstanceId = (Enum::ItemInstanceId)0;
				unsigned short DestinationSlot = 0;
			};
		}
	}
}
