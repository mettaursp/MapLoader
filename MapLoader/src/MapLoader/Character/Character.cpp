#include "Character.h"

#include <MapLoader/Items/EmotionLibrary.h>
#include <MapLoader/Assets/GameAssetLibrary.h>
#include <MapLoader/Scene/RTScene.h>

namespace MapLoader
{
	template <typename T>
	bool contains(const std::vector<T>& vector, const T& searchFor)
	{
		for (const T& value : vector)
			if (value == searchFor)
				return true;

		return false;
	}

	Character::Character(const std::shared_ptr<GameAssetLibrary>& assetLibrary) : AssetLibrary(assetLibrary)
	{

	}

	void Character::EquipItem(const ItemModel* item, Item& customization)
	{
		if (item == nullptr) return;

		for (const ItemSlot& slot : item->Slots)
		{
			if (!ActiveSlots.contains(slot.Name))
			{
				bool replaces = false;

				for (const ItemData& asset : slot.Assets)
				{
					HideEars |= asset.EarFold;
					replaces |= asset.Replace;
					Transforms[asset.TargetNode] = Matrix4F();

					if (asset.AttachNode != "")
						Transforms[asset.AttachNode] = Matrix4F();
				}

				ActiveSlots[slot.Name] = EquippedSlot{ &customization, item, &slot, replaces };
			}
			else
				item += 0;
		}

		for (const std::string& meshName : item->Cutting)
		{
			bool alreadyHas = false;

			if (!contains(CutMeshes, meshName))
			{
				CutMeshes.push_back(meshName);
			}
		}
	}

	void Character::EquipItem(Item& item)
	{
		EquipItem(AssetLibrary->GetItems().LoadItem(item, Customization->Gender), item);
	}

	void Character::LoadTab(InventoryTab& equips)
	{
		EquipItem(equips.Hat);
		EquipItem(equips.Shirt);
		EquipItem(equips.Pants);
		EquipItem(equips.Gloves);
		EquipItem(equips.Shoes);
		EquipItem(equips.Earring);
		EquipItem(equips.Pendant);
		EquipItem(equips.Ring);
		EquipItem(equips.Cape);
		EquipItem(equips.Belt);
		EquipItem(equips.Weapon);
	}

