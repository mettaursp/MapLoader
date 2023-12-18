#pragma once

#include <vector>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct EmotionLearnPacket
			{
			};
			
			struct EmotionErrorPacket
			{
			};
			
			struct EmotionLoadPacket
			{
				struct EmotionEntry
				{
				};
				
				std::vector<EmotionEntry> Emotes;
			};
		}
	}
}
