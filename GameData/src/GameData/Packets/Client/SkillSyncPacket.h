#pragma once

#include <Engine/Math/Vector3S.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncPacket
			{
				long long SkillSn = 0;
				int SkillId = 0;
				short SkillLevel = 0;
				unsigned char MotionPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
