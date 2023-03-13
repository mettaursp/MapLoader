#include "FlatLibrary.h"

#include <ArchiveParser/ParserUtils.h>
#include <MapLoader/Assets/GameAssetLibrary.h>

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

		tinyxml2::XMLDocument document;

		flatFile.Read(DocumentBuffer);
		document.Parse(DocumentBuffer.data(), DocumentBuffer.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		LoadEntity(flatEntry, rootElement);

		return flatEntry;
	}

	FlatEntry FlatLibrary::FetchFlat(const std::string& name)
	{
		if (name.empty())
			return {};

		std::string lowerName = lower(name);

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

	FlatEntry FlatLibrary::LoadEntityFromFlat(const FlatEntry& flat, tinyxml2::XMLElement* entityElement)
	{
		Entities.push_back({ Entities.size(), flat.Entity->Entry });

		FlatEntry entityEntry = { &Entities.back() };

		AddFlatMixInFrom(flat.Placeable, entityEntry, entityEntry.Placeable, entityEntry.Entity->PlaceableIndex, Placeables);
		AddFlatMixInFrom(flat.Mesh, entityEntry, entityEntry.Mesh, entityEntry.Entity->MeshIndex, Meshes);
		AddFlatMixInFrom(flat.Light, entityEntry, entityEntry.Light, entityEntry.Entity->LightIndex, Lights);
		AddFlatMixInFrom(flat.Portal, entityEntry, entityEntry.Portal, entityEntry.Entity->PortalIndex, Portals);

		LoadEntity(entityEntry, entityElement);

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

	void FlatLibrary::LoadEntity(FlatEntry& entry, tinyxml2::XMLElement* entityElement)
	{
		entry.Entity->Id = readAttribute<const char*>(entityElement, "id", "");

		const Archive::Metadata::Entry* modelEntry = nullptr;

		for (tinyxml2::XMLElement* traitElement = entityElement->FirstChildElement(); traitElement; traitElement = traitElement->NextSiblingElement())
		{
			const char* type = traitElement->Name();

			if (strcmp(type, "trait") == 0)
			{
				continue;
			}

			const char* name = readAttribute<const char*>(traitElement, "name", "");

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
				tinyxml2::XMLElement* setElement = traitElement->FirstChildElement("set");

				LoadEntityProperties(entry.Entity, setElement, name);
				LoadPlaceableProperties(entry.Placeable, setElement, name);
				LoadMeshProperties(entry.Mesh, setElement, name);
				LoadLightProperties(entry.Light, setElement, name);
				LoadPortalProperties(entry.Portal, setElement, name);

				continue;
			}
		}

		if (entry.Placeable != nullptr)
			entry.Placeable->Transformation = getMatrix(entry.Placeable->Position, entry.Placeable->Rotation, entry.Placeable->Scale);
	}

	void FlatLibrary::LoadEntityProperties(FlatEntity* entity, tinyxml2::XMLElement* setElement, const char* name)
	{
		if (strcmp(name, "NifAsset") == 0 || strcmp(name, "ProxyNifAsset") == 0)
		{
			const char* uuid = readAttribute<const char*>(setElement, "value", "urn:llid:null") + 9;

			const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTagsWithLink(Archive::ParseHexInt(uuid, 0), "gamebryo-scenegraph");

			if (entry != nullptr)
			{
				entity->ProxyModel = AssetLibrary.GetModels().FetchModel(entry);
			}

			return;
		}
	}

	void FlatLibrary::LoadPlaceableProperties(FlatPlaceable* placeable, tinyxml2::XMLElement* setElement, const char* name)
	{
		if (placeable == nullptr) return;

		if (strcmp(name, "IsVisible") == 0 && false)
		{
			placeable->IsVisible = lower(readAttribute<const char*>(setElement, "value", "true")) == "true";

			return;
		}

		if (strcmp(name, "Position") == 0)
		{
			placeable->Position = readAttribute<Vector3SF>(setElement, "value", Vector3SF());

			return;
		}

		if (strcmp(name, "Rotation") == 0)
		{
			placeable->Rotation = readAttribute<Vector3SF>(setElement, "value", Vector3SF());

			return;
		}

		if (strcmp(name, "Scale") == 0)
		{
			placeable->Scale = readAttribute<float>(setElement, "value", 1);

			return;
		}
	}

	void FlatLibrary::LoadMeshProperties(FlatMesh* mesh, tinyxml2::XMLElement* setElement, const char* name)
	{
		if (mesh == nullptr) return;

		if (strcmp(name, "NifAsset") == 0 || strcmp(name, "ProxyNifAsset") == 0)
		{
			const char* uuid = readAttribute<const char*>(setElement, "value", "urn:llid:null") + 9;

			const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTagsWithLink(Archive::ParseHexInt(uuid, 0), "gamebryo-scenegraph");

			if (entry != nullptr)
			{
				mesh->Model = AssetLibrary.GetModels().FetchModel(entry);
			}

			return;
		}

		if (strcmp(name, "MaterialColor") == 0)
		{
			mesh->MaterialColor = readAttribute<Color3>(setElement, "value", Color3(1.f, 1, 1));

			return;
		}
	}

	void FlatLibrary::LoadLightProperties(FlatLight* light, tinyxml2::XMLElement* setElement, const char* name)
	{
		if (light == nullptr) return;

		if (strcmp(name, "Dimmer") == 0)
		{
			light->Dimmer = readAttribute<float>(setElement, "value", 0);

			return;
		}

		if (strcmp(name, "DiffuseColor") == 0)
		{
			light->DiffuseColor = readAttribute<Color3>(setElement, "value", Color3(0.f, 0, 0));

			return;
		}

		if (strcmp(name, "SpecularColor") == 0)
		{
			light->SpecularColor = readAttribute<Color3>(setElement, "value", Color3(0.f, 0, 0));

			return;
		}

		if (strcmp(name, "AmbientColor") == 0)
		{
			light->AmbientColor = readAttribute<Color3>(setElement, "value", Color3(0.f, 0, 0));

			return;
		}

		if (strcmp(name, "CastShadows") == 0)
		{
			light->CastsShadows = lower(readAttribute<const char*>(setElement, "value", "false")) == "true";

			return;
		}

		if (strcmp(name, "Range") == 0)
		{
			light->Range = readAttribute<float>(setElement, "value", 0);

			return;
		}
	}

	void FlatLibrary::LoadPortalProperties(FlatPortal* portal, tinyxml2::XMLElement* setElement, const char* name)
	{
		if (portal == nullptr) return;

		if (strcmp(name, "TargetFieldSN") == 0)
		{
			portal->TargetField = padId(readAttribute<std::string>(setElement, "value", ""));

			return;
		}

		if (strcmp(name, "TargetPortalID") == 0)
		{
			portal->TargetPortal = readAttribute<int>(setElement, "value", -1);

			return;
		}

		if (strcmp(name, "PortalID") == 0)
		{
			portal->PortalId = readAttribute<int>(setElement, "value", -1);

			return;
		}
	}
}