#pragma once

#include <string>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/ServerEnterPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct ServerEnterPacket
			{
				struct MapEntry
				{
					Enum::MapId MapId = (Enum::MapId)0;
				};
				
				Enum::ActorId PlayerActorId = (Enum::ActorId)0;
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				Enum::ChannelId ChannelId = (Enum::ChannelId)0;
				unsigned long long Exp = 0;
				unsigned long long RestExp = 0;
				unsigned long long Mesos = 0;
				unsigned long long TotalMerets = 0;
				unsigned long long Merets = 0;
				unsigned long long TotalGameMerets = 0;
				unsigned long long GameMerets = 0;
				unsigned long long EventMerets = 0;
				unsigned long long ValorTokens = 0;
				unsigned long long Treva = 0;
				unsigned long long Rue = 0;
				unsigned long long HaviFruit = 0;
				unsigned long long ReverseCoin = 0;
				unsigned long long MentorToken = 0;
				unsigned long long MenteeToken = 0;
				unsigned long long StarPoint = 0;
				unsigned long long MesoToken = 0;
				std::wstring ProfileUrl;
				std::vector<MapEntry> UnlockedMaps;
				std::vector<MapEntry> UnlockedTaxis;
				std::wstring MapleNewsUrl;
			};
		}
	}
}
