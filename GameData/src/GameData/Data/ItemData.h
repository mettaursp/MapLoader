#pragma once

#include <GameData/Data/ItemBinding.h>
#include <GameData/Data/ItemPet.h>
#include <GameData/Data/ItemEnchantment.h>
#include <GameData/Data/ItemCustomization.h>
#include <GameData/Data/ItemTransfer.h>
#include <GameData/Data/ItemMusic.h>
#include <GameData/Data/ItemBadge.h>
#include <GameData/Data/ItemBlueprint.h>
#include <GameData/Data/ItemStats.h>
#include <GameData/Data/ItemLimitBreak.h>
#include <GameData/Data/ItemTemplate.h>
#include <GameData/Data/ItemSocket.h>
#include <GameData/Data/ItemCouple.h>

namespace Maple
{
	namespace Game
	{
		struct ItemData
		{
			unsigned int Amount = 0;
			unsigned long long CreationTime = 0;
			unsigned long long ExpirationTime = 0;
			unsigned int TimesChanged = 0;
			unsigned int RemainingUses = 0;
			bool IsLocked = false;
			bool UnlockTime = false;
			bool GlamorForges = false;
			ItemCustomization Customization;
			ItemStats Stats;
			ItemEnchantment Enchantment;
			ItemLimitBreak LimitBreak;
			ItemTemplate Template;
			ItemBlueprint Blueprint;
			ItemPet Pet;
			ItemMusic Music;
			ItemBadge Badge;
			ItemTransfer ItemTransfer;
			ItemSocket ItemSocket;
			ItemCouple ItemCouple;
			ItemBinding Binding;
		};
	}
}
