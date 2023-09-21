#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>
#include <string>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PlayInstrumentStartScorePacket
			{
				bool IsCustom = false;
				Enum::InstrumentId InstrumentId = (Enum::InstrumentId)0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Vector3S InstrumentPosition;
				int InstrumentTick = 0;
				int GMId = 0;
				int PercussionId = 0;
				std::string MusicCode;
				std::wstring FileName;
			};
		}
	}
}
