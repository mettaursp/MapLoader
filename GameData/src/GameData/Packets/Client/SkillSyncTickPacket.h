#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncTickPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				int ServerTick = 0;
			};
		}
	}
}
