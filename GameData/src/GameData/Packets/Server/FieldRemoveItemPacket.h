#pragma once

#include <GameData/Enums/MapleHandles.h>

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
