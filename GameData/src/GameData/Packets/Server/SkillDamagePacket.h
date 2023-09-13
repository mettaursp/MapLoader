#pragma once

#include <vector>
#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>
#include <GameData/Enums/Combat.h>
#include <GameData/Packets\Server/SkillDamagePacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamagePacket
			{
				struct DamagedTarget
				{
					struct DamageInstance
					{
						Enum::HitType HitType = Enum::HitType::Normal;
						long long Damage = 0;
					};
					
					Enum::ActorId TargetId = (Enum::ActorId)0;
					std::vector<DamageInstance> Damages;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
				Enum::ActorId CasterId = (Enum::ActorId)0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				unsigned char MotionPoint = 0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Direction;
				int ServerTick = 0;
				std::vector<DamagedTarget> DamagedTargets;
			};
		}
	}
}
