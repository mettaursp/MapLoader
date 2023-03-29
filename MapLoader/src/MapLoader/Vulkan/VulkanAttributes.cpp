#include "VulkanAttributes.h"

#include <string>
#include <unordered_map>

namespace Graphics
{
	struct AttributesEnum
	{
		enum Attributes
		{
			R,
			RG,
			RGB,
			RGBA,
			BGRA,

			Count,
			Unknown
		};
	};

	typedef AttributesEnum::Attributes Attributes;

	struct SpecialAttributeTypesEnum
	{
		enum SpecialAttributeTypes
		{
			UnsignedNormalized8,
			SignedNormalized8,
			UnsignedScaled8,
			SignedScaled8,
			UnsignedNormalized16,
			SignedNormalized16,
			UnsignedScaled16,
			SignedScaled16,
			SRGB8,

			Count
		};
	};

	typedef SpecialAttributeTypesEnum::SpecialAttributeTypes SpecialAttributeTypes;

	const VkColorComponentFlags AttributeFlags[Attributes::Count] = {
		VK_COLOR_COMPONENT_R_BIT,
		VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT,
		VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT,
		VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
		VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
	};

	const FormatStats Formats[Enum::AttributeDataType::Count][Attributes::Count] = {
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R32G32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R32G32B32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R32G32B32A32_SFLOAT, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float64, 1, VK_FORMAT_R64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, AttributeFlags[Attributes::R], "double" },
			{ Enum::AttributeDataType::Float64, 2, VK_FORMAT_R64G64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, AttributeFlags[Attributes::RG], "dvec2" },
			{ Enum::AttributeDataType::Float64, 3, VK_FORMAT_R64G64B64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, AttributeFlags[Attributes::RGB], "dvec3" },
			{ Enum::AttributeDataType::Float64, 4, VK_FORMAT_R64G64B64A64_SFLOAT, spirv_cross::SPIRType::BaseType::Double, AttributeFlags[Attributes::RGBA], "dvec4" }
		},
		{
			{ Enum::AttributeDataType::Bool, 1, VK_FORMAT_R8_UINT, spirv_cross::SPIRType::BaseType::Boolean, AttributeFlags[Attributes::R], "bool" },
			{ Enum::AttributeDataType::Bool, 2, VK_FORMAT_R8G8_UINT, spirv_cross::SPIRType::BaseType::Boolean, AttributeFlags[Attributes::RG], "bvec2" },
			{ Enum::AttributeDataType::Bool, 3, VK_FORMAT_R8G8B8_UINT, spirv_cross::SPIRType::BaseType::Boolean, AttributeFlags[Attributes::RGB], "bvec3" },
			{ Enum::AttributeDataType::Bool, 4, VK_FORMAT_R8G8B8A8_UINT, spirv_cross::SPIRType::BaseType::Boolean, AttributeFlags[Attributes::RGBA], "bvec4" }
		},
		{
			{ Enum::AttributeDataType::Int8, 1, VK_FORMAT_R8_SINT, spirv_cross::SPIRType::BaseType::SByte, AttributeFlags[Attributes::R], "int8_t" },
			{ Enum::AttributeDataType::Int8, 2, VK_FORMAT_R8G8_SINT, spirv_cross::SPIRType::BaseType::SByte, AttributeFlags[Attributes::RG], "i8vec2" },
			{ Enum::AttributeDataType::Int8, 3, VK_FORMAT_R8G8B8_SINT, spirv_cross::SPIRType::BaseType::SByte, AttributeFlags[Attributes::RGB], "i8vec3" },
			{ Enum::AttributeDataType::Int8, 4, VK_FORMAT_R8G8B8A8_SINT, spirv_cross::SPIRType::BaseType::SByte, AttributeFlags[Attributes::RGBA], "i8vec4" },
			{ Enum::AttributeDataType::Int8, 4, VK_FORMAT_B8G8R8A8_SINT, spirv_cross::SPIRType::BaseType::SByte, AttributeFlags[Attributes::RGBA], "i8vec4" }
		},
		{
			{ Enum::AttributeDataType::Int16, 1, VK_FORMAT_R16_SINT, spirv_cross::SPIRType::BaseType::Short, AttributeFlags[Attributes::R], "int16_t" },
			{ Enum::AttributeDataType::Int16, 2, VK_FORMAT_R16G16_SINT, spirv_cross::SPIRType::BaseType::Short, AttributeFlags[Attributes::RG], "i16vec2" },
			{ Enum::AttributeDataType::Int16, 3, VK_FORMAT_R16G16B16_SINT, spirv_cross::SPIRType::BaseType::Short, AttributeFlags[Attributes::RGB], "i16vec3" },
			{ Enum::AttributeDataType::Int16, 4, VK_FORMAT_R16G16B16A16_SINT, spirv_cross::SPIRType::BaseType::Short, AttributeFlags[Attributes::RGBA], "i16vec4" }
		},
		{
			{ Enum::AttributeDataType::Int32, 1, VK_FORMAT_R32_SINT, spirv_cross::SPIRType::BaseType::Int, AttributeFlags[Attributes::R], "int32_t" },
			{ Enum::AttributeDataType::Int32, 2, VK_FORMAT_R32G32_SINT, spirv_cross::SPIRType::BaseType::Int, AttributeFlags[Attributes::RG], "i32vec2" },
			{ Enum::AttributeDataType::Int32, 3, VK_FORMAT_R32G32B32_SINT, spirv_cross::SPIRType::BaseType::Int, AttributeFlags[Attributes::RGB], "i32vec3" },
			{ Enum::AttributeDataType::Int32, 4, VK_FORMAT_R32G32B32A32_SINT, spirv_cross::SPIRType::BaseType::Int, AttributeFlags[Attributes::RGBA], "i32vec4" }
		},
		{
			{ Enum::AttributeDataType::Int64, 1, VK_FORMAT_R64_SINT, spirv_cross::SPIRType::BaseType::Int64, AttributeFlags[Attributes::R], "int64_t" },
			{ Enum::AttributeDataType::Int64, 2, VK_FORMAT_R64G64_SINT, spirv_cross::SPIRType::BaseType::Int64, AttributeFlags[Attributes::RG], "i64vec2" },
			{ Enum::AttributeDataType::Int64, 3, VK_FORMAT_R64G64B64_SINT, spirv_cross::SPIRType::BaseType::Int64, AttributeFlags[Attributes::RGB], "i64vec3" },
			{ Enum::AttributeDataType::Int64, 4, VK_FORMAT_R64G64B64A64_SINT, spirv_cross::SPIRType::BaseType::Int64, AttributeFlags[Attributes::RGBA], "i64vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt8, 1, VK_FORMAT_R8_UINT, spirv_cross::SPIRType::BaseType::UByte, AttributeFlags[Attributes::R], "uint8_t" },
			{ Enum::AttributeDataType::UInt8, 2, VK_FORMAT_R8G8_UINT, spirv_cross::SPIRType::BaseType::UByte, AttributeFlags[Attributes::RG], "u8vec2" },
			{ Enum::AttributeDataType::UInt8, 3, VK_FORMAT_R8G8B8_UINT, spirv_cross::SPIRType::BaseType::UByte, AttributeFlags[Attributes::RGB], "u8vec3" },
			{ Enum::AttributeDataType::UInt8, 4, VK_FORMAT_R8G8B8A8_UINT, spirv_cross::SPIRType::BaseType::UByte, AttributeFlags[Attributes::RGBA], "u8vec4" },
			{ Enum::AttributeDataType::UInt8, 4, VK_FORMAT_B8G8R8A8_UINT, spirv_cross::SPIRType::BaseType::UByte, AttributeFlags[Attributes::RGBA], "u8vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt16, 1, VK_FORMAT_R16_UINT, spirv_cross::SPIRType::BaseType::UShort, AttributeFlags[Attributes::R], "uint16_t" },
			{ Enum::AttributeDataType::UInt16, 2, VK_FORMAT_R16G16_UINT, spirv_cross::SPIRType::BaseType::UShort, AttributeFlags[Attributes::RG], "u16vec2" },
			{ Enum::AttributeDataType::UInt16, 3, VK_FORMAT_R16G16B16_UINT, spirv_cross::SPIRType::BaseType::UShort, AttributeFlags[Attributes::RGB], "u16vec3" },
			{ Enum::AttributeDataType::UInt16, 4, VK_FORMAT_R16G16B16A16_UINT, spirv_cross::SPIRType::BaseType::UShort, AttributeFlags[Attributes::RGBA], "u16vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt32, 1, VK_FORMAT_R32_UINT, spirv_cross::SPIRType::BaseType::UInt, AttributeFlags[Attributes::R], "uint32_t" },
			{ Enum::AttributeDataType::UInt32, 2, VK_FORMAT_R32G32_UINT, spirv_cross::SPIRType::BaseType::UInt, AttributeFlags[Attributes::RG], "u32vec2" },
			{ Enum::AttributeDataType::UInt32, 3, VK_FORMAT_R32G32B32_UINT, spirv_cross::SPIRType::BaseType::UInt, AttributeFlags[Attributes::RGB], "u32vec3" },
			{ Enum::AttributeDataType::UInt32, 4, VK_FORMAT_R32G32B32A32_UINT, spirv_cross::SPIRType::BaseType::UInt, AttributeFlags[Attributes::RGBA], "u32vec4" }
		},
		{
			{ Enum::AttributeDataType::UInt64, 1, VK_FORMAT_R64_SINT, spirv_cross::SPIRType::BaseType::UInt64, AttributeFlags[Attributes::R], "uint64_t" },
			{ Enum::AttributeDataType::UInt64, 2, VK_FORMAT_R64G64_UINT, spirv_cross::SPIRType::BaseType::UInt64, AttributeFlags[Attributes::RG], "u64vec2" },
			{ Enum::AttributeDataType::UInt64, 3, VK_FORMAT_R64G64B64_UINT, spirv_cross::SPIRType::BaseType::UInt64, AttributeFlags[Attributes::RGB], "u64vec3" },
			{ Enum::AttributeDataType::UInt64, 4, VK_FORMAT_R64G64B64A64_UINT, spirv_cross::SPIRType::BaseType::UInt64, AttributeFlags[Attributes::RGBA], "u64vec4" }
		}
	};

	const FormatStats SpecialFormats[SpecialAttributeTypes::Count][Attributes::Count] = {
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R8_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R8G8_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R8G8B8_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R8G8B8A8_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_B8G8R8A8_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R8_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R8G8_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R8G8B8_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R8G8B8A8_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_B8G8R8A8_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R8_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R8G8_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R8G8B8_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R8G8B8A8_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_B8G8R8A8_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R8_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R8G8_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R8G8B8_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R8G8B8A8_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_B8G8R8A8_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R16_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R16G16_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R16G16B16_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R16G16B16A16_UNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R16_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R16G16_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R16G16B16_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R16G16B16A16_SNORM, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" },
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R16_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R16G16_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R16G16B16_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R16G16B16A16_USCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R16_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R16G16_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R16G16B16_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R16G16B16A16_SSCALED, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		},
		{
			{ Enum::AttributeDataType::Float32, 1, VK_FORMAT_R8_SRGB, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::R], "float" },
			{ Enum::AttributeDataType::Float32, 2, VK_FORMAT_R8G8_SRGB, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RG], "vec2" },
			{ Enum::AttributeDataType::Float32, 3, VK_FORMAT_R8G8B8_SRGB, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGB], "vec3" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_R8G8B8A8_SRGB, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" },
			{ Enum::AttributeDataType::Float32, 4, VK_FORMAT_B8G8R8A8_SRGB, spirv_cross::SPIRType::BaseType::Float, AttributeFlags[Attributes::RGBA], "vec4" }
		}
	};

	const FormatStats BadFormat = {};

	const std::unordered_map<VkFormat, FormatStats const*> VulkanFormatMap = {
		{ VK_FORMAT_R32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][0] },
		{ VK_FORMAT_R32G32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][1] },
		{ VK_FORMAT_R32G32B32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][2] },
		{ VK_FORMAT_R32G32B32A32_SFLOAT, &Formats[Enum::AttributeDataType::Float32][3] },
		{ VK_FORMAT_R64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][0] },
		{ VK_FORMAT_R64G64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][1] },
		{ VK_FORMAT_R64G64B64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][2] },
		{ VK_FORMAT_R64G64B64A64_SFLOAT, &Formats[Enum::AttributeDataType::Float64][3] },
		{ VK_FORMAT_R8_SINT, &Formats[Enum::AttributeDataType::Int8][0] },
		{ VK_FORMAT_R8G8_SINT, &Formats[Enum::AttributeDataType::Int8][1] },
		{ VK_FORMAT_R8G8B8_SINT, &Formats[Enum::AttributeDataType::Int8][2] },
		{ VK_FORMAT_R8G8B8A8_SINT, &Formats[Enum::AttributeDataType::Int8][3] },
		{ VK_FORMAT_B8G8R8A8_SINT, &Formats[Enum::AttributeDataType::Int8][4] },
		{ VK_FORMAT_R16_SINT, &Formats[Enum::AttributeDataType::Int16][0] },
		{ VK_FORMAT_R16G16_SINT, &Formats[Enum::AttributeDataType::Int16][1] },
		{ VK_FORMAT_R16G16B16_SINT, &Formats[Enum::AttributeDataType::Int16][2] },
		{ VK_FORMAT_R16G16B16A16_SINT, &Formats[Enum::AttributeDataType::Int16][3] },
		{ VK_FORMAT_R32_SINT, &Formats[Enum::AttributeDataType::Int32][0] },
		{ VK_FORMAT_R32G32_SINT, &Formats[Enum::AttributeDataType::Int32][1] },
		{ VK_FORMAT_R32G32B32_SINT, &Formats[Enum::AttributeDataType::Int32][2] },
		{ VK_FORMAT_R32G32B32A32_SINT, &Formats[Enum::AttributeDataType::Int32][3] },
		{ VK_FORMAT_R64_SINT, &Formats[Enum::AttributeDataType::Int64][0] },
		{ VK_FORMAT_R64G64_SINT, &Formats[Enum::AttributeDataType::Int64][1] },
		{ VK_FORMAT_R64G64B64_SINT, &Formats[Enum::AttributeDataType::Int64][2] },
		{ VK_FORMAT_R64G64B64A64_SINT, &Formats[Enum::AttributeDataType::Int64][3] },
		{ VK_FORMAT_R8_UINT, &Formats[Enum::AttributeDataType::UInt8][0] },
		{ VK_FORMAT_R8G8_UINT, &Formats[Enum::AttributeDataType::UInt8][1] },
		{ VK_FORMAT_R8G8B8_UINT, &Formats[Enum::AttributeDataType::UInt8][2] },
		{ VK_FORMAT_R8G8B8A8_UINT, &Formats[Enum::AttributeDataType::UInt8][3] },
		{ VK_FORMAT_B8G8R8A8_UINT, &Formats[Enum::AttributeDataType::UInt8][4] },
		{ VK_FORMAT_R16_UINT, &Formats[Enum::AttributeDataType::UInt16][0] },
		{ VK_FORMAT_R16G16_UINT, &Formats[Enum::AttributeDataType::UInt16][1] },
		{ VK_FORMAT_R16G16B16_UINT, &Formats[Enum::AttributeDataType::UInt16][2] },
		{ VK_FORMAT_R16G16B16A16_UINT, &Formats[Enum::AttributeDataType::UInt16][3] },
		{ VK_FORMAT_R32_UINT, &Formats[Enum::AttributeDataType::UInt32][0] },
		{ VK_FORMAT_R32G32_UINT, &Formats[Enum::AttributeDataType::UInt32][1] },
		{ VK_FORMAT_R32G32B32_UINT, &Formats[Enum::AttributeDataType::UInt32][2] },
		{ VK_FORMAT_R32G32B32A32_UINT, &Formats[Enum::AttributeDataType::UInt32][3] },
		{ VK_FORMAT_R64_SINT, &Formats[Enum::AttributeDataType::UInt64][0] },
		{ VK_FORMAT_R64G64_UINT, &Formats[Enum::AttributeDataType::UInt64][1] },
		{ VK_FORMAT_R64G64B64_UINT, &Formats[Enum::AttributeDataType::UInt64][2] },
		{ VK_FORMAT_R64G64B64A64_UINT, &Formats[Enum::AttributeDataType::UInt64][3] },
		{ VK_FORMAT_R8_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized8][0] },
		{ VK_FORMAT_R8G8_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized8][1] },
		{ VK_FORMAT_R8G8B8_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized8][2] },
		{ VK_FORMAT_R8G8B8A8_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized8][3] },
		{ VK_FORMAT_B8G8R8A8_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized8][4] },
		{ VK_FORMAT_R8_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized8][0] },
		{ VK_FORMAT_R8G8_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized8][1] },
		{ VK_FORMAT_R8G8B8_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized8][2] },
		{ VK_FORMAT_R8G8B8A8_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized8][3] },
		{ VK_FORMAT_B8G8R8A8_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized8][4] },
		{ VK_FORMAT_R8_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled8][0] },
		{ VK_FORMAT_R8G8_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled8][1] },
		{ VK_FORMAT_R8G8B8_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled8][2] },
		{ VK_FORMAT_R8G8B8A8_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled8][3] },
		{ VK_FORMAT_B8G8R8A8_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled8][4] },
		{ VK_FORMAT_R8_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled8][0] },
		{ VK_FORMAT_R8G8_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled8][1] },
		{ VK_FORMAT_R8G8B8_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled8][2] },
		{ VK_FORMAT_R8G8B8A8_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled8][3] },
		{ VK_FORMAT_B8G8R8A8_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled8][4] },
		{ VK_FORMAT_R16_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized16][0] },
		{ VK_FORMAT_R16G16_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized16][1] },
		{ VK_FORMAT_R16G16B16_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized16][2] },
		{ VK_FORMAT_R16G16B16A16_UNORM, &SpecialFormats[SpecialAttributeTypes::UnsignedNormalized16][3] },
		{ VK_FORMAT_R16_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized16][0] },
		{ VK_FORMAT_R16G16_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized16][1] },
		{ VK_FORMAT_R16G16B16_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized16][2] },
		{ VK_FORMAT_R16G16B16A16_SNORM, &SpecialFormats[SpecialAttributeTypes::SignedNormalized16][3] },
		{ VK_FORMAT_R16_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled16][0] },
		{ VK_FORMAT_R16G16_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled16][1] },
		{ VK_FORMAT_R16G16B16_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled16][2] },
		{ VK_FORMAT_R16G16B16A16_USCALED, &SpecialFormats[SpecialAttributeTypes::UnsignedScaled16][3] },
		{ VK_FORMAT_R16_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled16][0] },
		{ VK_FORMAT_R16G16_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled16][1] },
		{ VK_FORMAT_R16G16B16_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled16][2] },
		{ VK_FORMAT_R16G16B16A16_SSCALED, &SpecialFormats[SpecialAttributeTypes::SignedScaled16][3] },
		{ VK_FORMAT_R8_SRGB, &SpecialFormats[SpecialAttributeTypes::SRGB8][0] },
		{ VK_FORMAT_R8G8_SRGB, &SpecialFormats[SpecialAttributeTypes::SRGB8][1] },
		{ VK_FORMAT_R8G8B8_SRGB, &SpecialFormats[SpecialAttributeTypes::SRGB8][2] },
		{ VK_FORMAT_R8G8B8A8_SRGB, &SpecialFormats[SpecialAttributeTypes::SRGB8][3] },
		{ VK_FORMAT_B8G8R8A8_SRGB, &SpecialFormats[SpecialAttributeTypes::SRGB8][4] },
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