#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/SkillSn.h>
#include <GameData/Enums/ActorId.h>
#include <GameData/Packets\Server/SkillDamageRegionPacket.h>
#include <GameData/Enums/HitType.h>

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
					
					Enum::ActorId TargetId;
					Vector3S Position;
					Vector3S Direction;
					std::vector<DamageInstance> Damages;
				};
				
				Enum::SkillSn SkillSn;
				Enum::ActorId CasterId;
				Enum::ActorId RegionSkillObjectId;
				unsigned char AttackPoint = 0;
				std::vector<DamagedTarget> DamagedTargets;
			};
		}
	}
}
