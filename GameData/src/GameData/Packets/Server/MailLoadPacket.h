#pragma once

#include <vector>
#include <GameData/Packets\Server/MailData.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct MailLoadPacket
			{
				std::vector<Maple::Game::MailData> Mail;
			};
		}
	}
}
