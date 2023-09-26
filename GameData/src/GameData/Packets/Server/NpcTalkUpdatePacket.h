#pragma once

#include <GameData/Packets\Server/ScriptContentData.h>

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
