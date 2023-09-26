#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PlayInstrumentStopImprovisePacket
			{
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
			};
		}
	}
}
