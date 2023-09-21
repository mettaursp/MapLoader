#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PetLapisSnarePacket
			{
				Enum::ItemId ItemId = (Enum::ItemId)0;
			};
		}
	}
}
