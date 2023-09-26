#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/NpcDialogData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkEndPacket
			{
				Enum::ActorId ActorId = (Enum::ActorId)0;
				unsigned char Flags = 0;
				Maple::Game::NpcDialogData Dialog;
			};
		}
	}
}
