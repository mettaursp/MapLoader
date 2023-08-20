#pragma once

#include <GameData/Enums/EffectLevel.h>
#include <GameData/Enums/EffectInstanceId.h>
#include <GameData/Packets\Server/BuffPacket.h>
#include <GameData/Enums/ActorId.h>
#include <GameData/Enums/EffectId.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BuffPacket
			{
				enum class ModeEnum
				{
					Add = 0,
					Remove = 1,
					Update = 2
				};
				
				ModeEnum Mode = ModeEnum::Add;
				Enum::ActorId TargetId;
				Enum::EffectInstanceId InstanceId;
				Enum::ActorId SourceId;
				bool UpdateEffect = false;
				int StartTime = 0;
				int EndTime = 0;
				Enum::EffectId EffectId;
				Enum::EffectLevel EffectLevel;
				int Stacks = 0;
				bool Enabled = false;
				bool UpdateShield = false;
				long long ShieldHealth = 0;
			};
		}
	}
}
