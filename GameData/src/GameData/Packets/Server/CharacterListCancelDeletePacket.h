#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListCancelDeletePacket
			{
				Enum::CharacterId CharacterId;
				unsigned int MessageId = 0;
			};
		}
	}
}
