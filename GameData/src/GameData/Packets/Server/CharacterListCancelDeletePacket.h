#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListCancelDeletePacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				unsigned int MessageId = 0;
			};
		}
	}
}
