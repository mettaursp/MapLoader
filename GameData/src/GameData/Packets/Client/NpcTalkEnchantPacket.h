#pragma once

#include <GameData/Packets\Client/NpcTalkEnchantPacket.h>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct NpcTalkEnchantPacket
			{
				enum class EventTypeEnum
				{
					Begin = 1,
					InProgress = 2,
					Result = 3
				};
				
				Enum::NpcId NpcId = (Enum::NpcId)0;
				Enum::ScriptId ScriptId = (Enum::ScriptId)0;
				EventTypeEnum EventType = EventTypeEnum::Begin;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
		}
	}
}
