#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/NpcDialogData.h>

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
