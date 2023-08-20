#pragma once

#include <GameData/Enums/SkillSn.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncTickPacket
			{
				Enum::SkillSn SkillSn;
				int ServerTick = 0;
			};
		}
	}
}
