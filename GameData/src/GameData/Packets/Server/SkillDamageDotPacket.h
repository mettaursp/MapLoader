#pragma once

#include <GameData/Enums/ActorId.h>
#include <GameData/Enums/HitType.h>

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