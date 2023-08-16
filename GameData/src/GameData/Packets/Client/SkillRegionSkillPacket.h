#pragma once

#include <Engine/Math/Vector3S.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillRegionSkillPacket
			{
				long long SkillSn = 0;
				unsigned char AttackPoint = 0;
				int AttackCounter = 0;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
