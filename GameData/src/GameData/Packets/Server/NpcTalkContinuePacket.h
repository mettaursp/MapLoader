#pragma once

#include <GameData/Enums/Handles.h>
#include <GameData/Data/NpcDialogData.h>

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
