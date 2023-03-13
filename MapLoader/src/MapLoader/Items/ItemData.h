#pragma once

#include <vector>
#include <string>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Vector3S.h>
#include <ArchiveParser/MetadataMapper.h>
#include <MapLoader/Assets/ModelData.h>

namespace MapLoader
{
	struct ItemData
	{
		std::string NifPath;
		const Archive::Metadata::Entry* ModelEntry = nullptr;
		MapLoader::ModelData* Model = nullptr;
		std::string SelfNode;
		std::string TargetNode;
		std::string AttachNode;
		bool Replace = false;
		bool EarFold = false;
		bool HasPonytail = false;
		bool IsWeapon = false;
	};

	struct ItemSlotScale
	{
		Vector3SF Value;
		float Min = 0;
		float Max = 0;
		bool Reverse = false;
	};

	struct ItemDecalTransform
	{
		Vector3SF Position;
		Vector3SF Rotation;
		int TextureTransformId = -1;
	};

	struct ItemDecal
	{
		std::string TexturePath;
		std::string ControlTexturePath;
		std::vector<ItemDecalTransform> Transforms;
		int Texture = -1;
		int ControlTexture = -1;
	};

	struct ItemSlot
	{
		std::string Name;
		std::vector<ItemData> Assets;
		std::vector<ItemSlotScale> Scales;
		std::vector<ItemDecal> Decals;
	};

	struct ItemCustomizationFlags
	{
		bool HairScale = false;
		bool HairPonytail = false;
		bool FaceDecorTranslation = false;
		bool FaceDecorRotation = false;
		bool FaceDecorScale = false;
		bool HatRotationX = false;
		bool HatRotationY = false;
		bool HatRotationZ = false;
		bool HatScale = false;
		bool HatAttach = false;
		bool HasDefaultHatTransform = false;
		Matrix4F DefaultHatTransform;
	};

	struct ItemModel
	{
		int Id = 0;
		std::string Name;
		std::vector<ItemSlot> Slots;
		std::vector<std::string> Cutting;
		ItemCustomizationFlags Customization;
	};
}