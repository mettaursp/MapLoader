#pragma once


namespace Networking
{
	namespace Packets
	{
		namespace Client
		{
			struct ResponseVersionPacket
			{
				enum class LocaleEnum
				{
					KR = 0,
					Unknown1 = 1,
					NA = 2,
					Unknown3 = 3,
					Unknown4 = 4,
					Unknown5 = 5
				};
				
				unsigned int Version = 0;
				unsigned short Feature = 0;
				LocaleEnum Locale = LocaleEnum::KR;
			};
		}
	}
}
