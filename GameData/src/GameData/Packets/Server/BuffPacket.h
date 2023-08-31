#pragma once

#include <GameData/Packets\Server/BuffPacket.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Data/EffectStats.h>

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
				Maple::Game::EffectStats Stats;
				bool Enabled = false;
				bool UpdateShield = false;
				long long ShieldHealth = 0;
			};
		}
	}
}
