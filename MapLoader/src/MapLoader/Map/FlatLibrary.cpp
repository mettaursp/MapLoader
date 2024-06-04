#include "FlatLibrary.h"

#include <ArchiveParser/ParserUtils.h>
#include <ArchiveParser/XmlReader.h>
#include <MapLoader/Assets/GameAssetLibrary.h>

template <>
void XmlLite::XmlAttribute::Read<Vector3SF>(const std::string_view& string, Vector3SF& value)
{
	const char* valueData = string.data();

	Read<float>(string, value.X);

	while (valueData[0] && (valueData[0] != ' ' && valueData[0] != ','))
		++valueData;

	while (valueData[0] && (valueData[0] == ' ' || valueData[0] == ','))
		++valueData;

	Read<float>({ valueData, string.size() - (valueData - string.data()) }, value.Y);

	while (valueData[0] && (valueData[0] != ' ' && valueData[0] != ','))
		++valueData;

	while (valueData[0] && (valueData[0] == ' ' || valueData[0] == ','))
		++valueData;

	Read<float>({ valueData, string.size() - (valueData - string.data()) }, value.Z);
}

template <>
void XmlLite::XmlAttribute::Read<Color3>(const std::string_view& string, Color3& value)
{
	const char* valueData = string.data();

	Read<float>(string, value.R);

	while (valueData[0] && (valueData[0] != ' ' && valueData[0] != ','))
		++valueData;

	while (valueData[0] && (valueData[0] == ' ' || valueData[0] == ','))
		++valueData;

	Read<float>({ valueData, string.size() - (valueData - string.data()) }, value.G);

	while (valueData[0] && (valueData[0] != ' ' && valueData[0] != ','))
		++valueData;

	while (valueData[0] && (valueData[0] == ' ' || valueData[0] == ','))
		++valueData;

	Read<float>({ valueData, string.size() - (valueData - string.data()) }, value.B);
}

namespace MapLoader
{
	const float PI = 3.14159265359f;

	float degToRad(float deg)
	{
		return deg / 180 * PI;
	}

	Matrix4F getMatrix(const Vector3SF& position, const Vector3SF& rotation, float scale, bool isDegrees)
	{
		// roll = yaw
		// yaw = pitch
		// pitch = roll
		float x = rotation.X;
		float y = rotation.Y;
		float z = rotation.Z;

		if (isDegrees)
		{
			x = degToRad(x);
			y = degToRad(y);
			z = degToRad(z);
		}

		Matrix4F roll = Matrix4F::RollRotation(z);
		Matrix4F yaw = Matrix4F::YawRotation(y);
		Matrix4F pitch = Matrix4F::PitchRotation(x);
		Matrix4F rotationMatrix = pitch * yaw * roll;
		//Matrix4F::EulerAnglesRotation(degToRad(rotation.X), degToRad(rotation.Y), degToRad(rotation.Z))
		return Matrix4F(position) * rotationMatrix * Matrix4F::NewScale(scale, scale, scale);
	}

	FlatLibrary::FlatLibrary(
		GameAssetLibrary& assetLibrary,
		FlatLibrary* parentLibrary) :
		AssetLibrary(assetLibrary),
		ParentLibrary(parentLibrary)
	{

	}

	FlatEntry FlatLibrary::FetchFlat(const Archive::Metadata::Entry* entry)
	{
		const auto& entityIndex = EntityMap.find(entry);

		if (entityIndex != EntityMap.end())
			return FetchEntry(entityIndex->second);

		Archive::ArchivePath flatFile = AssetLibrary.GetReader()->GetPath("Resource" + entry->RelativePath.string());

		if (!flatFile.Loaded())
		{
			std::cout << "failed to load map resource: " << flatFile.GetPath().string() << std::endl;

			return {};
		}

		EntityMap[entry] = Entities.size();
		Entities.push_back({ Entities.size(), entry });

		FlatEntry flatEntry = { this, Entities.size() - 1 };

		flatFile.Read(DocumentBuffer);

		XmlLite::XmlReader document;

		document.OpenDocument(DocumentBuffer);

		const XmlLite::XmlNode* modelNode = document.GetFirstChild();

		std::string_view name = document.ReadAttributeValue<std::string_view>("name", "");

		LoadEntity(flatEntry, document, name);

		return flatEntry;
	}

