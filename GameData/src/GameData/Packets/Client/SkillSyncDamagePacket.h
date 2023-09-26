#pragma once

#include <vector>
#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Client/SkillSyncDamagePacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncDamagePacket
			{
				struct Projectile
				{
					struct ChainTarget
					{
						Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
						Enum::ActorId TargetId = (Enum::ActorId)0;
						unsigned char Index = 0;
					};
					
					Enum::SkillAttackId SkillAttack = (Enum::SkillAttackId)0;
					Enum::ActorId TargetId = (Enum::ActorId)0;
					unsigned char Index = 0;
					std::vector<ChainTarget> ChainTargets;
				};
				
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
				std::vector<Projectile> Projectiles;
			};
		}
	}
}
