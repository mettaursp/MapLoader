#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/NpcDialogData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkContinuePacket
			{
				unsigned char Flags = 0;
				Enum::ActorId ActorId = (Enum::ActorId)0;
				Maple::Game::NpcDialogData Dialog;
			};
		}
	}
}
