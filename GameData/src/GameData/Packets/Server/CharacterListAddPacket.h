#pragma once

#include <GameData/Packets\Server/CharacterListEntry.h>

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
