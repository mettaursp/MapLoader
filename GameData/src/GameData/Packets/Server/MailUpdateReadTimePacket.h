#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct MailUpdateReadTimePacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
				unsigned long long ReadTime = 0;
			};
		}
	}
}
