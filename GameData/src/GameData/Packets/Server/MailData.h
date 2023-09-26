#pragma once

#include <string>
#include <vector>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Packets\Server/MailAttachData.h>
#include <GameData/Packets\Server/MailAdData.h>

namespace Maple
{
	namespace Game
	{
		struct MailData
		{
			unsigned char Type = 0;
			Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
			Enum::CharacterId SenderCharacterId = (Enum::CharacterId)0;
			std::wstring SenderName;
			std::wstring MailTitle;
			std::wstring MailContent;
			std::wstring MetadataKey;
			std::wstring MetadataValue;
			std::vector<MailAdData> Ads;
			std::vector<MailAttachData> AttachedItems;
			unsigned long long Mesos = 0;
			unsigned long long LastPurchaseTimestamp = 0;
			unsigned long long BlueMerets = 0;
			unsigned long long RedMerets = 0;
			unsigned long long ReadTime = 0;
			unsigned long long ExpirationTime = 0;
			unsigned long long SentTime = 0;
		};
	}
}
