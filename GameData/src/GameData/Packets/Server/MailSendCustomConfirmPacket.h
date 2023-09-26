#pragma once

#include <GameData/Enums/MapleHandles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct MailSendCustomConfirmPacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
			};
		}
	}
}
