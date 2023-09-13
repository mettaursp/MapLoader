#pragma once

#include <vector>
#include <GameData/Data/ItemBinding.h>
#include <GameData/Data/ItemSocket.h>
#include <GameData/Enums/Handles.h>

namespace Maple
{
	namespace Game
	{
		struct ItemSocket
		{
			struct Slot
			{
				struct GemData
				{
					Enum::ItemId ItemId = (Enum::ItemId)0;
					bool IsBound = false;
					ItemBinding Binding;
					bool IsLocked = false;
					unsigned long long UnlockTime = 0;
				};
				
				bool HasGem = false;
				GemData Gem;
			};
			
			unsigned char MaxSlots = 0;
			unsigned char UnlockedSlots = 0;
			std::vector<Slot> Sockets;
		};
	}
}
