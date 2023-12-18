#pragma once

#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct PatchFileDownloadPacketPacket
			{
				struct UnknownDataEntry
				{
				};
				
				std::vector<UnknownDataEntry> UnknownData;
			};
			
			struct PatchFileDeletePacket
			{
			};
			
			struct PatchFileDownloadOnlinePacket
			{
				struct UnknownDataEntry
				{
				};
				
				std::vector<UnknownDataEntry> UnknownData;
			};
		}
	}
}
