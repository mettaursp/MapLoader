#pragma once

#include <vector>

#include <ArchiveParser/ArchiveReader.h>
#include <MapLoader/Vulkan/VulkanContext.h>

#include "TextureAsset.h"

namespace MapLoader
{
	class GameAssetLibrary;

	class TextureLibrary
	{
	public:
		TextureLibrary(GameAssetLibrary& assetLibrary);
		~TextureLibrary();

		int FetchTexture(const std::string& name, VkFormat format, VkSamplerCreateInfo samplerInfo = TextureAsset::GetDefaultSampler());

		void FlushLoadingQueue(const VkCommandBuffer& cmdBuf);
		void FlushLoadingQueue();

		const std::vector<TextureAsset>& GetAssets() const { return Assets; }

		void FreeResources();

	private:
		GameAssetLibrary& AssetLibrary;
		std::string LoadingBuffer;
		std::vector<TextureAsset> Assets = { {} };
		std::unordered_map<const Archive::Metadata::Entry*, size_t> AssetMap;
		std::vector<size_t> LoadingQueue = { 0 };

		bool LoadDDS(const VkCommandBuffer& cmdBuf, TextureAsset& asset);
	};
}