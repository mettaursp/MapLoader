#include "TextureLibrary.h"

#include <nvvk/images_vk.hpp>
#include <nvvk/commands_vk.hpp>
#include <Engine/Math/Color4I.h>
#include <tinygltf/stb_image.h>
#include <ArchiveParser/ParserUtils.h>
#include <MapLoader/Assets/GameAssetLibrary.h>
#include <Engine/Assets/ParserUtils.h>

namespace MapLoader
{
	TextureLibrary::TextureLibrary(GameAssetLibrary& assetLibrary) : AssetLibrary(assetLibrary)
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
			AssetLibrary.GetVulkanContext()->Allocator.destroy(t.Data);
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
					if (entry == nullptr && AssetLibrary.GetReader()->GetPath("Resource" + newEntry.RelativePath.string()).Loaded())
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
		nvvk::CommandPool  cmdBufGet(AssetLibrary.GetVulkanContext()->Device, AssetLibrary.GetVulkanContext()->GraphicsQueueIndex);
		VkCommandBuffer    cmdBuf = cmdBufGet.createCommandBuffer();
		FlushLoadingQueue(cmdBuf);
		cmdBufGet.submitAndWait(cmdBuf);
		AssetLibrary.GetVulkanContext()->Allocator.finalizeAndReleaseStaging();
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
				nvvk::Image           image = AssetLibrary.GetVulkanContext()->Allocator.createImage(cmdBuf, bufferSize, &color, imageCreateInfo);
				VkImageViewCreateInfo ivInfo = nvvk::makeImageViewCreateInfo(image.image, imageCreateInfo);
				asset.Data = AssetLibrary.GetVulkanContext()->Allocator.createTexture(image, ivInfo, asset.SamplerInfo);

				// The image format must be in VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
				nvvk::cmdBarrierImageLayout(cmdBuf, asset.Data.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

				continue;
			}

			int texWidth, texHeight, texChannels;

			stbi_uc* stbi_pixels = nullptr;
			stbi_uc* pixels = nullptr;

			std::string extensionText = asset.Entry->LogPath.extension().string();

			Archive::ArchivePath textureFile = AssetLibrary.GetReader()->GetPath("Resource" + asset.Entry->RelativePath.string());

