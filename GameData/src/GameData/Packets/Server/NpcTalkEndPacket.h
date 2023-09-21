#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/NpcDialogData.h>

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
