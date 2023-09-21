#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct MailReceivePacket
			{
				unsigned int UnreadMailCount = 0;
				bool Alert = false;
				unsigned int Count = 0;
			};
		}
	}
}
