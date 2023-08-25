#pragma once

#include <GameData/Enums/ActorId.h>

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