	FlatEntry FlatLibrary::FetchFlat(const std::string_view& name)
	{
		if (name.empty())
			return {};

		std::string lowerName = lower(std::string(name));

		const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTags(name, "emergent-flat-model");

		if (entry == nullptr)
			return {};

		return FetchFlat(entry);
	}

	template <typename FlatType>
	void AddFlatMixInFrom(const std::vector<FlatType>& parentVector, size_t parentIndex, FlatEntry& entry, size_t& index, std::vector<FlatType>& vector)
	{
		if (parentIndex == (size_t)-1) return;

		index = vector.size();

		vector.push_back(parentVector[parentIndex]);

		FlatType& data = vector.back();
		data.Index = index;
		data.Parent = entry.Entity;
	}

	FlatEntry FlatLibrary::LoadEntityFromFlat(const FlatEntry& flat, XmlLite::XmlReader& document)
	{
		FlatEntity flatEntity = flat.Library->Entities[flat.Entity];

		Entities.push_back({ Entities.size(), flatEntity.Entry });

		FlatEntry entityEntry = { this, Entities.size() - 1 };
		FlatEntity& entity = Entities.back();

		AddFlatMixInFrom(flat.Library->Placeables, flatEntity.Placeable, entityEntry, entity.Placeable, Placeables);
		AddFlatMixInFrom(flat.Library->Meshes, flatEntity.Mesh, entityEntry, entity.Mesh, Meshes);
		AddFlatMixInFrom(flat.Library->Lights, flatEntity.Light, entityEntry, entity.Light, Lights);
		AddFlatMixInFrom(flat.Library->Portals, flatEntity.Portal, entityEntry, entity.Portal, Portals);
		AddFlatMixInFrom(flat.Library->PhysXShapes, flatEntity.PhysXShape, entityEntry, entity.PhysXShape, PhysXShapes);
		AddFlatMixInFrom(flat.Library->PhysXMeshes, flatEntity.PhysXMesh, entityEntry, entity.PhysXMesh, PhysXMeshes);
		AddFlatMixInFrom(flat.Library->Fluids, flatEntity.Fluid, entityEntry, entity.Fluid, Fluids);
		AddFlatMixInFrom(flat.Library->MapProperties, flatEntity.MapProperties, entityEntry, entity.MapProperties, MapProperties);
		AddFlatMixInFrom(flat.Library->VibrateObjects, flatEntity.Vibrate, entityEntry, entity.Vibrate, VibrateObjects);
		AddFlatMixInFrom(flat.Library->Breakable, flatEntity.Breakable, entityEntry, entity.Breakable, Breakable);
		AddFlatMixInFrom(flat.Library->PhysXWhiteboxes, flatEntity.PhysXWhitebox, entityEntry, entity.PhysXWhitebox, PhysXWhiteboxes);

		LoadEntity(entityEntry, document);

		return entityEntry;
	}

	FlatEntry FlatLibrary::FetchEntry(size_t index)
	{
		if (index == (size_t)-1)
			return {};

		FlatEntity* entity = &Entities[index];

		return { this, index };
	}

	template <typename FlatType>
	void AddFlatMixIn(FlatEntry& entry, size_t& index, std::vector<FlatType>& vector)
	{
		if (index != (size_t)-1) return;

		index = vector.size();

		vector.push_back({ vector.size(), entry.Entity });
	}

