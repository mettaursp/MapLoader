#pragma once

#include <vector>
#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/SkillSn.h>
#include <GameData/Packets\Client/SkillSyncDamagePacket.h>
#include <GameData/Enums/ActorId.h>
#include <GameData/Enums/SkillAttackId.h>

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
						Enum::SkillAttackId SkillAttack;
						Enum::ActorId TargetId;
						unsigned char Index = 0;
					};
					
					Enum::SkillAttackId SkillAttack;
					Enum::ActorId TargetId;
					unsigned char Index = 0;
					std::vector<ChainTarget> ChainTargets;
				};
				
				Enum::SkillSn SkillSn;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
				std::vector<Projectile> Projectiles;
			};
		}
	}
}
