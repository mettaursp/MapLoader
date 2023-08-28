#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillCastPacket
			{
				Enum::SkillSn SkillSn;
				int ServerTick = 0;
				Enum::SkillId SkillId;
				Enum::SkillLevel SkillLevel;
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
