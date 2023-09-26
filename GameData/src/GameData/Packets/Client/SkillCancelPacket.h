#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillCancelPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
			};
		}
	}
}
