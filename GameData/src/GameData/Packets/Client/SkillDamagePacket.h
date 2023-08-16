#pragma once

#include <Engine/Math/Vector3S.h>
#include <vector>

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
					int EntityId = 0;
				};
				
				long long SkillSn = 0;
				int AttackCounter = 0;
				int SourceId = 0;
				Vector3S Position;
				Vector3S HitPoint;
				Vector3S Rotation;
				unsigned char AttackPoint = 0;
				std::vector<HitEntity> Hits;
			};
		}
	}
}
