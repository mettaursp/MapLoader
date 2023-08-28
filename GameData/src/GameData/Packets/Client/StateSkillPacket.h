#pragma once

#include <GameData/Enums/Handles.h>

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
