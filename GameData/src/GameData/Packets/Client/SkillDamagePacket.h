#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/SkillSn.h>
#include <GameData/Enums/ActorId.h>
#include <GameData/Enums/SkillAttackId.h>
#include <GameData/Packets\Client/SkillDamagePacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillDamagePacket
			{
				struct HitEntity
				{
					Enum::ActorId EntityId;
				};
				
				Enum::SkillSn SkillSn;
				Enum::SkillAttackId SkillAttack;
				Vector3S Position;
				Vector3S HitPoint;
				Vector3S Rotation;
				unsigned char AttackPoint = 0;
				std::vector<HitEntity> Hits;
			};
		}
	}
}
