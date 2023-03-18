#include "VulkanAttributes.h"

#include <string>

namespace Graphics
{
	const VkFormat AttributeFormats[Enum::AttributeDataType::Count][4] = {
		/* Float32 */ { VK_FORMAT_R32_SFLOAT, VK_FORMAT_R32G32_SFLOAT, VK_FORMAT_R32G32B32_SFLOAT, VK_FORMAT_R32G32B32A32_SFLOAT },
		/* Float64 */ { VK_FORMAT_R64_SFLOAT, VK_FORMAT_R64G64_SFLOAT, VK_FORMAT_R64G64B64_SFLOAT, VK_FORMAT_R64G64B64A64_SFLOAT },
		/* Bool	   */ { VK_FORMAT_R8_UINT, VK_FORMAT_R8G8_UINT, VK_FORMAT_R8G8B8_UINT, VK_FORMAT_R8G8B8A8_UINT },
		/* Int8	   */ { VK_FORMAT_R8_SINT, VK_FORMAT_R8G8_SINT, VK_FORMAT_R8G8B8_SINT, VK_FORMAT_R8G8B8A8_SINT },
		/* Int16   */ { VK_FORMAT_R16_SINT, VK_FORMAT_R16G16_SINT, VK_FORMAT_R16G16B16_SINT, VK_FORMAT_R16G16B16A16_SINT },
		/* Int32   */ { VK_FORMAT_R32_SINT, VK_FORMAT_R32G32_SINT, VK_FORMAT_R32G32B32_SINT, VK_FORMAT_R32G32B32A32_SINT },
		/* Int64   */ { VK_FORMAT_R64_SINT, VK_FORMAT_R64G64_SINT, VK_FORMAT_R64G64B64_SINT, VK_FORMAT_R64G64B64A64_SINT },
		/* UInt8   */ { VK_FORMAT_R8_UINT, VK_FORMAT_R8G8_UINT, VK_FORMAT_R8G8B8_UINT, VK_FORMAT_R8G8B8A8_UINT },
		/* UInt16  */ { VK_FORMAT_R16_UINT, VK_FORMAT_R16G16_UINT, VK_FORMAT_R16G16B16_UINT, VK_FORMAT_R16G16B16A16_UINT },
		/* UInt32  */ { VK_FORMAT_R32_UINT, VK_FORMAT_R32G32_UINT, VK_FORMAT_R32G32B32_UINT, VK_FORMAT_R32G32B32A32_UINT },
		/* UInt64  */ { VK_FORMAT_R64_SINT, VK_FORMAT_R64G64_UINT, VK_FORMAT_R64G64B64_UINT, VK_FORMAT_R64G64B64A64_UINT }
	};

	const std::string AttributeFormatNames[Enum::AttributeDataType::Count][4] = {
		/* Float32 */ { "float", "vec2", "vec3", "vec4"},
		/* Float64 */ { "double", "dvec2", "dvec3", "dvec4"},
		/* Bool	   */ { "bool", "bvec2", "bvec3", "bvec4"},
		/* Int8	   */ { "int8_t", "i8vec2", "i8vec3", "i8vec4" },
		/* Int16   */ { "int16_t", "i16vec2", "i16vec3", "i16vec4" },
		/* Int32   */ { "int32_t", "i32vec2", "i32vec3", "i32vec4" },
		/* Int64   */ { "int64_t", "i64vec2", "i64vec3", "i64vec4" },
		/* UInt8   */ { "uint8_t", "u8vec2", "u8vec3", "u8vec4" },
		/* UInt16  */ { "uint16_t", "u16vec2", "u16vec3", "u16vec4" },
		/* UInt32  */ { "uint32_t", "u32vec2", "u32vec3", "u32vec4" },
		/* UInt64  */ { "uint64_t", "u64vec2", "u64vec3", "u64vec4" }
	};

	VkFormat GetVulkanFormat(Enum::AttributeDataType type, size_t elementCount)
	{
		return AttributeFormats[type][elementCount - 1];
	}

	const Enum::AttributeDataType VulkanAttributeFormats[21] = {
		/* Unknown,				  */ {},
		/* Void,				  */ {},
		/* Boolean,				  */ Enum::AttributeDataType::Bool,
		/* SByte,				  */ Enum::AttributeDataType::Int8,
		/* UByte,				  */ Enum::AttributeDataType::UInt8,
		/* Short,				  */ Enum::AttributeDataType::Int16,
		/* UShort,				  */ Enum::AttributeDataType::UInt16,
		/* Int,					  */ Enum::AttributeDataType::Int32,
		/* UInt,				  */ Enum::AttributeDataType::UInt32,
		/* Int64,				  */ Enum::AttributeDataType::Int64,
		/* UInt64,				  */ Enum::AttributeDataType::UInt64,
		/* AtomicCounter,		  */ {},
		/* Half,				  */ {},
		/* Float,				  */ Enum::AttributeDataType::Float32,
		/* Double,				  */ Enum::AttributeDataType::Float64,
		/* Struct,				  */ {},
		/* Image,				  */ {},
		/* SampledImage,		  */ {},
		/* Sampler,				  */ {},
		/* AccelerationStructure, */ {},
		/* RayQuery,			  */ {}
	};

	VkFormat GetVulkanFormat(spirv_cross::SPIRType::BaseType type, size_t elementCount)
	{
		return GetVulkanFormat(VulkanAttributeFormats[type], elementCount);
	}

	const std::string& GetFormatName(Enum::AttributeDataType type, size_t elementCount)
	{
		return AttributeFormatNames[type][elementCount - 1];
	}

	const std::string& GetFormatName(spirv_cross::SPIRType::BaseType type, size_t elementCount)
	{
		return GetFormatName(VulkanAttributeFormats[type], elementCount);
	}
}