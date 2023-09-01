#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListDeletePendingPacket
			{
				Enum::CharacterId CharacterId;
				unsigned int MessageId = 0;
				unsigned long long DeleteTime = 0;
			};
		}
	}
}
