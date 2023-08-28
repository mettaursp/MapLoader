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
				Enum::MapId MapId;
				Vector3S Position;
				Vector3S Rotation;
			};
		}
	}
}
