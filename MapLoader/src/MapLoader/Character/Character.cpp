#include "Character.h"

#include <MapLoader/Items/EmotionLibrary.h>
#include <MapLoader/Assets/GameAssetLibrary.h>
#include <MapLoader/Scene/RTScene.h>

namespace MapLoader
{
	struct RayHit
	{
		float Distance = 0;
		bool Hit = false;
		Vector3SF Intersection;
		Vector3SF Normal;
	};

	RayHit castRay(const MapLoader::ModelData* model, Vector3SF rayStart, Vector3SF rayDirection)
	{
		RayHit hit;

		for (size_t i = 0; i < model->Transformations.size(); ++i)
		{
			const auto& mesh = model->Meshes[i];

			if (mesh == nullptr) continue;

			Matrix4F transform = model->Transformations[i].Inverted();
			Vector3SF localStart = transform * Vector3F(rayStart, 1);
			Vector3SF localDirection = transform * Vector3F(rayDirection, 0);

			size_t positionIndex = mesh->GetFormat()->GetAttributeIndex("position");
			size_t normalIndex = mesh->GetFormat()->GetAttributeIndex("normal");

			const std::vector<int>& indexBuffer = mesh->GetIndexBuffer();

			for (size_t i = 0; i < indexBuffer.size(); i += 3)
			{
				size_t vertexAIndex = (size_t)indexBuffer[i];
				size_t vertexBIndex = (size_t)indexBuffer[i + 1];
				size_t vertexCIndex = (size_t)indexBuffer[i + 2];

				const Vector3SF& vertexA = mesh->GetAttribute<Vector3SF>(vertexAIndex, positionIndex);
				const Vector3SF& vertexB = mesh->GetAttribute<Vector3SF>(vertexBIndex, positionIndex);
				const Vector3SF& vertexC = mesh->GetAttribute<Vector3SF>(vertexCIndex, positionIndex);

				Vector3SF faceNormal = (vertexB - vertexA).Cross(vertexC - vertexA);

				float length = faceNormal.SquareLength();

				if (length <= 1e-9)
				{
					continue; // degenerate triangle (0 area)
				}

				float normalDot = faceNormal * localDirection;
				float distance = (faceNormal * (vertexA - localStart)) / normalDot;

				if (distance < hit.Distance)
					continue;

				Vector3SF intersection = localStart + distance * localDirection;

				float dot1 = (vertexB - vertexA).Cross(intersection - vertexA).Dot(faceNormal);
				float dot2 = (vertexC - vertexB).Cross(intersection - vertexB).Dot(faceNormal);
				float dot3 = (vertexA - vertexC).Cross(intersection - vertexC).Dot(faceNormal);

				if (!(std::signbit(dot1) == std::signbit(dot2) && std::signbit(dot1) == std::signbit(dot3)))
					continue;

				hit.Hit = true;
				hit.Intersection = intersection;
				hit.Distance = distance;

				float u = dot2 / length;
				float v = dot3 / length;
				float w = 1 - u - v;

				const Vector3SF& normalA = mesh->GetAttribute<Vector3SF>(vertexAIndex, normalIndex);
				const Vector3SF& normalB = mesh->GetAttribute<Vector3SF>(vertexBIndex, normalIndex);
				const Vector3SF& normalC = mesh->GetAttribute<Vector3SF>(vertexCIndex, normalIndex);

				hit.Normal = u * normalA + v * normalB + w * normalC;

				if (hit.Normal.SquareLength() <= 1e-9f)
					hit.Normal = faceNormal.Unit();
			}
		}

		return hit;
	}

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

		Transforms["Bip01_HeadNub"] = {};

		for (size_t i = 0; i < rig->Transformations.size(); ++i)
		{
			const auto transformIndex = Transforms.find(rig->NodeNames[i]);

			if (transformIndex != Transforms.end())
				transformIndex->second = rig->Transformations[i];
		}

		std::vector<const ItemModel*> addedModels;

		Matrix4F hatTransform;
		Vector3SF hatOffset;

		const auto& hat = ActiveSlots.find("CP");

		if (hat != ActiveSlots.end() && hat->second.Item->Customization.HatAttach)
		{
			const auto& hatAsset = hat->second.Slot->Assets[0];
			ModelData* hatModel = hatAsset.Model;

			for (size_t i = 0; i < hatModel->NodeNames.size(); ++i)
			{
				if (hatAsset.SelfNode == hatModel->NodeNames[i].substr(0, hatAsset.SelfNode.size()))
				{
					hatOffset = -hatModel->Transformations[i].Translation();

					break;
				}
			}

			const auto& hair = ActiveSlots.find("HR");

			if (hair != ActiveSlots.end())
			{
				ModelData* hairModel = hair->second.Slot->Assets[0].Model;
				const HatItem* hatData = reinterpret_cast<const HatItem*>(hat->second.Customization);

				RayHit hitData = castRay(hairModel, hatData->AttachOrigin, hatData->AttachDirection);

				if (hitData.Hit)
				{
					Vector3SF itemUp(1, 0, 0);

					Vector3SF front = hitData.Normal.Unit();
					Vector3SF right = front.Cross(itemUp).Unit();
					Vector3SF up = front.Cross(right).Unit();
					Vector3SF rotation = hatData->AttachRotation;
					
					hatTransform = Matrix4F(hitData.Intersection, -up, -right, front) * Matrix4F::EulerAnglesRotation(rotation.X, rotation.Y, rotation.Z);
				}
			}
		}

		for (auto& activeSlot : ActiveSlots)
		{
			currentSlot = &activeSlot.second;

			const ItemSlot* slot = currentSlot->Slot;

			dyeColor = currentSlot->Customization->Color;

			for (const ItemData& asset : slot->Assets)
			{
				Matrix4F assetTransform;

				const auto transformIndex = Transforms.find(asset.TargetNode);

				if (transformIndex != Transforms.end())
					assetTransform = transformIndex->second;

				if (slot->Name == "CP" && activeSlot.second.Item->Customization.HatAttach)
				{
					assetTransform = hatTransform * assetTransform;
				}

				if (asset.SelfNode == asset.TargetNode)
				{
					for (size_t i = 0; i < asset.Model->NodeNames.size(); ++i)
					{
						if (asset.SelfNode == asset.Model->NodeNames[i].substr(0, asset.SelfNode.size()))
						{
							assetTransform = assetTransform * asset.Model->Transformations[i].Inverted();
					
							break;
						}
					}
				}

				spawnModel(asset.Model, transform * assetTransform, spawnCallback);
			}
		}
	}
}