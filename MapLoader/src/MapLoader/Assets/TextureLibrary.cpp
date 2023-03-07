#include "TextureLibrary.h"

#include <nvvk/images_vk.hpp>
#include <nvvk/commands_vk.hpp>
#include <Engine/Math/Color4I.h>
#include <tinygltf/stb_image.h>
#include <ArchiveParser/ParserUtils.h>

namespace MapLoader
{
	TextureLibrary::TextureLibrary(const std::shared_ptr<Archive::ArchiveReader>& reader, const std::shared_ptr<Graphics::VulkanContext>& vulkanContext) : Reader(reader), VulkanContext(vulkanContext)
	{

	}

	TextureLibrary::~TextureLibrary()
	{
		FreeResources();
	}

	void TextureLibrary::FreeResources()
	{
		for (auto& t : Assets)
		{
			VulkanContext->Allocator.destroy(t.Data);
		}

		Assets.clear();
		AssetMap.clear();
	}

	int TextureLibrary::FetchTexture(const std::string& name, VkFormat format, VkSamplerCreateInfo samplerInfo)
	{
		if (name.empty())
			return -1;

		std::string lowerName = lower(name);

		std::vector<const Archive::Metadata::Entry*> entries;
		const Archive::Metadata::Entry* entry = nullptr;

		if (strncmp(lowerName.data(), "resource/", 9) == 0)
		{
			entry = Archive::Metadata::Entry::FindFirstEntryByTagWithRelPath(name.c_str() + 8, "image");
		}
		else
		{
			Archive::Metadata::Entry::FindEntriesByTags(name, "image", [this, &entry](const auto& newEntry)
				{
					if (entry == nullptr && Reader->GetPath("Resource" + newEntry.RelativePath.string()).Loaded())
					entry = &newEntry;
				}
			);
		}

		const auto& cached = AssetMap.find(entry);

		if (cached != AssetMap.end())
			return (int)cached->second;

		LoadingQueue.push_back(Assets.size());
		int id = (int)Assets.size();

		Assets.push_back({});
		TextureAsset& asset = Assets.back();

		asset.Entry = entry;
		asset.Format = format;
		asset.Id = id;
		asset.SamplerInfo = samplerInfo;

		AssetMap[entry] = id;

		return id;
	}

	void TextureLibrary::FlushLoadingQueue()
	{
		nvvk::CommandPool  cmdBufGet(VulkanContext->Device, VulkanContext->GraphicsQueueIndex);
		VkCommandBuffer    cmdBuf = cmdBufGet.createCommandBuffer();
		FlushLoadingQueue(cmdBuf);
		cmdBufGet.submitAndWait(cmdBuf);
		VulkanContext->Allocator.finalizeAndReleaseStaging();
	}

