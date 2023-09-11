#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ExpUpPacket
			{
				bool IsRestExp = false;
				unsigned long long ExpGained = 0;
				unsigned long long TotalExp = 0;
				unsigned long long RestExp = 0;
				unsigned int Message = 0;
				bool Additional = false;
			};
		}
	}
}
