#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct SkillSyncTickPacket
			{
				long long SkillSn = 0;
				int ServerTick = 0;
			};
		}
	}
}
