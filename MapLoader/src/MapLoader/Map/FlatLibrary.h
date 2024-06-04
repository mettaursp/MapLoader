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

	class FlatLibrary;

	struct FlatEntry
	{
		FlatLibrary* Library = nullptr;
		size_t Entity = (size_t)-1;
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
		auto& GetEntity(size_t i) { return Entities[i]; }
		auto& GetPlaceable(size_t i) { return Placeables[i]; }
		auto& GetMesh(size_t i) { return Meshes[i]; }
		auto& GetLight(size_t i) { return Lights[i]; }
		auto& GetPortal(size_t i) { return Portals[i]; }
		auto& GetPhysXShape(size_t i) { return PhysXShapes[i]; }
		auto& GetPhysXMesh(size_t i) { return PhysXMeshes[i]; }
		auto& GetFluid(size_t i) { return Fluids[i]; }
		auto& GetVibrateObject(size_t i) { return VibrateObjects[i]; }
		auto& GetBreakable(size_t i) { return Breakable[i]; }
		auto& GetMapProperties(size_t i) { return MapProperties[i]; }
		auto& GetPhysXWhitebox(size_t i) { return PhysXWhiteboxes[i]; }

	private:
		GameAssetLibrary& AssetLibrary;
		FlatLibrary* ParentLibrary = nullptr;
		std::vector<FlatEntity> Entities;
		std::vector<FlatPlaceable> Placeables;
		std::vector<FlatMesh> Meshes;
		std::vector<FlatLight> Lights;
		std::vector<FlatPortal> Portals;
		std::vector<FlatPhysXShape> PhysXShapes;
		std::vector<FlatPhysXMesh> PhysXMeshes;
		std::vector<FlatFluid> Fluids;
		std::vector<FlatVibrate> VibrateObjects;
		std::vector<FlatBreakable> Breakable;
		std::vector<FlatMapProperties> MapProperties;
		std::vector<FlatPhysXWhitebox> PhysXWhiteboxes;
		std::unordered_map<const Archive::Metadata::Entry*, size_t> EntityMap;
		std::string DocumentBuffer;

		FlatEntry FetchEntry(size_t index);

		void LoadMixin(FlatEntry& entry, FlatEntity& entity, std::string_view name);
		void LoadEntity(FlatEntry& entry, XmlLite::XmlReader& document, std::string_view name = { "", 0 });
		bool LoadEntityProperties(FlatEntity* entity, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadPlaceableProperties(FlatPlaceable* entity, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadMeshProperties(FlatMesh* mesh, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadLightProperties(FlatLight* light, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadPortalProperties(FlatPortal* portal, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadMapProperties(FlatMapProperties* mapProperties, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadVibrateProperties(FlatVibrate* vibrate, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadBreakableProperties(FlatBreakable* breakable, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadPhysXMeshProperties(FlatPhysXMesh* mesh, XmlLite::XmlReader& document, const std::string_view& name);
		bool LoadPhysXWhiteboxProperties(FlatPhysXWhitebox* box, XmlLite::XmlReader& document, const std::string_view& name);
	};
}