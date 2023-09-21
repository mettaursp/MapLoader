#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/NpcDialogData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkRespondPacket
			{
				unsigned char Flags = 0;
				Enum::QuestId QuestId = (Enum::QuestId)0;
				Maple::Game::NpcDialogData Dialog;
			};
		}
	}
}
