#pragma once

#include <vector>
#include <GameData/Packets\Server/TrophyUpdatePacket.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TrophyUpdatePacket
			{
				enum class StatusEnum
				{
					InProgress = 2,
					Finished = 3
				};
				
				struct Timestamp
				{
					int Index = 0;
					long long Time = 0;
				};
				
				Enum::TrophyId TrophyId = (Enum::TrophyId)0;
				StatusEnum Status = StatusEnum::InProgress;
				bool IsDone = false;
				int NextGrade = 0;
				int LastReward = 0;
				bool IsFavorited = false;
				int Counter = 0;
				std::vector<Timestamp> Timestamps;
			};
		}
	}
}
