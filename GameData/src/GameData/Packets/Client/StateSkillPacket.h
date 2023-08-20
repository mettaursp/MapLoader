#pragma once

#include <GameData/Enums/SkillId.h>
#include <GameData/Enums/SkillSn.h>
#include <GameData/Enums/SkillLevel.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct StateSkillPacket
			{
				Enum::SkillSn SkillSn;
				unsigned int ServerTick = 0;
				Enum::SkillId SkillId;
				Enum::SkillLevel SkillLevel;
				int Animation = 0;
				int ClientTick = 0;
			};
		}
	}
}
