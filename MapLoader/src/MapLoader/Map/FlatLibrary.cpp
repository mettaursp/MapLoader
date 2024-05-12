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

		FlatEntry flatEntry = { &Entities.back() };

		flatFile.Read(DocumentBuffer);

		XmlLite::XmlReader document;

		document.OpenDocument(DocumentBuffer);

		document.GetFirstChild();

		LoadEntity(flatEntry, document);

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
	void AddFlatMixInFrom(const FlatType* parent, FlatEntry& entry, FlatType*& pointer, size_t& pointerIndex, std::vector<FlatType>& vector)
	{
		if (parent == nullptr) return;

		vector.push_back(*parent);

		pointer = &vector.back();
		pointer->Index = vector.size() - 1;
		pointer->Parent = entry.Entity->Index;
		pointerIndex = pointer->Index;
	}

	FlatEntry FlatLibrary::LoadEntityFromFlat(const FlatEntry& flat, XmlLite::XmlReader& document)
	{
		Entities.push_back({ Entities.size(), flat.Entity->Entry });

		FlatEntry entityEntry = { &Entities.back() };

		AddFlatMixInFrom(flat.Placeable, entityEntry, entityEntry.Placeable, entityEntry.Entity->PlaceableIndex, Placeables);
		AddFlatMixInFrom(flat.Mesh, entityEntry, entityEntry.Mesh, entityEntry.Entity->MeshIndex, Meshes);
		AddFlatMixInFrom(flat.Light, entityEntry, entityEntry.Light, entityEntry.Entity->LightIndex, Lights);
		AddFlatMixInFrom(flat.Portal, entityEntry, entityEntry.Portal, entityEntry.Entity->PortalIndex, Portals);

		LoadEntity(entityEntry, document);

		return entityEntry;
	}

	FlatEntry FlatLibrary::FetchEntry(size_t index)
	{
		if (index == (size_t)-1)
			return {};

		FlatEntity* entity = &Entities[index];

		return { 
			entity,
			entity->PlaceableIndex != (size_t)-1 ? &Placeables[entity->PlaceableIndex] : nullptr,
			entity->MeshIndex != (size_t)-1 ? &Meshes[entity->MeshIndex] : nullptr,
			entity->LightIndex != (size_t)-1 ? &Lights[entity->LightIndex] : nullptr,
			entity->PortalIndex != (size_t)-1 ? &Portals[entity->PortalIndex] : nullptr
		};
	}

	template <typename FlatType>
	void AddFlatMixIn(FlatEntry& entry, FlatType*& pointer, size_t& pointerIndex, std::vector<FlatType>& vector)
	{
		if (pointer != nullptr) return;

		vector.push_back({ vector.size(), entry.Entity->Index });

		pointer = &vector.back();
		pointerIndex = pointer->Index;
	}

	void FlatLibrary::LoadEntity(FlatEntry& entry, XmlLite::XmlReader& document)
	{
		entry.Entity->Id = document.ReadAttributeValue<std::string_view>("id", "");

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
				if (strcmp(name, "Placeable") == 0)
				{
					AddFlatMixIn(entry, entry.Placeable, entry.Entity->PlaceableIndex, Placeables);

					continue;
				}

				if (strcmp(name, "Mesh") == 0)
				{
					AddFlatMixIn(entry, entry.Mesh, entry.Entity->MeshIndex, Meshes);

					continue;
				}

				if (strcmp(name, "Light") == 0)
				{
					AddFlatMixIn(entry, entry.Light, entry.Entity->LightIndex, Lights);

					continue;
				}

				if (strcmp(name, "Portal") == 0)
				{
					AddFlatMixIn(entry, entry.Portal, entry.Entity->PortalIndex, Portals);

					continue;
				}

				if (strcmp(name, "DirectionalLight") == 0)
				{
					AddFlatMixIn(entry, entry.Light, entry.Entity->LightIndex, Lights);

					entry.Light->Type = EntityLightType::Directional;

					continue;
				}

				if (strcmp(name, "PointLight") == 0)
				{
					AddFlatMixIn(entry, entry.Light, entry.Entity->LightIndex, Lights);

					entry.Light->Type = EntityLightType::Point;

					continue;
				}

				if (strcmp(name, "AmbientLight") == 0)
				{
					AddFlatMixIn(entry, entry.Light, entry.Entity->LightIndex, Lights);

					entry.Light->Type = EntityLightType::Ambient;

					continue;
				}

				continue;
			}

			if (strcmp(type, "property") == 0)
			{
				const XmlLite::XmlNode* setNode = document.GetFirstChild("set");

				if (setNode == nullptr) continue;

				LoadEntityProperties(entry.Entity, document, name) ||
				LoadPlaceableProperties(entry.Placeable, document, name) ||
				LoadMeshProperties(entry.Mesh, document, name) ||
				LoadLightProperties(entry.Light, document, name) ||
				LoadPortalProperties(entry.Portal, document, name);

				continue;
			}
		}

		if (entry.Placeable != nullptr)
			entry.Placeable->Transformation = getMatrix(entry.Placeable->Position, entry.Placeable->Rotation, entry.Placeable->Scale);
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
}