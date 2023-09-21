#pragma once

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ShopErrorPacket
			{
				unsigned int Message = 0;
				unsigned int StringId = 0;
			};
		}
	}
}
