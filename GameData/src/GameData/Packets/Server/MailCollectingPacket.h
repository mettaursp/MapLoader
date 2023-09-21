#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct MailCollectingPacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
				unsigned long long CollectTime = 0;
			};
		}
	}
}
