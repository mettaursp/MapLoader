#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PlayInstrumentStartImprovisePacket
			{
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Vector3S InstrumentPosition;
				int GMId = 0;
				int PercussionId = 0;
			};
		}
	}
}
