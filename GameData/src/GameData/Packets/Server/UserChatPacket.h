#pragma once

#include <GameData/Enums/Handles.h>
#include <string>
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
				
				Enum::AccountId AccountId;
				Enum::CharacterId CharacterId;
				std::wstring CharacterName;
				std::wstring Message;
				TypeEnum Type = TypeEnum::All;
				Enum::ChannelId ChannelId;
				Enum::SuperChatId SuperChatId;
				Enum::ClubId ClubId;
			};
		}
	}
}
