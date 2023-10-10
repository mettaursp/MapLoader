#pragma once

#include <string>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct LogInAuthTokenPacket
			{
				unsigned char Mode = 0;
				std::string AuthToken;
				unsigned long long MachineLow = 0;
				unsigned long long MachineHigh = 0;
				std::string Locale;
			};
		}
	}
}
