#include "VulkanAttributes.h"

#include <string>
#include <unordered_map>

namespace Graphics
{
	const FormatStats Formats[Enum::AttributeDataType::Count][4] = {
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R32G32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R32G32B32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R32G32B32A32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float64, 1, VK_FORMAT_R64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, "double" },
			{ Enum::AttributeDataType::Float64, 2, VK_FORMAT_R64G64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, "dvec2" },
			{ Enum::AttributeDataType::Float64, 3, VK_FORMAT_R64G64B64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, "dvec3" },
			{ Enum::AttributeDataType::Float64, 4, VK_FORMAT_R64G64B64A64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, "dvec4" }
		},
		{
			{ Enum::AttributeDataType::Bool, 1, VK_FORMAT_R8_UINT, spirv_cross::SPIRType::BaseType::Boolean, "bool" },
			{ Enum::AttributeDataType::Bool, 2, VK_FORMAT_R8G8_UINT, spirv_cross::SPIRType::BaseType::Boolean, "bvec2" },
			{ Enum::AttributeDataType::Bool, 3, VK_FORMAT_R8G8B8_UINT, spirv_cross::SPIRType::BaseType::Boolean, "bvec3" },
			{ Enum::AttributeDataType::Bool, 4, VK_FORMAT_R8G8B8A8_UINT, spirv_cross::SPIRType::BaseType::Boolean, "bvec4" }
		},
		{
			{ Enum::AttributeDataType::Int8, 1, VK_FORMAT_R8_SINT, spirv_cross::SPIRType::BaseType::SByte, "int8_t" },
			{ Enum::AttributeDataType::Int8, 2, VK_FORMAT_R8G8_SINT, spirv_cross::SPIRType::BaseType::SByte, "i8vec2" },
			{ Enum::AttributeDataType::Int8, 3, VK_FORMAT_R8G8B8_SINT, spirv_cross::SPIRType::BaseType::SByte, "i8vec3" },
			{ Enum::AttributeDataType::Int8, 4, VK_FORMAT_R8G8B8A8_SINT, spirv_cross::SPIRType::BaseType::SByte, "i8vec4" }
		},
		{
			{ Enum::AttributeDataType::Int16, 1, VK_FORMAT_R16_SINT, spirv_cross::SPIRType::BaseType::Short, "int16_t" },
			{ Enum::AttributeDataType::Int16, 2, VK_FORMAT_R16G16_SINT, spirv_cross::SPIRType::BaseType::Short, "i16vec2" },
			{ Enum::AttributeDataType::Int16, 3, VK_FORMAT_R16G16B16_SINT, spirv_cross::SPIRType::BaseType::Short, "i16vec3" },
			{ Enum::AttributeDataType::Int16, 4, VK_FORMAT_R16G16B16A16_SINT, spirv_cross::SPIRType::BaseType::Short, "i16vec4" }
		},
		{
			{ Enum::AttributeDataType::Int32, 1, VK_FORMAT_R32_SINT, spirv_cross::SPIRType::BaseType::Int, "int32_t" },
			{ Enum::AttributeDataType::Int32, 2, VK_FORMAT_R32G32_SINT, spirv_cross::SPIRType::BaseType::Int, "i32vec2" },
			{ Enum::AttributeDataType::Int32, 3, VK_FORMAT_R32G32B32_SINT, spirv_cross::SPIRType::BaseType::Int, "i32vec3" },
			{ Enum::AttributeDataType::Int32, 4, VK_FORMAT_R32G32B32A32_SINT, spirv_cross::SPIRType::BaseType::Int, "i32vec4" }
		},
		{
			{ Enum::AttributeDataType::Int64, 1, VK_FORMAT_R64_SINT, spirv_cross::SPIRType::BaseType::Int64, "int64_t" },
			{ Enum::AttributeDataType::Int64, 2, VK_FORMAT_R64G64_SINT, spirv_cross::SPIRType::BaseType::Int64, "i64vec2" },
			{ Enum::AttributeDataType::Int64, 3, VK_FORMAT_R64G64B64_SINT, spirv_cross::SPIRType::BaseType::Int64, "i64vec3" },
			{ Enum::AttributeDataType::Int64, 4, VK_FORMAT_R64G64B64A64_SINT, spirv_cross::SPIRType::BaseType::Int64, "i64vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt8, 1, VK_FORMAT_R8_UINT, spirv_cross::SPIRType::BaseType::UByte, "uint8_t" },
			{ Enum::AttributeDataType::UInt8, 2, VK_FORMAT_R8G8_UINT, spirv_cross::SPIRType::BaseType::UByte, "u8vec2" },
			{ Enum::AttributeDataType::UInt8, 3, VK_FORMAT_R8G8B8_UINT, spirv_cross::SPIRType::BaseType::UByte, "u8vec3" },
			{ Enum::AttributeDataType::UInt8, 4, VK_FORMAT_R8G8B8A8_UINT, spirv_cross::SPIRType::BaseType::UByte, "u8vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt16, 1, VK_FORMAT_R16_UINT, spirv_cross::SPIRType::BaseType::UShort, "uint16_t" },
			{ Enum::AttributeDataType::UInt16, 2, VK_FORMAT_R16G16_UINT, spirv_cross::SPIRType::BaseType::UShort, "u16vec2" },
			{ Enum::AttributeDataType::UInt16, 3, VK_FORMAT_R16G16B16_UINT, spirv_cross::SPIRType::BaseType::UShort, "u16vec3" },
			{ Enum::AttributeDataType::UInt16, 4, VK_FORMAT_R16G16B16A16_UINT, spirv_cross::SPIRType::BaseType::UShort, "u16vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt32, 1, VK_FORMAT_R32_UINT, spirv_cross::SPIRType::BaseType::UInt, "uint32_t" },
			{ Enum::AttributeDataType::UInt32, 2, VK_FORMAT_R32G32_UINT, spirv_cross::SPIRType::BaseType::UInt, "u32vec2" },
			{ Enum::AttributeDataType::UInt32, 3, VK_FORMAT_R32G32B32_UINT, spirv_cross::SPIRType::BaseType::UInt, "u32vec3" },
			{ Enum::AttributeDataType::UInt32, 4, VK_FORMAT_R32G32B32A32_UINT, spirv_cross::SPIRType::BaseType::UInt, "u32vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt64, 1, VK_FORMAT_R64_SINT, spirv_cross::SPIRType::BaseType::UInt64, "uint64_t" },
			{ Enum::AttributeDataType::UInt64, 2, VK_FORMAT_R64G64_UINT, spirv_cross::SPIRType::BaseType::UInt64, "u64vec2" },
			{ Enum::AttributeDataType::UInt64, 3, VK_FORMAT_R64G64B64_UINT, spirv_cross::SPIRType::BaseType::UInt64, "u64vec3" },
			{ Enum::AttributeDataType::UInt64, 4, VK_FORMAT_R64G64B64A64_UINT, spirv_cross::SPIRType::BaseType::UInt64, "u64vec4" }
		}
	};

	const FormatStats BadFormat = { Enum::AttributeDataType::Unknown, 0, VK_FORMAT_UNDEFINED, spirv_cross::SPIRType::BaseType::Unknown, "unknown" };

	const std::unordered_map<VkFormat, FormatStats const*> VulkanFormatMap = {
		{ VK_FORMAT_R32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][1] },
		{ VK_FORMAT_R32G32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][2] },
		{ VK_FORMAT_R32G32B32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][3] },
		{ VK_FORMAT_R32G32B32A32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][4] },
		{ VK_FORMAT_R64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][1] },
		{ VK_FORMAT_R64G64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][2] },
		{ VK_FORMAT_R64G64B64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][3] },
		{ VK_FORMAT_R64G64B64A64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][4] },
		{ VK_FORMAT_R8_UINT, &Formats[Enum::AttributeDataType::Bool][1] },
		{ VK_FORMAT_R8G8_UINT, &Formats[Enum::AttributeDataType::Bool][2] },
		{ VK_FORMAT_R8G8B8_UINT, &Formats[Enum::AttributeDataType::Bool][3] },
		{ VK_FORMAT_R8G8B8A8_UINT, &Formats[Enum::AttributeDataType::Bool][4] },
		{ VK_FORMAT_R8_SINT, &Formats[Enum::AttributeDataType::Int8][1] },
		{ VK_FORMAT_R8G8_SINT, &Formats[Enum::AttributeDataType::Int8][2] },
		{ VK_FORMAT_R8G8B8_SINT, &Formats[Enum::AttributeDataType::Int8][3] },
		{ VK_FORMAT_R8G8B8A8_SINT, &Formats[Enum::AttributeDataType::Int8][4] },
		{ VK_FORMAT_R16_SINT, &Formats[Enum::AttributeDataType::Int16][1] },
		{ VK_FORMAT_R16G16_SINT, &Formats[Enum::AttributeDataType::Int16][2] },
		{ VK_FORMAT_R16G16B16_SINT, &Formats[Enum::AttributeDataType::Int16][3] },
		{ VK_FORMAT_R16G16B16A16_SINT, &Formats[Enum::AttributeDataType::Int16][4] },
		{ VK_FORMAT_R32_SINT, &Formats[Enum::AttributeDataType::Int32][1] },
		{ VK_FORMAT_R32G32_SINT, &Formats[Enum::AttributeDataType::Int32][2] },
		{ VK_FORMAT_R32G32B32_SINT, &Formats[Enum::AttributeDataType::Int32][3] },
		{ VK_FORMAT_R32G32B32A32_SINT, &Formats[Enum::AttributeDataType::Int32][4] },
		{ VK_FORMAT_R64_SINT, &Formats[Enum::AttributeDataType::Int64][1] },
		{ VK_FORMAT_R64G64_SINT, &Formats[Enum::AttributeDataType::Int64][2] },
		{ VK_FORMAT_R64G64B64_SINT, &Formats[Enum::AttributeDataType::Int64][3] },
		{ VK_FORMAT_R64G64B64A64_SINT, &Formats[Enum::AttributeDataType::Int64][4] },
		{ VK_FORMAT_R8_UINT, &Formats[Enum::AttributeDataType::UInt8][1] },
		{ VK_FORMAT_R8G8_UINT, &Formats[Enum::AttributeDataType::UInt8][2] },
		{ VK_FORMAT_R8G8B8_UINT, &Formats[Enum::AttributeDataType::UInt8][3] },
		{ VK_FORMAT_R8G8B8A8_UINT, &Formats[Enum::AttributeDataType::UInt8][4] },
		{ VK_FORMAT_R16_UINT, &Formats[Enum::AttributeDataType::UInt16][1] },
		{ VK_FORMAT_R16G16_UINT, &Formats[Enum::AttributeDataType::UInt16][2] },
		{ VK_FORMAT_R16G16B16_UINT, &Formats[Enum::AttributeDataType::UInt16][3] },
		{ VK_FORMAT_R16G16B16A16_UINT, &Formats[Enum::AttributeDataType::UInt16][4] },
		{ VK_FORMAT_R32_UINT, &Formats[Enum::AttributeDataType::UInt32][1] },
		{ VK_FORMAT_R32G32_UINT, &Formats[Enum::AttributeDataType::UInt32][2] },
		{ VK_FORMAT_R32G32B32_UINT, &Formats[Enum::AttributeDataType::UInt32][3] },
		{ VK_FORMAT_R32G32B32A32_UINT, &Formats[Enum::AttributeDataType::UInt32][4] },
		{ VK_FORMAT_R64_SINT, &Formats[Enum::AttributeDataType::UInt64][1] },
		{ VK_FORMAT_R64G64_UINT, &Formats[Enum::AttributeDataType::UInt64][2] },
		{ VK_FORMAT_R64G64B64_UINT, &Formats[Enum::AttributeDataType::UInt64][3] },
		{ VK_FORMAT_R64G64B64A64_UINT, &Formats[Enum::AttributeDataType::UInt64][4] }
	};

	VkFormat GetVulkanFormat(Enum::AttributeDataType type, size_t elementCount)
	{
		return Formats[type][elementCount - 1].Format;
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
		return Formats[type][elementCount - 1].Name;
	}

	const std::string& GetFormatName(spirv_cross::SPIRType::BaseType type, size_t elementCount)
	{
		return GetFormatName(VulkanAttributeFormats[type], elementCount);
	}

	const FormatStats& GetFormatStats(Enum::AttributeDataType type, size_t elementCount)
	{
		return Formats[type][elementCount - 1];
	}

	const FormatStats& GetFormatStats(spirv_cross::SPIRType::BaseType type, size_t elementCount)
	{
		return Formats[VulkanAttributeFormats[type]][elementCount - 1];
	}

	const FormatStats& GetFormatStats(VkFormat format)
	{
		const auto& index = VulkanFormatMap.find(format);

		if (index != VulkanFormatMap.end())
			return *index->second;

		return BadFormat;
	}

	const std::unordered_map<VkFormat, DepthStencilFormatStats> VulkanDepthStencilFormatMap = {
		{ VK_FORMAT_D16_UNORM,
			{
				true,
				false,
				Enum::AttributeDataType::UInt16,
				Enum::AttributeDataType::Unknown,
				spirv_cross::SPIRType::BaseType::UShort,
				spirv_cross::SPIRType::BaseType::Unknown
			}
		},
		{ VK_FORMAT_X8_D24_UNORM_PACK32,
			{
				true,
				false,
				Enum::AttributeDataType::UInt24,
				Enum::AttributeDataType::Unknown,
				spirv_cross::SPIRType::BaseType::UInt,
				spirv_cross::SPIRType::BaseType::Unknown
			}
		},
		{ VK_FORMAT_D32_SFLOAT,
			{
				true,
				false,
				Enum::AttributeDataType::UInt32,
				Enum::AttributeDataType::Unknown,
				spirv_cross::SPIRType::BaseType::UInt,
				spirv_cross::SPIRType::BaseType::Unknown
			}
		},
		{ VK_FORMAT_S8_UINT,
			{
				false,
				true,
				Enum::AttributeDataType::Unknown,
				Enum::AttributeDataType::UInt8,
				spirv_cross::SPIRType::BaseType::Unknown,
				spirv_cross::SPIRType::BaseType::UByte
			}
		},
		{ VK_FORMAT_D16_UNORM_S8_UINT,
			{
				true,
				true,
				Enum::AttributeDataType::UInt16,
				Enum::AttributeDataType::UInt8,
				spirv_cross::SPIRType::BaseType::UShort,
				spirv_cross::SPIRType::BaseType::UByte
			}
		},
		{ VK_FORMAT_D24_UNORM_S8_UINT,
			{
				true,
				true,
				Enum::AttributeDataType::UInt24,
				Enum::AttributeDataType::UInt8,
				spirv_cross::SPIRType::BaseType::UInt,
				spirv_cross::SPIRType::BaseType::UByte
			}
		},
		{ VK_FORMAT_D32_SFLOAT_S8_UINT,
			{
				true,
				true,
				Enum::AttributeDataType::UInt32,
				Enum::AttributeDataType::UInt8,
				spirv_cross::SPIRType::BaseType::UInt,
				spirv_cross::SPIRType::BaseType::UByte
			}
		}
	};

	const DepthStencilFormatStats& GetDepthStencilStats(VkFormat format)
	{
		const auto& index = VulkanDepthStencilFormatMap.find(format);

		if (index != VulkanDepthStencilFormatMap.end())
			return index->second;

		static const DepthStencilFormatStats badFormat;

		return badFormat;
	}
}