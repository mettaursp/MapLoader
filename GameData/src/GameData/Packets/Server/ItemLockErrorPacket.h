#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ItemLockErrorPacket
			{
				unsigned int ErrorCode = 0;
			};
		}
	}
}
