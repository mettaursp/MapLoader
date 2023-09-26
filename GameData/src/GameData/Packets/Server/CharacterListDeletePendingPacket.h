#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListDeletePendingPacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				unsigned int MessageId = 0;
				unsigned long long DeleteTime = 0;
			};
		}
	}
}
