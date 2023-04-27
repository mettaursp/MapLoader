#pragma once

#include <nvvk/resourceallocator_vk.hpp>
#include <ArchiveParser/MetadataMapper.h>
#include <vulkan/vulkan_core.h>

namespace MapLoader
{
	struct TextureAsset
	{
		int Id = 0;
		nvvk::Texture Data;
		const Archive::Metadata::Entry* Entry = nullptr;
		VkFormat Format = VK_FORMAT_R8G8B8A8_SRGB;
		VkSamplerCreateInfo SamplerInfo = GetDefaultSampler();
		bool HasTransparency = false;
		bool HasInvisibility = false;

		static VkSamplerCreateInfo GetDefaultSampler();
	};
}