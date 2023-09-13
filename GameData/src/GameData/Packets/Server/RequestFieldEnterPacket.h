#pragma once

#include <Engine/Math/Vector3S.h>
#include <GameData/Enums/Handles.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct RequestFieldEnterPacket
			{
				Enum::MapId MapId = (Enum::MapId)0;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
