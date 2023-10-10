#pragma once

#include <GameData/Enums/MapleHandles.h>
#include <GameData/Enums/MapleItem.h>
#include <GameData/Data/PacketCommon.h>
#include <vector>

namespace Maple
{
	namespace Game
	{
		struct BlackMarketEntryData
		{
			Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
			unsigned long long TimeListed = 0;
			unsigned long long TimeListed2 = 0;
			unsigned long long TimeExpires = 0;
			unsigned int Amount = 0;
			unsigned long long CostPerItem = 0;
			Enum::ItemInstanceId ItemInstanceId = (Enum::ItemInstanceId)0;
			Enum::ItemId ItemId = (Enum::ItemId)0;
			Enum::Rarity Rarity = (Enum::Rarity)0;
			Enum::AccountId ListerAccountId = (Enum::AccountId)0;
			ItemData ItemData;
		};
	}
}
namespace Networking
{
	namespace Packets
	{
		namespace Server
		{
			struct BlackMarketPrepareListingPacket
			{
				Enum::ItemId ItemId = (Enum::ItemId)0;
				Enum::Rarity Rarity = (Enum::Rarity)0;
				unsigned int ShopPrice = 0;
			};
			
			struct BlackMarketCancelListingPacket
			{
				Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
			};
			
			struct BlackMarketSearchResultsPacket
			{
				std::vector<Maple::Game::BlackMarketEntryData> Entries;
			};
			
			struct BlackMarketSoldPacket
			{
			};
			
			struct BlackMarketCreateListingPacket
			{
				Maple::Game::BlackMarketEntryData Listing;
			};
			
			struct BlackMarketMyListingsPacket
			{
				std::vector<Maple::Game::BlackMarketEntryData> Entries;
			};
			
			struct BlackMarketPurchasePacket
			{
				Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
				unsigned int Amount = 0;
			};
			
			struct BlackMarketErrorPacket
			{
				unsigned int ErrorCode = 0;
				Enum::ListingInstanceId ListingInstanceId = (Enum::ListingInstanceId)0;
			};
		}
	}
}