	void TextureLibrary::FlushLoadingQueue(const VkCommandBuffer& cmdBuf)
	{
		Color4I loadFailPurple = Color4I((Color4I::byte)255, 0, 255, 255);

		for (size_t textureId : LoadingQueue)
		{
			TextureAsset& asset = Assets[textureId];

			if (asset.Entry == nullptr)
			{
				Color4I color = Color4I((Color4I::byte)255, 255, 255, 255);
				VkDeviceSize           bufferSize = sizeof(color);
				auto                   imgSize = VkExtent2D{ 1, 1 };
				auto                   imageCreateInfo = nvvk::makeImage2DCreateInfo(imgSize, asset.Format);

				// Creating the dummy texture
				nvvk::Image           image = VulkanContext->Allocator.createImage(cmdBuf, bufferSize, &color, imageCreateInfo);
				VkImageViewCreateInfo ivInfo = nvvk::makeImageViewCreateInfo(image.image, imageCreateInfo);
				asset.Data = VulkanContext->Allocator.createTexture(image, ivInfo, asset.SamplerInfo);

				// The image format must be in VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
				nvvk::cmdBarrierImageLayout(cmdBuf, asset.Data.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

				continue;
			}

			int texWidth, texHeight, texChannels;

			stbi_uc* stbi_pixels = nullptr;
			stbi_uc* pixels = nullptr;

			std::string extensionText = asset.Entry->LogPath.extension().string();

			Archive::ArchivePath textureFile = Reader->GetPath("Resource" + asset.Entry->RelativePath.string());

			if (textureFile.Loaded())
			{
				textureFile.Read(LoadingBuffer);

				if (extensionText == ".dds")
				{
					if (LoadDDS(cmdBuf, asset))
						continue;
				}
				else
				{
					stbi_load_from_memory(reinterpret_cast<stbi_uc*>(LoadingBuffer.data()), (int)LoadingBuffer.size(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

					pixels = stbi_pixels;
				}
			}

			// Handle failure
			if (!stbi_pixels)
			{
				texWidth = texHeight = 1;
				texChannels = 4;
				pixels = reinterpret_cast<stbi_uc*>(&loadFailPurple);
			}

			VkDeviceSize bufferSize = static_cast<uint64_t>(texWidth) * texHeight * sizeof(uint8_t) * 4;
			auto         imgSize = VkExtent2D{ (uint32_t)texWidth, (uint32_t)texHeight };
			auto         imageCreateInfo = nvvk::makeImage2DCreateInfo(imgSize, asset.Format, VK_IMAGE_USAGE_SAMPLED_BIT, true);

			{
				nvvk::Image image = VulkanContext->Allocator.createImage(cmdBuf, bufferSize, pixels, imageCreateInfo);
				nvvk::cmdGenerateMipmaps(cmdBuf, image.image, asset.Format, imgSize, imageCreateInfo.mipLevels);
				VkImageViewCreateInfo ivInfo = nvvk::makeImageViewCreateInfo(image.image, imageCreateInfo);
				asset.Data = VulkanContext->Allocator.createTexture(image, ivInfo, asset.SamplerInfo);
			}

			stbi_image_free(stbi_pixels);
		}

		LoadingQueue.clear();
	}

	typedef unsigned long DWORD;

	struct DDS_PIXELFORMAT {
		DWORD dwSize;
		DWORD dwFlags;
		DWORD dwFourCC;
		DWORD dwRGBBitCount;
		DWORD dwRBitMask;
		DWORD dwGBitMask;
		DWORD dwBBitMask;
		DWORD dwABitMask;
	};

	struct DDS_HEADER
	{
		DWORD           dwSize;
		DWORD           dwFlags;
		DWORD           dwHeight;
		DWORD           dwWidth;
		DWORD           dwPitchOrLinearSize;
		DWORD           dwDepth;
		DWORD           dwMipMapCount;
		DWORD           dwReserved1[11];
		DDS_PIXELFORMAT ddspf;
		DWORD           dwCaps;
		DWORD           dwCaps2;
		DWORD           dwCaps3;
		DWORD           dwCaps4;
		DWORD           dwReserved2;
	};

	bool TextureLibrary::LoadDDS(const VkCommandBuffer& cmdBuf, TextureAsset& asset)
	{
		const char* bufferData = LoadingBuffer.data();

		if (strncmp(bufferData, "DDS ", 4) != 0)
		{
			std::cout << std::string("not a valid DDS: '" + asset.Entry->RelativePath.string() + "'");

			return false;
		}

		bufferData += 4;

		std::string formatName(bufferData + 80, 4);
		const DDS_HEADER* ddsHeader = reinterpret_cast<const DDS_HEADER*>(bufferData);
		const char* header = bufferData;

		bufferData += sizeof(DDS_HEADER);

		unsigned int linearSize = ddsHeader->dwPitchOrLinearSize;
		int mipLevels = ddsHeader->dwMipMapCount;

		if (ddsHeader->dwWidth == 0 && ddsHeader->dwHeight == 0)
			bufferData += 0;

		if (mipLevels == 0)
			mipLevels = 1;

		unsigned int size = (mipLevels > 1 ? linearSize + linearSize : linearSize);


		int BlockSize = 16;

		VkFormat format;

		if (formatName == std::string("DXT1", 4))
		{
			BlockSize = 8;
			format = VkFormat::VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
		}
		else if (formatName == std::string("DXT3", 4))
			format = VkFormat::VK_FORMAT_BC2_UNORM_BLOCK;
		else if (formatName == std::string("DXT5", 4))
			format = VkFormat::VK_FORMAT_BC3_UNORM_BLOCK;
		else
		{
			std::cout << ("unsupported DDS: '" + asset.Entry->RelativePath.string() + "'");

			return false;
		}

		VkDeviceSize bufferSize = size;//static_cast<uint64_t>(texWidth) * texHeight * sizeof(uint8_t) * 4;
		auto         imgSize = VkExtent2D{ (uint32_t)ddsHeader->dwWidth, (uint32_t)ddsHeader->dwHeight };
		auto         imageCreateInfo = nvvk::makeImage2DCreateInfo(imgSize, format, VK_IMAGE_USAGE_SAMPLED_BIT, mipLevels);

		{
			nvvk::Image image = VulkanContext->Allocator.createImageDDS(cmdBuf, bufferSize, bufferData, imageCreateInfo, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, BlockSize);
			VkImageViewCreateInfo ivInfo = nvvk::makeImageViewCreateInfo(image.image, imageCreateInfo);
			asset.Data = VulkanContext->Allocator.createTexture(image, ivInfo, asset.SamplerInfo);
		}

		return true;
	}
}