			if (textureFile.Loaded())
			{
				textureFile.Read(LoadingBuffer);

				if (extensionText == ".dds")
				{
					if (LoadDDS(cmdBuf, asset))
					{
						continue;
					}
				}
				else
				{
					stbi_load_from_memory(reinterpret_cast<stbi_uc*>(LoadingBuffer.data()), (int)LoadingBuffer.size(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

					for (int i = 3; i < texWidth * texHeight && !asset.HasInvisibility; i += 4)
					{
						stbi_uc alpha = LoadingBuffer[i];
						asset.HasTransparency |= alpha != 0xFF;
						asset.HasInvisibility |= alpha == 0;

						if (asset.HasInvisibility)
							break;
					}

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
				nvvk::Image image = AssetLibrary.GetVulkanContext()->Allocator.createImage(cmdBuf, bufferSize, pixels, imageCreateInfo);
				nvvk::cmdGenerateMipmaps(cmdBuf, image.image, asset.Format, imgSize, imageCreateInfo.mipLevels);
				VkImageViewCreateInfo ivInfo = nvvk::makeImageViewCreateInfo(image.image, imageCreateInfo);
				asset.Data = AssetLibrary.GetVulkanContext()->Allocator.createTexture(image, ivInfo, asset.SamplerInfo);
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

	void CheckTransparencyDxt1(const char* data, VkDeviceSize size, VkExtent3D dimensions, bool& hasTransparency, bool& hasInvisibility)
	{
		Endian endian = Endian(std::endian::little);

		std::string_view stream(data, size);

		for (size_t y = 0; y < dimensions.height; y += 4)
		{
			for (size_t x = 0; x < dimensions.width; x += 4)
			{
				unsigned short color0 = endian.read<unsigned short>(stream);
				unsigned short color1 = endian.read<unsigned short>(stream);
				unsigned int encoding = endian.read<unsigned int>(stream); // blending

				// only full transparency supported
				if (color0 > color1) continue;

				for (size_t i = 0; i < 4; ++i, encoding >>= 2)
				{
					if ((encoding & 3) >= 3)
					{
						hasTransparency |= true;
						hasInvisibility |= true;

						return;
					}
				}
			}
		}
	}

	void CheckTransparencyDxt3(const char* data, VkDeviceSize size, VkExtent3D dimensions, bool& hasTransparency, bool& hasInvisibility)
	{
		Endian endian = Endian(std::endian::little);

		std::string_view stream(data, size);

		for (size_t y = 0; y < dimensions.height; y += 4)
		{
			for (size_t x = 0; x < dimensions.width; x += 4)
			{
				unsigned int alpha0 = endian.read<unsigned int>(stream);
				unsigned int alpha1 = endian.read<unsigned int>(stream);

				endian.read<unsigned short>(stream); // color0
				endian.read<unsigned short>(stream); // color1

				endian.read<unsigned int>(stream); // blending


				for (size_t j = 0; j < 4; ++j)
				{
					for (size_t i = 0; i < 4; ++i)
					{
						if (x + i >= dimensions.width || y + j >= dimensions.height) continue;

						unsigned char alpha = 0;

						if (j < 2)
							alpha = 17 * (unsigned char)((alpha0 >> (4 * (4 * j + i))) & 0xF);
						else
							alpha = 17 * (unsigned char)((alpha1 >> (4 * (4 * (j - 2) + i))) & 0xF);

						hasTransparency |= alpha != 0xFF;
						hasInvisibility |= alpha == 0;

						if (hasInvisibility)
							return;
					}
				}
			}
		}
	}

	void CheckTransparencyDxt5(const char* data, VkDeviceSize size, VkExtent3D dimensions, bool& hasTransparency, bool& hasInvisibility)
	{
		Endian endian = Endian(std::endian::little);

		std::string_view stream(data, size);

		for (size_t y = 0; y < dimensions.height; y += 4)
		{
			for (size_t x = 0; x < dimensions.width; x += 4)
			{
				unsigned int alpha0 = endian.read<unsigned char>(stream);
				unsigned int alpha1 = endian.read<unsigned char>(stream);

				unsigned int alphaBlending0 = endian.read<unsigned int>(stream);
				unsigned short alphaBlending1 = endian.read<unsigned short>(stream);

				unsigned long long alphaBlending = ((unsigned long long)alphaBlending1 << 32) | alphaBlending0;

				endian.read<unsigned short>(stream); // color0
				endian.read<unsigned short>(stream); // color1

				endian.read<unsigned int>(stream); // blending


				for (size_t j = 0; j < 4; ++j)
				{
					for (size_t i = 0; i < 4; ++i)
					{
						if (x + i >= dimensions.width || y + j >= dimensions.height) continue;

						unsigned int alpha = (unsigned int)(alphaBlending >> (3 * (4 * j + i))) & 0x7;

						if (alpha == 0)
							alpha = alpha0;
						else if (alpha == 1)
							alpha = alpha1;
						else if (alpha0 > alpha1)
							alpha = ((8 - alpha) * alpha0 + (alpha - 1) * alpha1) / 7;
						else if (alpha == 6)
							alpha = 0;
						else if (alpha == 7)
							alpha = 255;
						else
							alpha = (((6 - alpha) * alpha0 + (alpha - 1) * alpha1) / 5);

						hasTransparency |= alpha != 0xFF;
						hasInvisibility |= alpha == 0;

						if (hasInvisibility)
							return;
					}
				}
			}
		}
	}

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

		VkFormat format = VK_FORMAT_UNDEFINED;

		int formatType = -1;

		if (formatName == std::string("DXT1", 4))
		{
			BlockSize = 8;
			format = VkFormat::VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
			formatType = 0;
		}
		else if (formatName == std::string("DXT3", 4))
		{
			format = VkFormat::VK_FORMAT_BC2_UNORM_BLOCK;
			formatType = 1;
		}
		else if (formatName == std::string("DXT5", 4))
		{
			format = VkFormat::VK_FORMAT_BC3_UNORM_BLOCK;
			formatType = 2;
		}
		else
		{
			std::cout << ("unsupported DDS: '" + asset.Entry->RelativePath.string() + "': ") << formatName << std::endl;

			return false;
		}

		VkDeviceSize bufferSize = size;//static_cast<uint64_t>(texWidth) * texHeight * sizeof(uint8_t) * 4;
		auto         imgSize = VkExtent2D{ (uint32_t)ddsHeader->dwWidth, (uint32_t)ddsHeader->dwHeight };
		auto         imageCreateInfo = nvvk::makeImage2DCreateInfo(imgSize, format, VK_IMAGE_USAGE_SAMPLED_BIT, mipLevels);

		switch (formatType)
		{
		case 0:
			CheckTransparencyDxt1(bufferData, size, imageCreateInfo.extent, asset.HasTransparency, asset.HasInvisibility);
			break;
		case 1:
			CheckTransparencyDxt3(bufferData, size, imageCreateInfo.extent, asset.HasTransparency, asset.HasInvisibility);
			break;
		case 2:
			CheckTransparencyDxt5(bufferData, size, imageCreateInfo.extent, asset.HasTransparency, asset.HasInvisibility);
			break;
		}

		{
			nvvk::Image image = AssetLibrary.GetVulkanContext()->Allocator.createImageDDS(cmdBuf, bufferSize, bufferData, imageCreateInfo, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, BlockSize);
			VkImageViewCreateInfo ivInfo = nvvk::makeImageViewCreateInfo(image.image, imageCreateInfo);
			asset.Data = AssetLibrary.GetVulkanContext()->Allocator.createTexture(image, ivInfo, asset.SamplerInfo);
		}

		return true;
	}
}