#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct StateSkillPacket
			{
				Enum::SkillSn SkillSn = (Enum::SkillSn)0;
				unsigned int ServerTick = 0;
				Enum::SkillId SkillId = (Enum::SkillId)0;
				Enum::SkillLevel SkillLevel = (Enum::SkillLevel)0;
				int Animation = 0;
				int ClientTick = 0;
			};
		}
	}
}
