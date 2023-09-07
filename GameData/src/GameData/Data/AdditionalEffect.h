#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/EffectStats.h>

namespace Maple
{
	namespace Game
	{
		struct AdditionalEffect
		{
			Enum::ActorId TargetId;
			Enum::EffectInstanceId InstanceId;
			Enum::ActorId SourceId;
			EffectStats Stats;
			bool Enabled = false;
			long long ShieldHealth = 0;
		};
	}
}
