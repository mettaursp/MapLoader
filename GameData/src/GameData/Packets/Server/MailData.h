#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>
#include <string>
#include <vector>

namespace Maple
{
	namespace Game
	{
		struct MailAttachData
		{
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			unsigned char Index = 0;
			unsigned int Amount = 0;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			ItemData ItemData;
		};
		
		struct MailAdData
		{
		};
		
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
namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct MailError2Packet
			{
				unsigned int Message = 0;
			};
			
			struct MailEndListPacket
			{
			};
			
			struct MailExpireNotificationPacket
			{
			};
			
			struct MailStartListPacket
			{
			};
			
			struct MailReceivePacket
			{
				unsigned int UnreadMailCount = 0;
				bool Alert = false;
				unsigned int Count = 0;
			};
			
			struct MailUpdateReadTimePacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
				unsigned long long ReadTime = 0;
			};
			
			struct MailErrorPacket
			{
			};
			
			struct MailCollectingPacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
				unsigned long long CollectTime = 0;
			};
			
			struct MailSendCustomConfirmPacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
			};
			
			struct MailDeletePacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
			};
			
			struct MailLoadPacket
			{
				std::vector<Maple::Game::MailData> Mail;
			};
			
			struct MailReadPacket
			{
				Enum::MailInstanceId MailInstanceId = (Enum::MailInstanceId)0;
				unsigned long long ReadTime = 0;
			};
			
			struct MailReceiveGiftNotificationPacket
			{
			};
		}
	}
}
