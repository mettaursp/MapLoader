#pragma once

#include "ItemData.h"

#include <unordered_map>
#include <MapLoader/Character/Character.h>

namespace MapLoader
{
	class GameAssetLibrary;

	class ItemLibrary
	{
	public:
		ItemLibrary(GameAssetLibrary& assetLibrary);
		const ItemModel* LoadItem(const Item& item, Gender gender);

	private:
		GameAssetLibrary& AssetLibrary;

		std::unordered_map<int, ItemModel> MaleItems;
		std::unordered_map<int, ItemModel> FemaleItems;
		std::string DocumentBuffer;
	};
}