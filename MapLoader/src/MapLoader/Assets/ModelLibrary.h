#pragma once

#include <unordered_set>

#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include <ArchiveParser/MetadataMapper.h>
#include <MapLoader/Assets/ModelData.h>
#include "TextureLibrary.h"
#include <host_device.h>
#include <MapLoader/obj_loader.h>

namespace MapLoader
{
	class GameAssetLibrary;

	class ModelLibrary
	{
	public:
		ModelLibrary(GameAssetLibrary& assetLibrary);
		~ModelLibrary();

		ModelData* FetchModel(const Archive::Metadata::Entry* entry, bool keepRawData = false);

		const auto& GetUnmappedMaterials() const { return UnmappedMaterials; }
		const auto& GetModels() const { return Models; }
		const auto& GetMeshDescriptions() const { return MeshDescriptions; }
		const auto& GetGpuData() const { return GpuMeshData; }
		const auto& GetTextureTransforms() const { return TextureTransforms; }
		auto& GetMaterialTextures() { return MaterialTextures; }
		const auto& GetMaterialTextures() const { return MaterialTextures; }
		auto& GetTextureTransforms() { return TextureTransforms; }

		void FreeResources();

		static const std::unordered_map<std::string, int> MaterialTypeMap;

	private:
		GameAssetLibrary& AssetLibrary;
		std::string NifDocumentBuffer;
		std::shared_ptr<Engine::Graphics::MeshFormat> ImportFormat;
		std::shared_ptr<Engine::Graphics::MeshFormat> ImportFormatWithColor;
		std::shared_ptr<Engine::Graphics::MeshFormat> ImportFormatWithBinormal;
		std::shared_ptr<Engine::Graphics::MeshFormat> ImportFormatWithColorAndBinormal;
		std::map<const Archive::Metadata::Entry*, size_t> ModelMap;
		std::vector<TextureTransform> TextureTransforms;
		std::vector<std::unique_ptr<ModelData>> Models;
		std::vector<ObjDesc> GpuMeshData;
		std::vector<MeshDescription> MeshDescriptions;
		std::vector<MaterialTextures> MaterialTextures;
		int DuplicateFormatUses = 0;

		static std::unordered_set<std::string> UnmappedMaterials;

		bool FetchModel(const Archive::ArchivePath& file, ModelData& loadedModel, bool keepRawData = false);
		uint32_t LoadModel(ObjLoader& loader, const Matrix4F& transform = Matrix4F(), bool invisible = false);
	};
}