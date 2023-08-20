#pragma once

#include <GameData/Packets\Client/NpcTalkAllianceQuestAcceptPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkAllianceQuestAcceptPacket
			{
				enum class EventTypeEnum
				{
					Complete = 0,
					Start = 2
				};
				
				int Index = 0;
				EventTypeEnum EventType = EventTypeEnum::Start;
			};
		}
	}
}
