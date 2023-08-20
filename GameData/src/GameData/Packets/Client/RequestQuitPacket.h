#pragma once

#include <GameData/Packets\Client/RequestQuitPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct RequestQuitPacket
			{
				enum class ModeEnum
				{
					ChangeCharacter = 0,
					Quit = 1
				};
				
				ModeEnum Mode = ModeEnum::Quit;
			};
		}
	}
}
