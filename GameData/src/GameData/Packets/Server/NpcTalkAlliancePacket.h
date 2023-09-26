#pragma once

#include <GameData/Packets\Server/NpcDialogData.h>

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
