#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct ReconnectPacket
			{
				Enum::AccountId AccountId;
				Enum::CharacterId CharacterId;
			};
		}
	}
}
