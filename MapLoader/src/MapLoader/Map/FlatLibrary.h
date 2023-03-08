#pragma once

#include <MapLoader/Assets/ModelLibrary.h>
#include <MapLoader/Assets/TextureLibrary.h>
#include <tinyxml2/tinyxml2.h>

#include "FlatModel.h"

namespace MapLoader
{
	extern const float PI;
	float degToRad(float deg);
	Matrix4F getMatrix(const Vector3SF& position, const Vector3SF& rotation, float scale, bool isDegrees = true);

	struct FlatEntry
	{
		FlatEntity* Entity = nullptr;
		FlatPlaceable* Placeable = nullptr;
		FlatMesh* Mesh = nullptr;
		FlatLight* Light = nullptr;
		FlatPortal* Portal = nullptr;
	};

	class FlatLibrary
	{
	public:
		FlatLibrary(
			const std::shared_ptr<Archive::ArchiveReader>& reader,
			const std::shared_ptr<ModelLibrary>& modelLibrary,
			const std::shared_ptr<TextureLibrary>& textureLibrary,
			const std::shared_ptr<FlatLibrary>& parentLibrary = nullptr);

		FlatEntry FetchFlat(const Archive::Metadata::Entry* entry);
		FlatEntry FetchFlat(const std::string& name);
		FlatEntry LoadEntityFromFlat(const FlatEntry& flat, tinyxml2::XMLElement* entityElement);

	private:
		std::shared_ptr<Archive::ArchiveReader> Reader;
		std::shared_ptr<ModelLibrary> ModelLibrary;
		std::shared_ptr<TextureLibrary> TextureLibrary;
		std::shared_ptr<FlatLibrary> ParentLibrary;
		std::vector<FlatEntity> Entities;
		std::vector<FlatPlaceable> Placeables;
		std::vector<FlatMesh> Meshes;
		std::vector<FlatLight> Lights;
		std::vector<FlatPortal> Portals;
		std::unordered_map<const Archive::Metadata::Entry*, size_t> EntityMap;
		std::string DocumentBuffer;

		FlatEntry FetchEntry(size_t index);

		void LoadEntity(FlatEntry& entry, tinyxml2::XMLElement* entityElement);
		void LoadEntityProperties(FlatEntity* entity, tinyxml2::XMLElement* setElement, const char* name);
		void LoadPlaceableProperties(FlatPlaceable* entity, tinyxml2::XMLElement* setElement, const char* name);
		void LoadMeshProperties(FlatMesh* mesh, tinyxml2::XMLElement* setElement, const char* name);
		void LoadLightProperties(FlatLight* light, tinyxml2::XMLElement* setElement, const char* name);
		void LoadPortalProperties(FlatPortal* portal, tinyxml2::XMLElement* setElement, const char* name);
	};
}