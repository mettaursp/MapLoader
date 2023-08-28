#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncPacket
			{
				Enum::SkillSn SkillSn;
				Enum::SkillId SkillId;
				Enum::SkillLevel SkillLevel;
				unsigned char MotionPoint = 0;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
