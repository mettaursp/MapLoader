#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct SkillDamageHealPacket
			{
				Enum::ActorId CasterId;
				Enum::ActorId TargetId;
				int ServerTick = 0;
				int HpAmount = 0;
				int SpAmount = 0;
				int EpAmount = 0;
				bool IsVisible = false;
			};
		}
	}
}
