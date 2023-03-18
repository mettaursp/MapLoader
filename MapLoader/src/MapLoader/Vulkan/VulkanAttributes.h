#pragma once

#include <Engine/VulkanGraphics/Core/BufferFormat.h>
#include <vulkan/vulkan_core.h>
#include <spirv_cross/spirv_common.hpp>

namespace Graphics
{
	VkFormat GetVulkanFormat(Enum::AttributeDataType type, size_t elementCount);
	VkFormat GetVulkanFormat(spirv_cross::SPIRType::BaseType type, size_t elementCount);
	const std::string& GetFormatName(Enum::AttributeDataType type, size_t elementCount);
	const std::string& GetFormatName(spirv_cross::SPIRType::BaseType type, size_t elementCount);
}