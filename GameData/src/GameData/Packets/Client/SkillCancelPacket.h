#pragma once

#include <GameData/Enums/SkillSn.h>

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
