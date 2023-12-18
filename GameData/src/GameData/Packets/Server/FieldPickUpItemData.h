#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldPickUpItemPacket
			{
				Enum::ItemEntityId ObjectId = (Enum::ItemEntityId)0;
			};
		}
	}
}
