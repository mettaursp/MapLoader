#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListChangeNamePacket
			{
				unsigned int Confirm = 0;
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				std::wstring Name;
			};
		}
	}
}
