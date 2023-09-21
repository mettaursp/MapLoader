#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkActionMovePlayerPacket
			{
				Enum::PortalId PortalId = (Enum::PortalId)0;
			};
		}
	}
}
