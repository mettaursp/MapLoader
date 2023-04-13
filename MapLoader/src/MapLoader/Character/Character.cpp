#include "Character.h"

#include <MapLoader/Items/EmotionLibrary.h>
#include <MapLoader/Assets/GameAssetLibrary.h>
#include <MapLoader/Scene/RTScene.h>
#include <MapLoader/Map/FlatLibrary.h>
#include <MapLoader/Assets/SkinnedModel.h>
#include <Engine/Objects/Transform.h>

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

		for (size_t i = 0; i < model->Nodes.size(); ++i)
		{
			const auto& mesh = model->Nodes[i].Mesh;

			if (mesh == nullptr) continue;

			Matrix4F transform = model->Nodes[i].Transformation.Inverted();
			Vector3SF localStart = transform * Vector3F(rayStart, 1);
			Vector3SF localDirection = transform * Vector3F(rayDirection, 0);

			size_t positionIndex = mesh->GetFormat()->GetAttributeIndex("position");
			size_t normalIndex = mesh->GetFormat()->GetAttributeIndex("normal");

			const std::vector<int>& indexBuffer = mesh->GetIndexBuffer();

			for (size_t j = 0; j < indexBuffer.size(); j += 3)
			{
				size_t vertexAIndex = (size_t)indexBuffer[j];
				size_t vertexBIndex = (size_t)indexBuffer[j + 1];
				size_t vertexCIndex = (size_t)indexBuffer[j + 2];

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
				hit.Intersection = rayStart + distance * rayDirection;
				hit.Distance = distance;

				float u = dot2 / length;
				float v = dot3 / length;
				float w = 1 - u - v;

				const Vector3SF& normalA = mesh->GetAttribute<Vector3SF>(vertexAIndex, normalIndex);
				const Vector3SF& normalB = mesh->GetAttribute<Vector3SF>(vertexBIndex, normalIndex);
				const Vector3SF& normalC = mesh->GetAttribute<Vector3SF>(vertexCIndex, normalIndex);

				hit.Normal = u * normalA + v * normalB + w * normalC;
				hit.Normal = model->Nodes[i].Transformation * Vector3F(hit.Normal, 0);

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

	Character::Character(const std::shared_ptr<GameAssetLibrary>& assetLibrary, const std::shared_ptr<RTScene>& scene) : AssetLibrary(assetLibrary), Scene(scene)
	{

	}

	Character::~Character()
	{
		ReleaseResources();
	}

	void Character::ReleaseResources()
	{
		if (Model != nullptr)
			Model->ReleaseResources();

		if (SkeletonBuffer.buffer != nullptr)
			AssetLibrary->GetVulkanContext()->Allocator.destroy(SkeletonBuffer);
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

		std::string rigName = Customization->Gender == Gender::Male ? "Male" : "Female";

		const Archive::Metadata::Entry* rigAnimationEntry = Archive::Metadata::Entry::FindFirstEntryByTags(rigName, "gamebryo-animation");

		RigAnimationData* animData = AssetLibrary->GetAnimations().FetchRigAnimations(rigAnimationEntry);

		MapLoader::ModelData* rig = AssetLibrary->GetAnimations().FetchRig(animData);

		if (HideEars)
			CutMeshes.push_back("FA_EA");

		SpawningData parameters
		{
			.CurrentSlot{ nullptr },
			.CurrentDyeColor{ Customization->SkinColor },
			.SpawningRig{ true },
		};

		SpawnParameters = &parameters;

		const auto faceDecor = ActiveSlots.find("FD");

		if (faceDecor != ActiveSlots.end())
			parameters.FaceDecor = &faceDecor->second;
		else
			parameters.FaceDecor = nullptr;

		auto face = AssetLibrary->GetEmotions().GetFace(Customization->Gender, Customization->Emotion, Customization->EmotionFrame, Customization->Face.Id);
		parameters.FaceFile = face.File;
		parameters.FaceControl = face.Control;

		auto spawnCallback = [this](ModelSpawnParameters& spawnParameters)
		{
			return SpawnModelCallback(spawnParameters);
		};

		Transform = Engine::Create<Engine::Transform>();
		Transform->SetTransformation(transform);
		Transform->Update(0);

		Model = Engine::Create<SkinnedModel>(AssetLibrary, Scene);
		Model->SetParent(Transform);
		Model->SetTransform(Transform.get());
		Model->AddModel(rig, {}, spawnCallback);

		//CreateRigDebugMesh(rig, transform);

		parameters.SpawningRig = false;

		for (size_t i = 0; i < rig->Nodes.size(); ++i)
		{
			const auto transformIndex = Transforms.find(rig->Nodes[i].Name);

			if (transformIndex != Transforms.end())
				transformIndex->second = rig->Nodes[i].Transformation;
		}

		std::vector<const ItemModel*> addedModels;

		Matrix4F hatTransform = ComputeHatTransform();

		for (auto& activeSlot : ActiveSlots)
		{
			parameters.CurrentSlot = &activeSlot.second;

			const ItemSlot* slot = parameters.CurrentSlot->Slot;

			parameters.CurrentDyeColor = parameters.CurrentSlot->Customization->Color;

			for (const ItemData& asset : slot->Assets)
			{
				Matrix4F assetTransform;

				if (slot->Name == "CP" && activeSlot.second.Item->Customization.HatAttach)
				{
					assetTransform = hatTransform;
				}

				Model->AddModel(asset.Model, assetTransform, asset.SelfNode, asset.TargetNode, spawnCallback);
			}
		}

		Model->CreateRigDebugMesh(AssetLibrary->GetModels());

		Scene->AddSkinnedModel(Model);

		SpawnParameters = nullptr;
	}

	Matrix4F Character::ComputeHatTransform()
	{
		const auto& hat = ActiveSlots.find("CP");

		if (hat == ActiveSlots.end() || !hat->second.Item->Customization.HatAttach) return Matrix4F();

		const auto& hair = ActiveSlots.find("HR");

		if (hair == ActiveSlots.end()) return Matrix4F();

		Vector3SF hatOffset;

		const auto& hatAsset = hat->second.Slot->Assets[0];
		ModelData* hatModel = hatAsset.Model;

		for (size_t i = 0; i < hatModel->Nodes.size(); ++i)
		{
			if (hatAsset.SelfNode == hatModel->Nodes[i].Name.substr(0, hatAsset.SelfNode.size()))
			{
				hatOffset = -hatModel->Nodes[i].Transformation.Translation();

				break;
			}
		}

		ModelData* hairModel = hair->second.Slot->Assets[0].Model;
		const HatItem* hatData = reinterpret_cast<const HatItem*>(hat->second.Customization);

		RayHit hitData = castRay(hairModel, hatData->AttachOrigin, hatData->AttachDirection);

		if (!hitData.Hit) return Matrix4F();

		Vector3SF itemUp(1, 0, 0);

		Vector3SF front = hitData.Normal.Unit();
		Vector3SF right = front.Cross(itemUp).Unit();
		Vector3SF up = front.Cross(right).Unit();

		Matrix4F rotation = getMatrix(Vector3SF(0, 0, 0), hatData->AttachRotation, 1, true);

		return Matrix4F(hitData.Intersection, front, -up, -right) * rotation * Matrix4F(hatOffset);
	}

	bool Character::SpawnModelCallback(ModelSpawnParameters& spawnParameters) {
		auto& modelNode = spawnParameters.Model->Nodes[spawnParameters.MeshIndex];
		const std::string& meshName = modelNode.Name;

		if (contains(CutMeshes, meshName))
			return false;

		const auto equippedIndex = ActiveSlots.find(meshName.substr(0, 2));

		if (SpawnParameters->SpawningRig && equippedIndex != ActiveSlots.end() && equippedIndex->second.Replaces && meshName != "FA_EA")
			return false;

		const DyeColor& color = modelNode.Shader == "MS2CharacterSkinMaterial" ? Customization->SkinColor : SpawnParameters->CurrentDyeColor;

		spawnParameters.NewInstance.primaryColor = vec3(color.Primary.R, color.Primary.G, color.Primary.B);
		spawnParameters.NewInstance.secondaryColor = vec3(color.Secondary.R, color.Secondary.G, color.Secondary.B);

		if (meshName == "FA")
		{
			spawnParameters.NewInstance.flags |= 2;
		}

		if (SpawnParameters->CurrentSlot != nullptr && (SpawnParameters->CurrentSlot->Slot->Decals.size() > 0 || SpawnParameters->CurrentSlot->Slot->Name == "FA"))
		{
			auto& materialTextures = AssetLibrary->GetModels().GetMaterialTextures();

			spawnParameters.NewInstance.textureOverride = (int)materialTextures.size();

			materialTextures.push_back(materialTextures[modelNode.Material.textures]);

			MaterialTextures& overrides = materialTextures.back();

			for (const ItemDecal& decal : SpawnParameters->CurrentSlot->Slot->Decals)
			{
				int preset = std::max(-1, std::min((int)decal.Transforms.size() - 1, SpawnParameters->CurrentSlot->Customization->Preset));

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

			if (SpawnParameters->CurrentSlot->Slot->Name == "FA" && modelNode.Name == "FA")
			{
				int diffuseTexture = AssetLibrary->GetTextures().FetchTexture("Resource/Model/Textures/" + SpawnParameters->FaceFile, VK_FORMAT_R8G8B8A8_UNORM);
				int controlTexture = AssetLibrary->GetTextures().FetchTexture("Resource/Model/Textures/" + SpawnParameters->FaceControl, VK_FORMAT_R8G8B8A8_UNORM);

				if (diffuseTexture != -1)
				{
					overrides.diffuse.id = diffuseTexture;
				}

				if (controlTexture != -1)
				{
					overrides.colorOverride.id = controlTexture;
				}
			}

			if (SpawnParameters->CurrentSlot->Slot->Name == "FA" && modelNode.Name == "FA_Skin" && SpawnParameters->FaceDecor != nullptr)
			{
				for (const ItemDecal& decal : SpawnParameters->FaceDecor->Slot->Decals)
				{
					int preset = std::max(-1, std::min((int)decal.Transforms.size() - 1, SpawnParameters->FaceDecor->Customization->Preset));

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
	}

	void Character::CreateRigDebugMesh(MapLoader::ModelData* rig, const Matrix4F transform)
	{
		std::vector<VertexPosBinding> vertices;
		std::vector<int> indices;
		std::unordered_map<size_t, size_t> boneMap;
		
		for (size_t i = 0; i < rig->Nodes.size(); ++i)
		{
			const ModelNode& node = rig->Nodes[i];

			if (!node.IsBone) continue;

			boneMap[i] = vertices.size();
			vertices.push_back({});

			VertexPosBinding& vertex = vertices.back();

			vertex.position = node.Transformation.Translation();
			vertex.color = 0x00FF00FF;

			if (node.AttachedTo != (size_t)-1)
			{
				indices.push_back((int)boneMap[node.AttachedTo]);
				indices.push_back((int)vertices.size() - 1);
			}
		}

		uint32_t id = AssetLibrary->GetModels().LoadWireframeMesh(vertices, indices);

		AssetLibrary->GetModels().SpawnWireframe(Scene.get(), id, transform);
	}
}