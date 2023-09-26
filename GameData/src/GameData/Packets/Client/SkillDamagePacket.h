#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
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
					Enum::ActorId EntityId = (Enum::ActorId)0;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
				Vector3S Position;
				Vector3S HitPoint;
				Vector3S Rotation;
				unsigned char AttackPoint = 0;
				std::vector<HitEntity> Hits;
			};
		}
	}
}
