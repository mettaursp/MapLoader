#pragma once

#include <GameData/Data/NpcDialogData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkAlliancePacket
			{
				unsigned char Flags = 0;
				Maple::Game::NpcDialogData Dialog;
			};
		}
	}
}
