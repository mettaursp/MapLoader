#pragma once

#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct MailDeletePacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
			};
		}
	}
}
