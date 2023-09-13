#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldRemovePlayerPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
		}
	}
}
