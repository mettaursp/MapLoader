#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillRegionSkillPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				unsigned char AttackPoint = 0;
				int AttackCounter = 0;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
