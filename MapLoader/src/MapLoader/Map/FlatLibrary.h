#pragma once

#include "FlatModel.h"

namespace XmlLite
{
	class XmlReader;
}

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

	class GameAssetLibrary;

	class FlatLibrary
	{
	public:
		FlatLibrary(
			GameAssetLibrary& assetLibrary,
			FlatLibrary* parentLibrary = nullptr);

		FlatEntry FetchFlat(const Archive::Metadata::Entry* entry);
		FlatEntry FetchFlat(const std::string_view& name);
		FlatEntry LoadEntityFromFlat(const FlatEntry& flat, XmlLite::XmlReader& document);

	private:
		GameAssetLibrary& AssetLibrary;
		FlatLibrary* ParentLibrary = nullptr;
		std::vector<FlatEntity> Entities;
		std::vector<FlatPlaceable> Placeables;
		std::vector<FlatMesh> Meshes;
		std::vector<FlatLight> Lights;
		std::vector<FlatPortal> Portals;
		std::unordered_map<const Archive::Metadata::Entry*, size_t> EntityMap;
		std::string DocumentBuffer;

		FlatEntry FetchEntry(size_t index);

		void LoadEntity(FlatEntry& entry, XmlLite::XmlReader& document);
		bool LoadEntityProperties(FlatEntity* entity, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadPlaceableProperties(FlatPlaceable* entity, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadMeshProperties(FlatMesh* mesh, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadLightProperties(FlatLight* light, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadPortalProperties(FlatPortal* portal, XmlLite::XmlReader& document, const std::string_view& name);
	};
}