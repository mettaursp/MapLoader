#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/EffectStats.h>

namespace Maple
{
	namespace Game
	{
		struct AdditionalEffect
		{
			Enum::ActorId TargetId = (Enum::ActorId)0;
			Enum::EffectInstanceId InstanceId = (Enum::EffectInstanceId)0;
			Enum::ActorId SourceId = (Enum::ActorId)0;
			EffectStats Stats;
			bool Enabled = false;
			long long ShieldHealth = 0;
		};
	}
}
