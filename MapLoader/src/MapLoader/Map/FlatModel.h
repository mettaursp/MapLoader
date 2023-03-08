#pragma once

#include <MapLoader/Assets/ModelData.h>
#include <ArchiveParser/MetadataMapper.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Color3.h>

namespace MapLoader
{
	enum class EntityLightType
	{
		Point,
		Directional,
		Ambient
	};

	struct FlatLight
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		EntityLightType Type = EntityLightType::Point;
		float Dimmer = 0;
		Color3 DiffuseColor;
		Color3 SpecularColor;
		Color3 AmbientColor;
		float Range = 0;
		Vector3SF Position;
		Vector3SF Direction;
		float Scale;
		bool Enabled = false;
		bool CastsShadows = true;
	};

	struct FlatPortal
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		int TargetPortal = -1;
		int PortalId = -1;
		std::string TargetField;
	};

	struct FlatMesh
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		MapLoader::ModelData* Model = nullptr;
		Color3 MaterialColor = Color3(1.0f, 1, 1);
	};

	struct FlatPlaceable
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		Matrix4F Transformation;
		Vector3SF Position;
		Vector3SF Rotation;
		float Scale = 1;
		bool IsVisible = true;
	};

	struct FlatEntity
	{
		size_t Index = (size_t)-1;
		const Archive::Metadata::Entry* Entry = nullptr;
		MapLoader::ModelData* ProxyModel = nullptr;
		std::string Id;
		size_t PlaceableIndex = (size_t)-1;
		size_t LightIndex = (size_t)-1;
		size_t PortalIndex = (size_t)-1;
		size_t MeshIndex = (size_t)-1;
	};
}