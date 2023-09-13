#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldRemoveItemPacket
			{
				Enum::ItemEntityId ObjectId = (Enum::ItemEntityId)0;
			};
		}
	}
}
