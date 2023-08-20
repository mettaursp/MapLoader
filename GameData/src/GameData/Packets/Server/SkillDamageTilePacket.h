#pragma once

#include <GameData/Enums/SkillLevel.h>
#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/SkillId.h>
#include <GameData/Enums/SkillSn.h>
#include <GameData/Packets\Server/SkillDamageTilePacket.h>
#include <GameData/Enums/ActorId.h>
#include <GameData/Enums/HitType.h>

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
