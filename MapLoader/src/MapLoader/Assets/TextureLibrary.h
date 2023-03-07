#pragma once

#include <vector>

#include <ArchiveParser/ArchiveReader.h>
#include <MapLoader/Vulkan/VulkanContext.h>

#include "TextureAsset.h"

namespace MapLoader
{
	class TextureLibrary
	{
	public:
		TextureLibrary(const std::shared_ptr<Archive::ArchiveReader>& reader, const std::shared_ptr<Graphics::VulkanContext>& vulkanContext);
		~TextureLibrary();

		int FetchTexture(const std::string& name, VkFormat format, VkSamplerCreateInfo samplerInfo = TextureAsset::GetDefaultSampler());

		void FlushLoadingQueue(const VkCommandBuffer& cmdBuf);
		void FlushLoadingQueue();

		const std::vector<TextureAsset>& GetAssets() const { return Assets; }

		void FreeResources();

	private:
		std::shared_ptr<Archive::ArchiveReader> Reader;
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		std::string LoadingBuffer;
		std::vector<TextureAsset> Assets = { {} };
		std::unordered_map<const Archive::Metadata::Entry*, size_t> AssetMap;
		std::vector<size_t> LoadingQueue = { 0 };

		bool LoadDDS(const VkCommandBuffer& cmdBuf, TextureAsset& asset);
	};
}