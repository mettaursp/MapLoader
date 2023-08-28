#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillCancelPacket
			{
				Enum::SkillSn SkillSn;
			};
		}
	}
}
