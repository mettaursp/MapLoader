#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleCombat.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamageDotPacket
			{
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::ActorId TargetId = (Enum::ActorId)0;
				int ServerTick = 0;
				Enum::HitType HitType = Enum::HitType::Normal;
				long long Damage = 0;
			};
		}
	}
}
