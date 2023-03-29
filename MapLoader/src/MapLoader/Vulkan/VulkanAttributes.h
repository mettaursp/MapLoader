#pragma once

#include <Engine/VulkanGraphics/Core/BufferFormat.h>
#include <vulkan/vulkan_core.h>
#include <spirv_cross/spirv_common.hpp>

namespace Graphics
{
	struct FormatStats
	{
		Enum::AttributeDataType DataType = Enum::AttributeDataType::Unknown;
		size_t ElementCount;
		VkFormat Format = VK_FORMAT_UNDEFINED;
		spirv_cross::SPIRType::BaseType BaseType = spirv_cross::SPIRType::BaseType::Unknown;
		std::string Name;
	};

	struct DepthStencilFormatStats
	{
		bool DepthEnabled = false;
		bool StencilEnabled = false;
		Enum::AttributeDataType DepthDataType = Enum::AttributeDataType::Unknown;
		Enum::AttributeDataType StencilDataType = Enum::AttributeDataType::Unknown;
		spirv_cross::SPIRType::BaseType DepthBaseType = spirv_cross::SPIRType::BaseType::Unknown;
		spirv_cross::SPIRType::BaseType StencilBaseType = spirv_cross::SPIRType::BaseType::Unknown;
	};

	VkFormat GetVulkanFormat(Enum::AttributeDataType type, size_t elementCount);
	VkFormat GetVulkanFormat(spirv_cross::SPIRType::BaseType type, size_t elementCount);
	const std::string& GetFormatName(Enum::AttributeDataType type, size_t elementCount);
	const std::string& GetFormatName(spirv_cross::SPIRType::BaseType type, size_t elementCount);
	const FormatStats& GetFormatStats(Enum::AttributeDataType type, size_t elementCount);
	const FormatStats& GetFormatStats(spirv_cross::SPIRType::BaseType type, size_t elementCount);
	const FormatStats& GetFormatStats(VkFormat format);
	const DepthStencilFormatStats& GetDepthStencilStats(VkFormat format);
}