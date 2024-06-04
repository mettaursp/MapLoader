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

	enum class EntityCubeType
	{
		Blank = 0,
		None = VisibilityFlags::eCubeTypeNone,
		Ground = VisibilityFlags::eCubeTypeGround,
		Fluid = VisibilityFlags::eCubeTypeFluid,
		Wall = VisibilityFlags::eCubeTypeWall,
		Object = VisibilityFlags::eCubeTypeObject,
		Building = VisibilityFlags::eCubeTypeBuilding
	};

	enum class EntityCollisionGroup
	{
		CollisionGroup0 = VisibilityFlags::eCollisionGroup0,
		CollisionGroup7 = VisibilityFlags::eCollisionGroup7,
		CollisionGroup8 = VisibilityFlags::eCollisionGroup8,
		CollisionGroup9 = VisibilityFlags::eCollisionGroup9,
		CollisionGroupMisc = VisibilityFlags::eCollisionGroupMisc
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

	struct FlatPhysXShape
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
	};
	
	struct FlatPhysXMesh
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		EntityCollisionGroup CollisionGroup = EntityCollisionGroup::CollisionGroupMisc;
	};

	struct FlatFluid
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
	};

	struct FlatVibrate
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		bool Enabled = true;
	};

	struct FlatBreakable
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		bool Enabled = true;
		EntityCollisionGroup CollisionGroup = EntityCollisionGroup::CollisionGroupMisc;
		bool NxCollision = false;
	};

	struct FlatMapProperties
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		EntityCubeType CubeType = EntityCubeType::Blank;
		bool GeneratePhysX = false;
		bool DisableCollision = false;
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

	struct FlatPhysXWhitebox
	{
		size_t Index = (size_t)-1;
		size_t Parent = (size_t)-1;
		Vector3SF ShapeDimensions;
	};

	struct FlatEntity
	{
		size_t Index = (size_t)-1;
		const Archive::Metadata::Entry* Entry = nullptr;
		MapLoader::ModelData* ProxyModel = nullptr;
		std::string Id;
		size_t Placeable = (size_t)-1;
		size_t Light = (size_t)-1;
		size_t Portal = (size_t)-1;
		size_t PhysXShape = (size_t)-1;
		size_t PhysXMesh = (size_t)-1;
		size_t Fluid = (size_t)-1;
		size_t Vibrate = (size_t)-1;
		size_t Breakable = (size_t)-1;
		size_t MapProperties = (size_t)-1;
		size_t Mesh = (size_t)-1;
		size_t PhysXWhitebox = (size_t)-1;
	};
}