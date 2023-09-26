#pragma once

#include <vector>
#include <GameData/Packets\Server/CharacterListEntry.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct CharacterListLoadPacket
			{
				std::vector<Maple::Game::CharacterListEntry> Characters;
			};
		}
	}
}
