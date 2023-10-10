#pragma once

#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BuffPacket
			{
				enum class ModeEnum
				{
					Add = 0,
					Remove = 1,
					Update = 2
				};
				
				ModeEnum Mode = ModeEnum::Add;
				bool UpdateEffect = false;
				Maple::Game::AdditionalEffect Effect;
				bool UpdateShield = false;
			};
		}
	}
}