	void FlatLibrary::LoadMixin(FlatEntry& entry, FlatEntity& entity, std::string_view name)
	{
		if (strcmp(name, "Placeable") == 0)
		{
			AddFlatMixIn(entry, entity.Placeable, Placeables);

			return;
		}

		if (strcmp(name, "Mesh") == 0)
		{
			AddFlatMixIn(entry, entity.Mesh, Meshes);

			return;
		}

		if (strcmp(name, "Light") == 0)
		{
			AddFlatMixIn(entry, entity.Light, Lights);

			return;
		}

		if (strcmp(name, "PhysXShape") == 0)
		{
			AddFlatMixIn(entry, entity.PhysXShape, PhysXShapes);

			return;
		}

		if (strcmp(name, "PhysXProp") == 0)
		{
			AddFlatMixIn(entry, entity.PhysXMesh, PhysXMeshes);

			return;
		}

		if (strcmp(name, "MS2Fluid") == 0)
		{
			AddFlatMixIn(entry, entity.Fluid, Fluids);

			return;
		}

		if (strcmp(name, "MS2Vibrate") == 0)
		{
			AddFlatMixIn(entry, entity.Vibrate, VibrateObjects);

			return;
		}

		if (strcmp(name, "MS2Breakable") == 0)
		{
			AddFlatMixIn(entry, entity.Breakable, Breakable);

			return;
		}

		if (strcmp(name, "MS2MapProperties") == 0)
		{
			AddFlatMixIn(entry, entity.MapProperties, MapProperties);

			return;
		}

		if (strcmp(name, "PhysXWhitebox") == 0)
		{
			AddFlatMixIn(entry, entity.PhysXWhitebox, PhysXWhiteboxes);

			return;
		}

		if (strcmp(name, "DirectionalLight") == 0)
		{
			AddFlatMixIn(entry, entity.Light, Lights);

			Lights[entity.Light].Type = EntityLightType::Directional;

			return;
		}

		if (strcmp(name, "PointLight") == 0)
		{
			AddFlatMixIn(entry, entity.Light, Lights);

			Lights[entity.Light].Type = EntityLightType::Point;

			return;
		}

		if (strcmp(name, "AmbientLight") == 0)
		{
			AddFlatMixIn(entry, entity.Light, Lights);

			Lights[entity.Light].Type = EntityLightType::Ambient;

			return;
		}
	}

	void FlatLibrary::LoadEntity(FlatEntry& entry, XmlLite::XmlReader& document, std::string_view name)
	{
		FlatEntity& entity = Entities[entry.Entity];

		entity.Id = document.ReadAttributeValue<std::string_view>("id", "");

		if (name.size() != 0)
		{
			LoadMixin(entry, entity, name);
		}

		const Archive::Metadata::Entry* modelEntry = nullptr;
		bool popNode = false;

		XmlLite::XmlReader::StackMarker traitMarker = document.GetStackMarker();

		for (const XmlLite::XmlNode* traitNode = document.GetFirstChild(); traitNode; traitNode = document.GetNextSibling(traitMarker))
		{
			popNode = true;

			std::string_view type = traitNode->Name;

			if (strcmp(type, "trait") == 0)
			{
				continue;
			}

			std::string_view name = document.ReadAttributeValue<std::string_view>("name", "");

			if (strcmp(type, "mixin") == 0)
			{
				LoadMixin(entry, entity, name);

				continue;
			}

			if (strcmp(type, "property") == 0)
			{
				const XmlLite::XmlNode* setNode = document.GetFirstChild("set");

				if (setNode == nullptr) continue;

				
				const auto get = [] <typename T> (std::vector<T>& vector, size_t index) -> T*
				{
					if (index == (size_t)-1) return nullptr;

					return &vector[index];
				};

				LoadEntityProperties(get(Entities, entry.Entity), document, name) ||
				LoadPlaceableProperties(get(Placeables, entity.Placeable), document, name) ||
				LoadMeshProperties(get(Meshes, entity.Mesh), document, name) ||
				LoadLightProperties(get(Lights, entity.Light), document, name) ||
				LoadPortalProperties(get(Portals, entity.Portal), document, name) ||
				LoadMapProperties(get(MapProperties, entity.MapProperties), document, name) ||
				LoadVibrateProperties(get(VibrateObjects, entity.Vibrate), document, name) ||
				LoadBreakableProperties(get(Breakable, entity.Breakable), document, name) ||
				LoadPhysXMeshProperties(get(PhysXMeshes, entity.PhysXMesh), document, name) || 
				LoadPhysXWhiteboxProperties(get(PhysXWhiteboxes, entity.PhysXWhitebox), document, name);

				continue;
			}
		}

		if (entity.Placeable != (size_t)-1)
			Placeables[entity.Placeable].Transformation = getMatrix(Placeables[entity.Placeable].Position, Placeables[entity.Placeable].Rotation, Placeables[entity.Placeable].Scale);
	}

