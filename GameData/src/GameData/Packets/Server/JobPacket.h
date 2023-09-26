#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/JobPacket.h>
#include <GameData/Data/SkillTreeData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct JobPacket
			{
				enum class ModeEnum
				{
					Notify = 0,
					Basic = 1,
					Awakening = 2,
					Error = 3,
					Unknown = 7,
					Load = 8,
					Update = 9,
					Reset = 10,
					AutoDistribute = 11
				};
				
				Enum::ActorId ActorId = (Enum::ActorId)0;
				ModeEnum Mode = (ModeEnum)0;
				Maple::Game::SkillTreeData SkillTree;
			};
		}
	}
}
