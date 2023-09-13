#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldRemoveNpcPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
		}
	}
}
