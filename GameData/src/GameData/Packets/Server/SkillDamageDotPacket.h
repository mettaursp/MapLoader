#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Combat.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamageDotPacket
			{
				Enum::ActorId CasterId;
				Enum::ActorId TargetId;
				int ServerTick = 0;
				Enum::HitType HitType = Enum::HitType::Normal;
				long long Damage = 0;
			};
		}
	}
}
