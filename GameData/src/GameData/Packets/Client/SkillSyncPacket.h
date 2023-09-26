#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				unsigned char MotionPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
