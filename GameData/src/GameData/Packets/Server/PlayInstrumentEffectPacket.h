#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PlayInstrumentEffectPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
		}
	}
}
