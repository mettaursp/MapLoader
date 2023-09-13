#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Combat.h>
#include <GameData/Packets\Server/SkillDamageRegionPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamageRegionPacket
			{
				struct DamagedTarget
				{
					struct DamageInstance
					{
						Enum::HitType HitType = Enum::HitType::Normal;
						long long Damage = 0;
					};
					
					Enum::ActorId TargetId = (Enum::ActorId)0;
					Vector3S Position;
					Vector3S Direction;
					std::vector<DamageInstance> Damages;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::ActorId RegionSkillObjectId = (Enum::ActorId)0;
				unsigned char AttackPoint = 0;
				std::vector<DamagedTarget> DamagedTargets;
			};
		}
	}
}
