#pragma once

#include <vector>
#include <Engine/Math/Vector3S.h>

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
						int AttackCount = 0;
						int SourceId = 0;
						int TargetId = 0;
						unsigned char Index = 0;
					};
					
					int AttackCount = 0;
					int SourceId = 0;
					int TargetId = 0;
					unsigned char Index = 0;
					std::vector<ChainTarget> ChainTargets;
				};
				
				long long SkillSn = 0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
				std::vector<Projectile> Projectiles;
			};
		}
	}
}
