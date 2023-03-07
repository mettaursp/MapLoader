#include "TextureAsset.h"

namespace MapLoader
{
	VkSamplerCreateInfo TextureAsset::GetDefaultSampler()
	{
		VkSamplerCreateInfo samplerCreateInfo{ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
		samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerCreateInfo.maxLod = FLT_MAX;

		return samplerCreateInfo;
	}
}