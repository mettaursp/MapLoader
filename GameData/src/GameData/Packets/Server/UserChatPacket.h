#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/UserChatPacket.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct UserChatPacket
			{
				enum class TypeEnum
				{
					All = 0,
					WhisperFrom = 3,
					WhisperTo = 4,
					WhisperFail = 5,
					WhisperReject = 6,
					Party = 7,
					Guild = 8,
					Notice = 9,
					World = 11,
					Channel = 12,
					NoticeAlert = 13,
					NoticeAlert2 = 14,
					ItemEnchant = 15,
					Super = 16,
					GuildAlert = 18,
					Unknown = 19,
					Club = 20,
					ChatBubble = 23
				};
				
				Enum::AccountId AccountId = (Enum::AccountId)0;
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
				std::wstring CharacterName;
				std::wstring Message;
				unsigned int StringId = 0;
				TypeEnum Type = TypeEnum::All;
				Enum::ChannelId ChannelId = (Enum::ChannelId)0;
				Enum::SuperChatId SuperChatId = (Enum::SuperChatId)0;
				Enum::ClubId ClubId = (Enum::ClubId)0;
			};
		}
	}
}
