#pragma once

#include <unordered_set>

#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include <ArchiveParser/MetadataMapper.h>
#include <ArchiveParser/ArchiveReader.h>
#include <MapLoader/Assets/ModelData.h>
#include "TextureLibrary.h"
#include <host_device.h>
#include <MapLoader/obj_loader.h>

namespace MapLoader
{

	class ModelLibrary
	{
	public:
		ModelLibrary(
			const std::shared_ptr<Archive::ArchiveReader>& reader,
			const std::shared_ptr<TextureLibrary>& textureLibrary,
			const std::shared_ptr<Graphics::VulkanContext>& vulkanContext);
		~ModelLibrary();

		ModelData* FetchModel(const Archive::Metadata::Entry* entry, bool keepRawData = false);

		const auto& GetUnmappedMaterials() const { return UnmappedMaterials; }
		const auto& GetModels() const { return Models; }
		const auto& GetMeshDescriptions() const { return MeshDescriptions; }
		const auto& GetGpuData() const { return GpuMeshData; }
		const auto& GetTextureTransforms() const { return TextureTransforms; }
		auto& GetTextureTransforms() { return TextureTransforms; }

		void FreeResources();

		static const std::unordered_map<std::string, int> MaterialTypeMap;

	private:
		std::shared_ptr<Archive::ArchiveReader> Reader;
		std::shared_ptr<TextureLibrary> TextureLibrary;
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
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

		static std::unordered_set<std::string> UnmappedMaterials;

		bool FetchModel(const Archive::ArchivePath& file, ModelData& loadedModel, bool keepRawData = false);
		uint32_t LoadModel(ObjLoader& loader, const Matrix4F& transform = Matrix4F(), bool invisible = false);
	};
}