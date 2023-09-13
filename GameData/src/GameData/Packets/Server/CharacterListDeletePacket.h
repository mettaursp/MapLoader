#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListDeletePacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			};
		}
	}
}