	void Character::Load(CharacterData* customization, const Matrix4F transform)
	{
		Customization = customization;
		EquipItem(Customization->Face);
		EquipItem(Customization->FaceDecor);

		LoadTab(Customization->Cosmetics);
		LoadTab(Customization->Gear);

		EquipItem(Customization->Hair);

		std::string rigPath = Customization->Gender == Gender::Male ? "/Model/Character/male/m_body.nif" : "/Model/Character/female/f_body.nif";

		const Archive::Metadata::Entry* rigEntry = Archive::Metadata::Entry::FindFirstEntryByTagWithRelPath(rigPath, "gamebryo-scenegraph");

		MapLoader::ModelData* rig = AssetLibrary->GetModels().FetchModel(rigEntry, true);

		if (HideEars)
			CutMeshes.push_back("FA_EA");

		DyeColor dyeColor = Customization->SkinColor;
		bool spawningRig = true;

		EquippedSlot* currentSlot = nullptr;

		const auto faceDecor = ActiveSlots.find("FD");

		EmotionTexture face = AssetLibrary->GetEmotions().GetFace(Customization->Gender, Customization->Emotion, Customization->EmotionFrame, Customization->Face.Id);

		const auto spawnCallback = [this, &dyeColor, &spawningRig, &currentSlot, &faceDecor, &face](MapLoader::ModelData* model, size_t i, InstDesc& instance)
		{
			const std::string& meshName = model->NodeNames[i];

			if (contains(CutMeshes, meshName))
				return false;

			const auto equippedIndex = ActiveSlots.find(meshName.substr(0, 2));

			if (spawningRig && equippedIndex != ActiveSlots.end() && equippedIndex->second.Replaces && meshName != "FA_EA")
				return false;

			const DyeColor& color = model->Shaders[i] == "MS2CharacterSkinMaterial" ? Customization->SkinColor : dyeColor;

			instance.primaryColor = vec3(color.Primary.R, color.Primary.G, color.Primary.B);
			instance.secondaryColor = vec3(color.Secondary.R, color.Secondary.G, color.Secondary.B);

			if (meshName == "FA")
			{
				instance.flags |= 2;
			}

			if (currentSlot != nullptr && (currentSlot->Slot->Decals.size() > 0 || currentSlot->Slot->Name == "FA"))
			{
				auto& materialTextures = AssetLibrary->GetModels().GetMaterialTextures();

				instance.textureOverride = (int)materialTextures.size();

				materialTextures.push_back(materialTextures[model->Materials[i].textures]);

				MaterialTextures& overrides = materialTextures.back();

				for (const ItemDecal& decal : currentSlot->Slot->Decals)
				{
					int preset = std::max(-1, std::min((int)decal.Transforms.size() - 1, currentSlot->Customization->Preset));

					if (decal.Texture != -1)
					{
						overrides.decal.id = decal.Texture;

						if (decal.Transforms.size() > 0)
						{
							overrides.decal.transformId = decal.Transforms[preset].TextureTransformId;
						}
					}

					if (decal.ControlTexture != -1)
					{
						overrides.colorOverride.id = decal.ControlTexture;

						if (decal.Transforms.size() > 0)
						{
							overrides.colorOverride.transformId = decal.Transforms[preset].TextureTransformId;
						}
					}
				}

				if (currentSlot->Slot->Name == "FA" && model->NodeNames[i] == "FA")
				{
					int diffuseTexture = AssetLibrary->GetTextures().FetchTexture("Resource/Model/Textures/" + face.File, VK_FORMAT_R8G8B8A8_UNORM);
					int controlTexture = AssetLibrary->GetTextures().FetchTexture("Resource/Model/Textures/" + face.Control, VK_FORMAT_R8G8B8A8_UNORM);

					if (diffuseTexture != -1)
					{
						overrides.diffuse.id = diffuseTexture;
					}

					if (controlTexture != -1)
					{
						overrides.colorOverride.id = controlTexture;
					}
				}

				if (currentSlot->Slot->Name == "FA" && model->NodeNames[i] == "FA_Skin" && faceDecor != ActiveSlots.end())
				{
					for (const ItemDecal& decal : faceDecor->second.Slot->Decals)
					{
						int preset = std::max(-1, std::min((int)decal.Transforms.size() - 1, faceDecor->second.Customization->Preset));

						if (decal.Texture != -1)
						{
							overrides.decal.id = decal.Texture;

							if (decal.Transforms.size() > 0)
							{
								overrides.decal.transformId = decal.Transforms[preset].TextureTransformId;
							}
						}

						if (decal.ControlTexture != -1)
						{
							overrides.colorOverride.id = decal.ControlTexture;

							if (decal.Transforms.size() > 0)
							{
								overrides.colorOverride.transformId = decal.Transforms[preset].TextureTransformId;
							}
						}
					}
				}
			}

			return true;
		};

		spawnModel(rig, transform, spawnCallback);

		spawningRig = false;

		for (size_t i = 0; i < rig->Transformations.size(); ++i)
		{
			const auto transformIndex = Transforms.find(rig->NodeNames[i]);

			if (transformIndex != Transforms.end())
				transformIndex->second = rig->Transformations[i];
		}

		std::vector<const ItemModel*> addedModels;

		Matrix4F hatTransform;

		for (auto& activeSlot : ActiveSlots)
		{
			currentSlot = &activeSlot.second;

			const ItemSlot* slot = currentSlot->Slot;

			dyeColor = currentSlot->Customization->Color;

			if (currentSlot->Item->Customization.HasDefaultHatTransform)
			{
				const auto transformIndex = Transforms.find("HR");

				if (transformIndex != Transforms.end())
					hatTransform = currentSlot->Item->Customization.DefaultHatTransform;
			}

			for (const ItemData& asset : slot->Assets)
			{
				Matrix4F assetTransform;

				const auto transformIndex = Transforms.find(asset.TargetNode);

				if (transformIndex != Transforms.end())
					assetTransform = transformIndex->second;

				if (slot->Name == "CP")
					assetTransform = assetTransform * hatTransform;

				for (size_t i = 0; i < asset.Model->NodeNames.size(); ++i)
				{
					if (asset.SelfNode == asset.Model->NodeNames[i].substr(0, asset.SelfNode.size()))
					{
						assetTransform = assetTransform * asset.Model->Transformations[i].Inverted();

						break;
					}
				}

				spawnModel(asset.Model, transform * assetTransform, spawnCallback);
			}
		}
	}
}