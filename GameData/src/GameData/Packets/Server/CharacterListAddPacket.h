#pragma once

#include <GameData/Data/CharacterListEntry.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListAddPacket
			{
				Maple::Game::CharacterListEntry Character;
			};
		}
	}
}
