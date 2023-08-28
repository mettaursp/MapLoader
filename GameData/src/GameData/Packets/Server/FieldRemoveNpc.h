#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct FieldRemoveNpc
			{
				Enum::ActorId ActorId;
			};
		}
	}
}