	bool FlatLibrary::LoadEntityProperties(FlatEntity* entity, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (/*strcmp(name, "NifAsset") == 0 ||*/ strcmp(name, "ProxyNifAsset") == 0)
		{
			std::string_view uuid = document.ReadAttributeValue<std::string_view>("value", "urn:llid:null");

			uuid = { uuid.data() + 9, uuid.size() - 9 };
		
			const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTagsWithLink(Archive::ParseHexInt(uuid, 0), "gamebryo-scenegraph");
		
			if (entry != nullptr)
			{
				entity->ProxyModel = AssetLibrary.GetModels().FetchModel(entry);
			}
		
			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadPlaceableProperties(FlatPlaceable* placeable, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (placeable == nullptr) return false;

		if (strcmp(name, "IsVisible") == 0 && false)
		{
			placeable->IsVisible = lower(document.ReadAttributeValue<std::string>("value", "true")) == "true";

			return true;
		}

		if (strcmp(name, "Position") == 0)
		{
			placeable->Position = document.ReadAttributeValue<Vector3SF>("value", Vector3SF());

			return true;
		}

		if (strcmp(name, "Rotation") == 0)
		{
			placeable->Rotation = document.ReadAttributeValue<Vector3SF>("value", Vector3SF());

			return true;
		}

		if (strcmp(name, "Scale") == 0)
		{
			placeable->Scale = document.ReadAttributeValue<float>("value", 1);

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadMeshProperties(FlatMesh* mesh, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (mesh == nullptr) return false;

		if (strcmp(name, "NifAsset") == 0/* || strcmp(name, "ProxyNifAsset") == 0*/)
		{
			std::string_view uuid = document.ReadAttributeValue<std::string_view>("value", "urn:llid:null");

			uuid = { uuid.data() + 9, uuid.size() - 9 };

			const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTagsWithLink(Archive::ParseHexInt(uuid, 0), "gamebryo-scenegraph");

			if (entry != nullptr)
			{
				//if (strcmp(name, "ProxyNifAsset") == 0)
				//	mesh->ProxyModel = AssetLibrary.GetModels().FetchModel(entry);
				//else
					mesh->Model = AssetLibrary.GetModels().FetchModel(entry);
			}

			return true;
		}

		if (strcmp(name, "MaterialColor") == 0)
		{
			mesh->MaterialColor = document.ReadAttributeValue<Color3>("value", Color3(1.f, 1, 1));

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadLightProperties(FlatLight* light, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (light == nullptr) return false;

		if (strcmp(name, "Dimmer") == 0)
		{
			light->Dimmer = document.ReadAttributeValue<float>("value", 0);

			return true;
		}

		if (strcmp(name, "DiffuseColor") == 0)
		{
			light->DiffuseColor = document.ReadAttributeValue<Color3>("value", Color3(0.f, 0, 0));

			return true;
		}

		if (strcmp(name, "SpecularColor") == 0)
		{
			light->SpecularColor = document.ReadAttributeValue<Color3>("value", Color3(0.f, 0, 0));

			return true;
		}

		if (strcmp(name, "AmbientColor") == 0)
		{
			light->AmbientColor = document.ReadAttributeValue<Color3>("value", Color3(0.f, 0, 0));

			return true;
		}

		if (strcmp(name, "CastShadows") == 0)
		{
			light->CastsShadows = lower(document.ReadAttributeValue<std::string>("value", "false")) == "true";

			return true;
		}

		if (strcmp(name, "Range") == 0)
		{
			light->Range = document.ReadAttributeValue<float>("value", 0);

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadPortalProperties(FlatPortal* portal, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (portal == nullptr) return false;

		if (strcmp(name, "TargetFieldSN") == 0)
		{
			portal->TargetField = padId(document.ReadAttributeValue<std::string>("value", ""));

			return true;
		}

		if (strcmp(name, "TargetPortalID") == 0)
		{
			portal->TargetPortal = document.ReadAttributeValue<int>("value", -1);

			return true;
		}

		if (strcmp(name, "PortalID") == 0)
		{
			portal->PortalId = document.ReadAttributeValue<int>("value", -1);

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadMapProperties(FlatMapProperties* mapProperties, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (mapProperties == nullptr) return false;

		if (strcmp(name, "CubeType") == 0)
		{
			std::string cubeType = document.ReadAttributeValue<std::string>("value", "None");

			if (cubeType == "None")
				mapProperties->CubeType = EntityCubeType::None;
			if (cubeType == "Ground")
				mapProperties->CubeType = EntityCubeType::Ground;
			if (cubeType == "Fluid")
				mapProperties->CubeType = EntityCubeType::Fluid;
			if (cubeType == "Wall")
				mapProperties->CubeType = EntityCubeType::Wall;
			if (cubeType == "Object")
				mapProperties->CubeType = EntityCubeType::Object;
			if (cubeType == "Building")
				mapProperties->CubeType = EntityCubeType::Building;

			return true;
		}

		if (strcmp(name, "GeneratePhysX") == 0)
		{
			mapProperties->GeneratePhysX = lower(document.ReadAttributeValue<std::string>("value", "false")) == "true";

			return true;
		}

		if (strcmp(name, "DisableCollision") == 0)
		{
			mapProperties->DisableCollision = lower(document.ReadAttributeValue<std::string>("value", "false")) == "true";

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadVibrateProperties(FlatVibrate* vibrate, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (vibrate == nullptr) return false;

		if (strcmp(name, "Enabled") == 0)
		{
			vibrate->Enabled = document.ReadAttributeValue<std::string>("value", "True") == "True";

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadBreakableProperties(FlatBreakable* breakable, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (breakable == nullptr) return false;

		if (strcmp(name, "Enabled") == 0)
		{
			breakable->Enabled = document.ReadAttributeValue<std::string>("value", "True") == "True";

			return true;
		}

		if (strcmp(name, "NxCollision") == 0)
		{
			breakable->NxCollision = document.ReadAttributeValue<std::string>("value", "True") == "True";

			return true;
		}

		if (strcmp(name, "PropCollisionGroup") == 0)
		{
			int value = document.ReadAttributeValue<int>("value", 0);

			switch (value)
			{
			case 0: breakable->CollisionGroup = EntityCollisionGroup::CollisionGroup0;
				break;
			case 7: breakable->CollisionGroup = EntityCollisionGroup::CollisionGroup7;
				break;
			case 8: breakable->CollisionGroup = EntityCollisionGroup::CollisionGroup8;
				break;
			case 9: breakable->CollisionGroup = EntityCollisionGroup::CollisionGroup9;
				break;
			default: break;
			}

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadPhysXMeshProperties(FlatPhysXMesh* mesh, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (mesh == nullptr) return false;

		if (strcmp(name, "PropCollisionGroup") == 0)
		{
			int value = document.ReadAttributeValue<int>("value", 0);

			switch (value)
			{
			case 0: mesh->CollisionGroup = EntityCollisionGroup::CollisionGroup0;
				break;
			case 7: mesh->CollisionGroup = EntityCollisionGroup::CollisionGroup7;
				break;
			case 8: mesh->CollisionGroup = EntityCollisionGroup::CollisionGroup8;
				break;
			case 9: mesh->CollisionGroup = EntityCollisionGroup::CollisionGroup9;
				break;
			default: break;
			}

			return true;
		}

		return false;
	}

	bool FlatLibrary::LoadPhysXWhiteboxProperties(FlatPhysXWhitebox* box, XmlLite::XmlReader& document, const std::string_view& name)
	{
		if (box == nullptr) return false;

		if (strcmp(name, "ShapeDimensions") == 0)
		{
			box->ShapeDimensions = document.ReadAttributeValue<Vector3SF>("value", {});

			return true;
		}

		return false;
	}


}