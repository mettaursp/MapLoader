#pragma once

#include <string>
#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>

namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct TradeFinalizeConfirmPacket
			{
				unsigned char Index = 0;
			};
			
			struct TradeChangeOfferPacket
			{
				unsigned char Index = 0;
			};
			
			struct TradeFinalizePacket
			{
				unsigned char Index = 0;
			};
			
			struct TradeSetMoneyPacket
			{
				unsigned char Index = 0;
				unsigned long long Mesos = 0;
			};
			
			struct TradeAddItemPacket
			{
				unsigned char Index = 0;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				unsigned int TradeSlot = 0;
				unsigned int Amount = 0;
				unsigned int TradeSlot2 = 0;
				Maple::Game::ItemData ItemData;
			};
			
			struct TradeEndPacket
			{
				bool Success = false;
			};
			
			struct TradeBeginPacket
			{
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			};
			
			struct TradeRemoveItemPacket
			{
				unsigned char Index = 0;
				unsigned int TradeSlot = 0;
				Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			};
			
			struct TradeConfirmRequestPacket
			{
			};
			
			struct TradeErrorPacket
			{
				unsigned int Message = 0;
				std::wstring Name;
				Enum::ItemId ItemId = (Enum::ItemId)0;
				unsigned int Level = 0;
			};
			
			struct TradeReceiveRequestPacket
			{
				std::wstring PlayerName;
				Enum::CharacterId CharacterId = (Enum::CharacterId)0;
			};
			
			struct TradeDeclinedPacket
			{
				std::wstring PlayerName;
			};
		}
	}
}
