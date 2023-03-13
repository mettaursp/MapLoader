#pragma once

#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Matrix4.h>
#include <MapLoader/Items/Dyes.h>
#include <MapLoader/Items/ItemData.h>

namespace MapLoader
{
	enum class Gender
	{
		Male = 0,
		Female = 1,
		Either = 2
	};

	struct Item
	{
		int Id = 0;
		DyeColor Color;
		int Preset = 0;
	};

	struct HairItem : public Item
	{
		//float Scale = 0;
		//int Pony = 0;
		//Vector3SF HatPosition;
		//Vector3SF HatRotation;
		//float HatScale = 1;
	};

	struct FaceDecorItem : public Item
	{

	};

	struct HatItem : public Item
	{
		bool CustomAttach = false;
		Vector3SF AttachDirection;
		Vector3SF AttachRotation;
	};

	struct InventoryTab
	{
		HatItem Hat;
		Item Shirt;
		Item Pants;
		Item Gloves;
		Item Shoes;
		bool ShirtCoversPants = false;
		Item Earring;
		Item Pendant;
		Item Ring;
		Item Cape;
		Item Belt;
		Item Weapon;
	};

	struct CharacterData
	{
		Gender Gender = Gender::Male;
		DyeColor SkinColor;
		HairItem Hair;
		FaceDecorItem FaceDecor;
		Item Face;
		InventoryTab Gear;
		InventoryTab Cosmetics;
		std::string Emotion = "default";
		int EmotionFrame = 0;
	};

	struct EquippedSlot
	{
		const Item* Customization = nullptr;
		const ItemModel* Item = nullptr;
		const ItemSlot* Slot = nullptr;
		bool Replaces = false;
	};

	class GameAssetLibrary;

	class Character
	{
	public:
		Character(const std::shared_ptr<GameAssetLibrary>& assetLibrary);
		void EquipItem(const ItemModel* item, Item& customization);
		void EquipItem(Item& item);
		void LoadTab(InventoryTab& equips);
		void Load(CharacterData* customization, const Matrix4F transform = Matrix4F());

	private:
		std::shared_ptr<GameAssetLibrary> AssetLibrary;
		CharacterData* Customization = nullptr;
		bool HideEars = false;
		std::unordered_map<std::string, EquippedSlot> ActiveSlots;
		std::vector<std::string> CutMeshes;
		std::unordered_map<std::string, Matrix4F> Transforms;
		Matrix4F Transform;
	};
}