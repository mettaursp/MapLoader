#pragma once

#include <GameData/Packets\Client/NpcTalkNextQuestPacket.h>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkNextQuestPacket
			{
				enum class EventTypeEnum
				{
					Complete = 0,
					Start = 2
				};
				
				Enum::QuestId QuestId = (Enum::QuestId)0;
				EventTypeEnum EventType = EventTypeEnum::Start;
			};
		}
	}
}
