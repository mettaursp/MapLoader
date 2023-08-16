#pragma once

#include <Engine/Math/Vector3S.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillCastPacket
			{
				long long SkillSn = 0;
				int ServerTick = 0;
				int SkillId = 0;
				short SkillLevel = 0;
				unsigned char AttackPoint = 0;
				Vector3S Position;
				Vector3S Direction;
				Vector3S Rotation;
				int ClientTick = 0;
				bool Flag = false;
			};
		}
	}
}
