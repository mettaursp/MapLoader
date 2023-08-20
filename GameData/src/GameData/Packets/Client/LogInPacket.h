#pragma once

#include <string>

namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct LogInPacket
			{
				unsigned char Mode = 0;
				std::wstring Username;
				std::wstring Password;
				std::string AuthToken;
				unsigned long long MachineLow = 0;
				unsigned long long MachineHigh = 0;
				int SessionKey = 0;
				std::string Locale;
			};
		}
	}
}
