#pragma once

#include <GameData/Enums/Handles.h>
#include <string>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListChangeNamePacket
			{
				unsigned int Confirm = 0;
				Enum::CharacterId CharacterId;
				std::wstring Name;
			};
		}
	}
}
