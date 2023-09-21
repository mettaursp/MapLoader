#pragma once

#include <GameData/Data/ScriptContentData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct NpcTalkUpdatePacket
			{
				Maple::Game::ScriptContentData ScriptContent;
			};
		}
	}
}
