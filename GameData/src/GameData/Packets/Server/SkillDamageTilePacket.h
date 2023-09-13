#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/Handles.h>
#include <GameData/Packets\Server/SkillDamageTilePacket.h>
#include <GameData/Enums/Combat.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamageTilePacket
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
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				std::vector<DamagedTarget> DamagedTargets;
			};
		}
	}
}
