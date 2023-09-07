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
					
					Enum::ActorId TargetId;
					Vector3S Position;
					Vector3S Direction;
					std::vector<DamageInstance> Damages;
				};
				
				Enum::SkillSn SkillSn;
				Enum::SkillId SkillId;
				Enum::SkillLevel SkillLevel;
				std::vector<DamagedTarget> DamagedTargets;
			};
		}
	}
}
