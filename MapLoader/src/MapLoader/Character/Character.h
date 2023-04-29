#pragma once

#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Matrix4.h>
#include <MapLoader/Items/Dyes.h>
#include <MapLoader/Items/ItemData.h>
#include <nvvk/resourceallocator_vk.hpp>

struct ModelSpawnParameters;

namespace Engine
{
	class Transform;
}

namespace MapLoader
{
	enum class Gender
	{
		Male = 0,
		Female = 1,
		Either = 2
	};

	enum class ItemSlotType
	{
		Hair = 2,
		Face = 3,
		FaceDecor = 4,
		Earring = 12,
		Hat = 13,
		Shirt = 14,
		Pants = 15,
		Gloves = 16,
		Shoes = 17,
		Cape = 18,
		Pendant = 19,
		Ring = 20,
		Belt = 21,
		Blade = 54,
		None
	};

	struct Item
	{
		ItemSlotType Slot = ItemSlotType::None;
		int Id = 0;
		DyeColor Color;
		int Preset = 0;
	};

	struct HairItem : public Item
	{
		float Scale = 0;
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
		Vector3SF AttachOrigin;
		Vector3SF AttachDirection;
		Vector3SF AttachRotation;
	};

	struct InventoryTab
	{
		HatItem Hat = { ItemSlotType::Hat };
		Item Shirt = { ItemSlotType::Shirt };
		Item Pants = { ItemSlotType::Pants };
		Item Gloves = { ItemSlotType::Gloves };
		Item Shoes = { ItemSlotType::Shoes };
		bool ShirtCoversPants = false;
		Item Earring = { ItemSlotType::Earring };
		Item Pendant = { ItemSlotType::Pendant };
		Item Ring = { ItemSlotType::Ring };
		Item Cape = { ItemSlotType::Cape };
		Item Belt = { ItemSlotType::Belt };
		Item Weapon = { ItemSlotType::Blade };
	};

	struct CharacterData
	{
		Gender Gender = Gender::Male;
		DyeColor SkinColor;
		HairItem Hair = { ItemSlotType::Hair };
		FaceDecorItem FaceDecor = { ItemSlotType::FaceDecor };
		Item Face = { ItemSlotType::Face };
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
	class SkinnedModel;

	class Character
	{
	public:
		Character(const std::shared_ptr<GameAssetLibrary>& assetLibrary, const std::shared_ptr<RTScene>& scene);
		~Character();

		void ReleaseResources();

		void EquipItem(const ItemModel* item, Item& customization);
		void EquipItem(Item& item);
		void LoadTab(InventoryTab& equips);
		void Load(CharacterData* customization, const Matrix4F transform = Matrix4F());

		const auto& GetModel() const { return Model; }

	private:
		struct SpawningData
		{
			std::string FaceFile;
			std::string FaceControl;
			EquippedSlot* FaceDecor = nullptr;
			EquippedSlot* CurrentSlot = nullptr;
			DyeColor CurrentDyeColor;
			bool SpawningRig = false;
		};

		std::shared_ptr<GameAssetLibrary> AssetLibrary;
		std::shared_ptr<RTScene> Scene;
		CharacterData* Customization = nullptr;
		bool HideEars = false;
		std::unordered_map<std::string, EquippedSlot> ActiveSlots;
		std::vector<std::string> CutMeshes;
		std::unordered_map<std::string, Matrix4F> Transforms;
		std::shared_ptr<Engine::Transform> Transform;
		nvvk::Buffer SkeletonBuffer;
		std::vector<Matrix4F> SkeletonData;
		SpawningData* SpawnParameters = nullptr;
		std::shared_ptr<SkinnedModel> Model;

		Matrix4F ComputeHatTransform();
		bool SpawnModelCallback(ModelSpawnParameters& spawnParameters);
		void CreateRigDebugMesh(MapLoader::ModelData* rig, const Matrix4F transform);
	};
}