#pragma once

#include <GameData/Enums/MapId.h>
#include <Engine/Math/Vector3S.h>

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
