#include "NifParser.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstring>

#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Vector2S.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Quaternion.h>
#include <Engine/Assets/ParserUtils.h>
#include <Engine/Objects/Transform.h>

#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include "NifComponentInfo.h"
#include "NifBlockTypes.h"

void NifDocument::ParseTransform(std::string_view& stream, NiTransform& transform, bool translationFirst, bool isQuaternion)
{
	if (translationFirst)
	{
		float x = Endian.read<float>(stream);
		float y = Endian.read<float>(stream);
		float z = Endian.read<float>(stream);

		transform.Translation = Vector3SF(z, y, x);
	}

	if (!isQuaternion)
	{
		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				transform.Rotation.Data[y][x] = Endian.read<float>(stream);
			}
		}
	}
	else
	{
		float x = Endian.read<float>(stream);
		float y = Endian.read<float>(stream);
		float z = Endian.read<float>(stream);
		float w = Endian.read<float>(stream);

		transform.Rotation = Quaternion(Vector3(x, y, z, w)).MatrixF();
	}

	if (!translationFirst)
	{
		float z = Endian.read<float>(stream);
		float y = Endian.read<float>(stream);
		float x = Endian.read<float>(stream);

		transform.Translation = Vector3SF(z, y, x);
	}

	std::swap(transform.Translation.X, transform.Translation.Z);

	transform.Scale = Endian.read<float>(stream);
}

void NifDocument::ParseBounds(std::string_view& stream, NiBounds& bounds)
{
	float z = Endian.read<float>(stream);
	float y = Endian.read<float>(stream);
	float x = Endian.read<float>(stream);

	bounds.Center = Vector3SF(x, y, z);
	bounds.Radius = Endian.read<float>(stream);

	std::swap(bounds.Center.X, bounds.Center.Z);
}

void NifDocument::ParseNode(std::string_view& stream, BlockData& block)
{
	NiNode* data = block.AddData<NiNode>();

	unsigned int numExtraData = Endian.read<unsigned int>(stream);

	data->ExtraData.resize(numExtraData);

	for (unsigned int i = 0; i < numExtraData; ++i)
		data->ExtraData[i] = &Blocks[Endian.read<unsigned int>(stream)];

	data->Controller = FetchRef(stream);
	data->Flags = Endian.read<unsigned short>(stream);
	
	ParseTransform(stream, data->Transformation);

	unsigned int numProperties = Endian.read<unsigned int>(stream);

	data->Properties.resize(numProperties);

	for (unsigned int i = 0; i < numProperties; ++i)
		data->Properties[i] = &Blocks[Endian.read<unsigned int>(stream)];

	data->CollisionObject = FetchRef(stream);

	unsigned int numChildren = Endian.read<unsigned int>(stream);

	data->Children.resize(numChildren);

	for (unsigned int i = 0; i < numChildren; ++i)
	{
		unsigned int childIndex = Endian.read<unsigned int>(stream);

		if (childIndex != (unsigned int)-1)
			data->Children[i] = &Blocks[childIndex];
	}

	unsigned int numEffects = Endian.read<unsigned int>(stream);

	data->Effects.resize(numEffects);

	for (unsigned int i = 0; i < numEffects; ++i)
		data->Effects[i] = &Blocks[Endian.read<unsigned int>(stream)];
}

void NifDocument::ParseMesh(std::string_view& stream, BlockData& block)
{
	NiMesh* data = block.AddData<NiMesh>();

	unsigned int numExtraData = Endian.read<unsigned int>(stream);

	data->ExtraData.resize(numExtraData);

	for (unsigned int i = 0; i < numExtraData; ++i)
		data->ExtraData[i] = &Blocks[Endian.read<unsigned int>(stream)];

	data->Controller = FetchRef(stream);
	data->Flags = Endian.read<unsigned short>(stream);

	ParseTransform(stream, data->Transformation);

	unsigned int numProperties = Endian.read<unsigned int>(stream);

	data->Properties.resize(numProperties);

	for (unsigned int i = 0; i < numProperties; ++i)
		data->Properties[i] = &Blocks[Endian.read<unsigned int>(stream)];

	data->CollisionObject = FetchRef(stream);

	unsigned int numMaterials = Endian.read<unsigned int>(stream);

	data->Materials.resize(numMaterials);
	data->MaterialExtraData.resize(numMaterials);

	for (unsigned int i = 0; i < numMaterials; ++i)
		data->Materials[i] = Strings[Endian.read<unsigned int>(stream)];

	for (unsigned int i = 0; i < numMaterials; ++i)
		data->MaterialExtraData[i] = FetchRef(stream);

	data->ActiveMaterial = Endian.read<unsigned int>(stream);
	data->MaterialNeedsUpdate = Endian.read<char>(stream);
	data->PrimitiveType = (MeshPrimitiveType)Endian.read<unsigned int>(stream);
	data->NumSubmeshes = Endian.read<unsigned short>(stream);
	data->InstancingEnabled = Endian.read<char>(stream);

	ParseBounds(stream, data->Bounds);

	unsigned int numDataStreams = Endian.read<unsigned int>(stream);

	data->Streams.resize(numDataStreams);

	for (unsigned int i = 0; i < numDataStreams; ++i)
	{
		data->Streams[i].Stream = FetchRef(stream);
		data->Streams[i].IsPerInstance = Endian.read<char>(stream);
		
		unsigned short numSubMeshes = Endian.read<unsigned short>(stream);

		data->Streams[i].SubmeshToRegionMap.resize(numSubMeshes);

		for (unsigned short j = 0; j < numSubMeshes; ++j)
			data->Streams[i].SubmeshToRegionMap[j] = Endian.read<unsigned short>(stream);

		unsigned int numSemantics = Endian.read<unsigned int>(stream);

		data->Streams[i].ComponentSemantics.resize(numSemantics);

		for (unsigned int j = 0; j < numSemantics; ++j)
		{
			data->Streams[i].ComponentSemantics[j].Name = Strings[Endian.read<unsigned int>(stream)];
			data->Streams[i].ComponentSemantics[j].Index = Endian.read<unsigned int>(stream);
		}
	}

	unsigned int numModifiers = Endian.read<unsigned int>(stream);

	data->Modifiers.resize(numModifiers);

	for (unsigned int i = 0; i < numModifiers; ++i)
		data->Modifiers[i] = FetchRef(stream);
}

void NifDocument::ParseTexturingProperty(std::string_view& stream, BlockData& block)
{
	NiTexturingProperty* data = block.AddData<NiTexturingProperty>();

	auto readTextureData = [&](NiTexturingProperty::TextureData& data)
	{
		data.HasThisTexture = Endian.read<char>(stream);

		if (!data.HasThisTexture) return;

		data.Source = FetchRef(stream);
		data.Flags = Endian.read<unsigned short>(stream);
		data.MaxAnisotropy = Endian.read<unsigned short>(stream);
		data.HasTextureTransform = Endian.read<char>(stream);

		if (data.HasTextureTransform)
		{
			float x = Endian.read<float>(stream);
			float y = Endian.read<float>(stream);

			data.Translation.Set(x, y);

			x = Endian.read<float>(stream);
			y = Endian.read<float>(stream);

			data.Scale.Set(x, y);
			data.Rotation = Endian.read<float>(stream);
			data.TransformMethod = Endian.read<unsigned int>(stream);

			x = Endian.read<float>(stream);
			y = Endian.read<float>(stream);

			data.Center.Set(x, y);
		}
	};

	ReadBlockRefs(stream, block, data->ExtraData);

	data->Controller = FetchRef(stream);
	data->Flags = Endian.read<unsigned short>(stream);
	data->TextureCount = Endian.read<unsigned int>(stream);

	readTextureData(data->BaseTexture);
	readTextureData(data->DarkTexture);
	readTextureData(data->DetailTexture);
	readTextureData(data->GlossTexture);
	readTextureData(data->GlowTexture);
	readTextureData(data->BumpTexture);

	if (data->BumpTexture.HasThisTexture)
	{
		data->BumpMapLumaScale = Endian.read<float>(stream);
		data->BumpMapLumaOffset = Endian.read<float>(stream);

		float x = Endian.read<float>(stream);
		float y = Endian.read<float>(stream);

		data->BumpMapRight.Set(x, y);

		x = Endian.read<float>(stream);
		y = Endian.read<float>(stream);

		data->BumpMapUp.Set(x, y);
	}

	readTextureData(data->NormalTexture);
	readTextureData(data->ParallaxTexture);
	readTextureData(data->Decal0Texture);

	unsigned int shaderTextureCount = Endian.read<unsigned int>(stream);

	data->ShaderTextures.resize(shaderTextureCount);

	for (unsigned int i = 0; i < shaderTextureCount; ++i)
	{
		readTextureData(data->ShaderTextures[i].Map);

		if (data->ShaderTextures[i].Map.HasThisTexture)
			data->ShaderTextures[i].MapId = Endian.read<unsigned int>(stream);
	}
}

void NifDocument::ParseSourceTexture(std::string_view& stream, BlockData& block)
{
	NiSourceTexture* data = block.AddData<NiSourceTexture>();

	ReadBlockRefs(stream, block, data->ExtraData);

	data->Controller = FetchRef(stream);
	data->UseExternal = Endian.read<unsigned char>(stream);
	
	unsigned int name = Endian.read<unsigned int>(stream);

	if (name != 0xFFFFFFFFu)
		data->FileName = Strings[name];

	data->PixelData = FetchRef(stream);
	data->PixelLayout = Endian.read<unsigned int>(stream);
	data->UseMipmaps = Endian.read<unsigned int>(stream);
	data->AlphaFormat = Endian.read<unsigned int>(stream);
	data->IsStatic = Endian.read<unsigned char>(stream);
	data->DirectRender = Endian.read<unsigned char>(stream);
	data->PersistRenderData = Endian.read<unsigned char>(stream);
}

void NifDocument::ParseStream(std::string_view& stream, BlockData& block)
{
	NiDataStream* data = block.AddData<NiDataStream>();

	data->Usage = (StreamUsage)(block.BlockType[13] - '0'); // they embedded both Usage and Access in the name, ew
	data->StreamSize = Endian.read<unsigned int>(stream);
	data->CloningBehavior = (CloningBehavior)Endian.read<unsigned int>(stream);

	unsigned int numRegions = Endian.read<unsigned int>(stream);

	data->Regions.resize(numRegions);

	for (unsigned int i = 0; i < numRegions; ++i)
	{
		data->Regions[i].StartIndex = Endian.read<unsigned int>(stream);
		data->Regions[i].NumIndices = Endian.read<unsigned int>(stream);
	}

	unsigned int numComponents = Endian.read<unsigned int>(stream);

	data->ComponentFormats.resize(numComponents);
	data->Attributes.resize(numComponents);

	for (unsigned int i = 0; i < numComponents; ++i)
	{
		data->ComponentFormats[i] = (ComponentFormat)Endian.read<unsigned int>(stream);

		auto index = ComponentInfo.find(data->ComponentFormats[i]);

		if (index != ComponentInfo.end())
		{
			data->Attributes[i].Type = index->second.DataType;
			data->Attributes[i].ElementCount = index->second.ElementCount;
		}
		else
		{
			data->Attributes[i].Type = Enum::AttributeDataType::Unknown;
			data->Attributes[i].ElementCount = 0;
		}
	}

	data->StreamData.resize(data->StreamSize);

	size_t amount = std::min((size_t)data->StreamSize, stream.size());

	std::memcpy(data->StreamData.data(), stream.data(), amount);
	advanceStream(stream, amount);

	data->Streamable = Endian.read<char>(stream);
}

Color3 NifDocument::ParseColor3(std::string_view& stream)
{
	float r = Endian.read<float>(stream);
	float g = Endian.read<float>(stream);
	float b = Endian.read<float>(stream);

	return Color3(r, g, b);
}

Color4 NifDocument::ParseColor4(std::string_view& stream)
{
	float r = Endian.read<float>(stream);
	float g = Endian.read<float>(stream);
	float b = Endian.read<float>(stream);
	float a = Endian.read<float>(stream);

	return Color4(r, g, b, a);
}

void NifDocument::ParseMaterialProperty(std::string_view& stream, BlockData& block)
{
	NiMaterialProperty* data = block.AddData<NiMaterialProperty>();

	ReadBlockRefs(stream, block, data->ExtraData);

	data->Controller = FetchRef(stream);
	data->AmbientColor = ParseColor3(stream);
	data->DiffuseColor = ParseColor3(stream);
	data->SpecularColor = ParseColor3(stream);
	data->EmissiveColor = ParseColor3(stream);
	data->Glossiness = Endian.read<float>(stream);
	data->Alpha = Endian.read<float>(stream);
}

void NifDocument::ParseSkinningMeshModifier(std::string_view& stream, BlockData& block)
{
	NiSkinningMeshModifier* data = block.AddData<NiSkinningMeshModifier>();

	unsigned int numSubmitPoints = Endian.read<unsigned int>(stream);

	for (unsigned int i = 0; i < numSubmitPoints; ++i)
		data->SubmitPoints.push_back(Endian.read<unsigned short>(stream));

	unsigned int numCompletePoints = Endian.read<unsigned int>(stream);

	for (unsigned int i = 0; i < numCompletePoints; ++i)
		data->CompletePoints.push_back(Endian.read<unsigned short>(stream));

	data->Flags = Endian.read<unsigned short>(stream);
	data->SkeletonRoot = FetchRef(stream);

	ParseTransform(stream, data->SkeletonTransformation, false);

	unsigned int numBones = Endian.read<unsigned int>(stream);

	for (unsigned int i = 0; i < numBones; ++i)
		data->Bones.push_back(FetchRef(stream));

	for (unsigned int i = 0; i < numBones; ++i)
	{
		data->BoneTransforms.push_back(NiTransform{});

		ParseTransform(stream, data->BoneTransforms.back(), false);
	}

	for (unsigned int i = 0; i < numBones; ++i)
	{
		data->BoneBounds.push_back(NiBounds{});

		ParseBounds(stream, data->BoneBounds.back());
	}
}

void NifDocument::ParseSequenceData(std::string_view& stream, BlockData& block)
{
	NiSequenceData* data = block.AddData<NiSequenceData>();

	unsigned int numEvaluators = Endian.read<unsigned int>(stream);

	data->Evaluators.resize(numEvaluators);

	for (unsigned int i = 0; i < numEvaluators; ++i)
		data->Evaluators[i] = FetchRef(stream);

	data->TextKeys = FetchRef(stream);
	data->Duration = Endian.read<float>(stream);
	data->CycleType = (CycleType)Endian.read<unsigned int>(stream);
	data->Frequency = Endian.read<float>(stream);

	unsigned int name = Endian.read<unsigned int>(stream);

	if (name != 0xFFFFFFFFu)
		data->AccumRootName = Strings[name];

	data->AccumFlags = (AccumFlags)Endian.read<unsigned int>(stream);
}

void NifDocument::ParseEvaluator(std::string_view& stream, BlockData& block, NiEvaluator* data)
{
	data->NodeName = FetchString(stream);
	data->PropertyType = FetchString(stream);
	data->ControllerType = FetchString(stream);
	data->ControllerId = FetchString(stream);
	data->InterpolatorId = FetchString(stream);
	
	unsigned char positionChannel = Endian.read<unsigned char>(stream);
	unsigned char rotationChannel = Endian.read<unsigned char>(stream);
	unsigned char scaleChannel = Endian.read<unsigned char>(stream);
	unsigned char flags = Endian.read<unsigned char>(stream);

	data->PositionPosed = positionChannel & 0x40;
	data->PositionChannel = (ChannelType)(positionChannel & 0x2F);
	data->RotationPosed = rotationChannel & 0x40;
	data->RotationChannel = (ChannelType)(rotationChannel & 0x2F);
	data->ScalePosed = scaleChannel & 0x40;
	data->ScaleChannel = (ChannelType)(scaleChannel & 0x2F);

	data->ChannelFlags = (ChannelTypeFlags)flags;
}

void NifDocument::ParseBSplineCompTransformEvaluator(std::string_view& stream, BlockData& block)
{
	NiBSplineCompTransformEvaluator* data = block.AddData<NiBSplineCompTransformEvaluator>();

	ParseEvaluator(stream, block, data);

	data->StartTime = Endian.read<float>(stream);
	data->EndTime = Endian.read<float>(stream);
	data->Data = FetchRef(stream);
	data->BasisData = FetchRef(stream);

	ParseTransform(stream, data->Transform, true, true);

	data->TranslationHandle = Endian.read<unsigned int>(stream);
	data->RotationHandle = Endian.read<unsigned int>(stream);
	data->ScaleHandle = Endian.read<unsigned int>(stream);
	data->TranslationOffset = Endian.read<float>(stream);
	data->TranslationHalfRange = Endian.read<float>(stream);
	data->RotationOffset = Endian.read<float>(stream);
	data->RotationHalfRange = Endian.read<float>(stream);
	data->ScaleOffset = Endian.read<float>(stream);
	data->ScaleHalfRange = Endian.read<float>(stream);
}

void NifDocument::ParseBSpineData(std::string_view& stream, BlockData& block)
{
	NiBSpineData* data = block.AddData<NiBSpineData>();

	unsigned int numFloatControlPoints = Endian.read<unsigned int>(stream);

	data->FloatControlPoints.resize(numFloatControlPoints);

	for (unsigned int i = 0; i < numFloatControlPoints; ++i)
		data->FloatControlPoints[i] = Endian.read<float>(stream);

	unsigned int numCompactControlPoints = Endian.read<unsigned int>(stream);

	data->CompactControlPoints.resize(numCompactControlPoints);

	for (unsigned int i = 0; i < numCompactControlPoints; ++i)
		data->CompactControlPoints[i] = Endian.read<short>(stream);
}

void NifDocument::ParseBSplineBasisData(std::string_view& stream, BlockData& block)
{
	NiBSplineBasisData* data = block.AddData<NiBSplineBasisData>();

	data->NumControlPoints = Endian.read<unsigned int>(stream);
}

void NifDocument::ParseTransformEvaluator(std::string_view& stream, BlockData& block)
{
	NiTransformEvaluator* data = block.AddData<NiTransformEvaluator>();

	ParseEvaluator(stream, block, data);
	ParseTransform(stream, data->Value, true, true);

	data->Data = FetchRef(stream);
}

template <>
float ParseKey<float>(NifDocument* document, std::string_view& stream)
{
	return document->Endian.read<float>(stream);
}

template <>
Quaternion ParseKey<Quaternion>(NifDocument* document, std::string_view& stream)
{
	float x = document->Endian.read<float>(stream);
	float y = document->Endian.read<float>(stream);
	float z = document->Endian.read<float>(stream);
	float w = document->Endian.read<float>(stream);

	return Quaternion(Vector3(x, y, z, w));
}

template <>
Vector3F ParseKey<Vector3F>(NifDocument* document, std::string_view& stream)
{
	float x = document->Endian.read<float>(stream);
	float y = document->Endian.read<float>(stream);
	float z = document->Endian.read<float>(stream);

	return Vector3F(x, y, z);
}


void NifDocument::ParseTransformData(std::string_view& stream, BlockData& block)
{
	NiTransformData* data = block.AddData<NiTransformData>();

	data->RotationKeys.Parse(this, stream);
	data->TranslationKeys.Parse(this, stream);
	data->ScaleKeys.Parse(this, stream);
}

void NifDocument::ParseTextKeyExtraData(std::string_view& stream, BlockData& block)
{
	NiTextKeyExtraData* data = block.AddData<NiTextKeyExtraData>();

	unsigned int length = Endian.read<unsigned int>(stream);

	data->TextKeys.resize(length);

	for (unsigned int i = 0; i < length; ++i)
	{
		data->TextKeys[i].Time = Endian.read<float>(stream);
		data->TextKeys[i].Value = FetchString(stream);
	}
}

void NifDocument::ParseColorExtraData(std::string_view& stream, BlockData& block)
{
	NiColorExtraData* data = block.AddData<NiColorExtraData>();

	data->Value = ParseColor4(stream);
}

void NifDocument::ParseFloatExtraData(std::string_view& stream, BlockData& block)
{
	NiFloatExtraData* data = block.AddData<NiFloatExtraData>();

	data->Value = Endian.read<float>(stream);
}

void NifDocument::ParseAlphaProperty(std::string_view& stream, BlockData& block)
{
	NiAlphaProperty* data = block.AddData<NiAlphaProperty>();

	ReadBlockRefs(stream, block, data->ExtraData);

	data->Controller = FetchRef(stream);
	data->Flags = Endian.read<unsigned short>(stream);
	data->Threshold = Endian.read<unsigned char>(stream);
}

void NifDocument::ParseVertexColorProperty(std::string_view& stream, BlockData& block)
{
	NiVertexColorProperty* data = block.AddData<NiVertexColorProperty>();

	ReadBlockRefs(stream, block, data->ExtraData);

	data->Controller = FetchRef(stream);
	data->Flags = Endian.read<unsigned short>(stream);
}

void advanceStream(std::string_view& stream, size_t amount)
{
	stream = std::string_view(stream.data() + amount, stream.size() - amount);
}

void NifDocument::ParserNoOp(std::string_view& stream, BlockData& block)
{
	advanceStream(stream, block.BlockSize);
}

std::unordered_map<std::string, NifDocument::BlockParseFunction> parserFunctions = {
	{ "NiNode", &NifDocument::ParseNode },
	{ "NiMesh", &NifDocument::ParseMesh },
	{ "NiTexturingProperty", &NifDocument::ParseTexturingProperty },
	{ "NiSourceTexture", &NifDocument::ParseSourceTexture },
	{ "NiDataStream", &NifDocument::ParseStream },
	{ "NiMaterialProperty", &NifDocument::ParseMaterialProperty },
	{ "NiSkinningMeshModifier", &NifDocument::ParseSkinningMeshModifier },
	{ "NiSequenceData", &NifDocument::ParseSequenceData },
	{ "NiBSplineCompTransformEvaluator", &NifDocument::ParseBSplineCompTransformEvaluator },
	{ "NiBSpineData", &NifDocument::ParseBSpineData },
	{ "NiBSplineBasisData", &NifDocument::ParseBSplineBasisData },
	{ "NiTransformEvaluator", &NifDocument::ParseTransformEvaluator },
	{ "NiTransformData", &NifDocument::ParseTransformData },
	{ "NiTextKeyExtraData", &NifDocument::ParseTextKeyExtraData },
	{ "NiColorExtraData", &NifDocument::ParseColorExtraData },
	{ "NiFloatExtraData", &NifDocument::ParseFloatExtraData },
	{ "NiAlphaProperty", &NifDocument::ParseAlphaProperty },
	{ "NiVertexColorProperty", &NifDocument::ParseVertexColorProperty }
};

std::set<std::string> ignoreBlockName = {
	"NiFloatInterpolator",
	"NiFloatData",
	"NiDataStream",
	"NiTextureTransformController",
	"NiTransformController",
	"NiTransformInterpolator",
	"NiSkinningMeshModifier",
	"NiBSplineCompTransformEvaluator",
	"NiBSplineData",
	"NiBSplineBasisData",
	"NiTransformEvaluator",
	"NiTransformData"
};

std::unordered_map<std::string, std::string> attributeAliases = {
	{ "POSITION", "position" },
	{ "POSITION_BP", "position" },
	{ "NORMAL", "normal" },
	{ "NORMAL_BP", "normal" },
	{ "TEXCOORD", "texcoord" },
	{ "BINORMAL", "binormal" },
	{ "BINORMAL_BP", "binormal" },
	{ "TANGENT", "tangent" },
	{ "TANGENT_BP", "tangent" },
	{ "MORPH_POSITION", "morphpos" },
	{ "MORPH_POSITION_BP", "morphpos" },
	{ "BLENDINDICES", "blendindices" },
	{ "BLENDWEIGHT", "blendweight" },
	{ "COLOR", "color" }
};

using namespace Engine::Graphics;

void NifParser::Parse(std::istream& stream)
{
	std::streampos start = stream.tellg();
	stream.seekg(0, std::ios::end);
	std::streampos length = stream.tellg() - start;
	stream.seekg(start);
	std::string buffer;
	buffer.resize(length);
	stream.read(&buffer[0], length);

	Parse(buffer);
}

void NifParser::Parse(std::string_view stream)
{
	std::string_view streamStart = stream;

	NifDocument document;

	std::string headerString;

	size_t index = 0;

	for (index; stream[index] != 0x0A; ++index);

	headerString.append(stream.data(), index);

	advanceStream(stream, index + 1);
	advanceStream(stream, 4);

	Endian endian = Endian(stream[0] ? std::endian::little : std::endian::big);
	document.Endian = endian;

	advanceStream(stream, 1);

	unsigned int userVersion = endian.read<unsigned int>(stream);
	unsigned int numBlocks = endian.read<unsigned int>(stream);
	unsigned int metaBlockSize = endian.read<unsigned int>(stream);
	
	advanceStream(stream, metaBlockSize);

	unsigned short numBlockTypes = endian.read<unsigned short>(stream);

	if (numBlockTypes == 0)
		return;

	document.BlockTypes.resize(numBlockTypes);
	document.BlockTypeIndices.resize(numBlocks);
	document.BlockSizes.resize(numBlocks);

	for (unsigned short i = 0; i < numBlockTypes; ++i)
	{
		unsigned int blockTypeSize = endian.read<unsigned int>(stream);

		if (blockTypeSize > 0)
		{
			document.BlockTypes[i].append(stream.data(), blockTypeSize);
			advanceStream(stream, blockTypeSize);
		}
	}

	for (unsigned int i = 0; i < numBlocks; ++i)
		document.BlockTypeIndices[i] = 0x7FFF & endian.read<unsigned short>(stream);

	for (unsigned int i = 0; i < numBlocks; ++i)
		document.BlockSizes[i] = endian.read<unsigned int>(stream);

	unsigned int numStrings = endian.read<unsigned int>(stream);
	unsigned int maxStringLength = endian.read<unsigned int>(stream);

	document.Strings.resize(numStrings);

	for (unsigned int i = 0; i < numStrings; ++i)
	{
		unsigned int stringLength = endian.read<unsigned int>(stream);

		if (stringLength > 0)
		{
			document.Strings[i].append(stream.data(), stringLength);
			advanceStream(stream, stringLength);
		}
	}

	unsigned int numGroups = endian.read<unsigned int>(stream);

	if (numGroups > 0)
		throw "WARNING, UNIMPLEMENTED";

	document.Blocks.resize(numBlocks);

	for (unsigned int blockIndex = 0; blockIndex < numBlocks; ++blockIndex)
	{
		BlockData& block = document.InitializeBlock(blockIndex);

		unsigned int position = (unsigned int)(stream.data() - streamStart.data());//stream.tellg();

		size_t truncateIndex = 0;

		for (truncateIndex; truncateIndex < block.BlockType.size() && block.BlockType[truncateIndex] > 1; ++truncateIndex);

		std::string typeName = block.BlockType.substr(0, truncateIndex);

		if (block.BlockSize > 0)
		{
			auto parserIterator = parserFunctions.find(typeName);

			if (parserIterator == parserFunctions.end())
				document.ParserNoOp(stream, block);
			else
			{
				auto iterator = ignoreBlockName.find(typeName);

				if (iterator == ignoreBlockName.end())
				{
					unsigned int name = endian.read<unsigned int>(stream);

					if (name != 0xFFFFFFFFu)
						block.BlockName = document.Strings[name];

					block.BlockStart = 4;
				}

				(document.*(parserIterator->second))(stream, block);
			}
		}

		unsigned int newPosition = (unsigned int)(stream.data() - streamStart.data());
		unsigned int parsedInBlock = newPosition - position;

		if (parsedInBlock != block.BlockSize)
		{
			advanceStream(stream, block.BlockSize - parsedInBlock);

			auto parserIterator = parserFunctions.find(typeName);

			if (parserIterator == parserFunctions.end())
				document.ParserNoOp(stream, block);
			else
				(document.*(parserIterator->second))(stream, block);

			throw "block parser read wrong amount";
		}
	}

	std::unordered_map<unsigned int, BlockData*> parents;
	std::unordered_map<unsigned int, size_t> parentEntries;
	std::unordered_map<unsigned int, size_t> parentLinkTypes;
	std::unordered_map<unsigned int, size_t> materials;
	std::unordered_map<unsigned int, size_t> nodeIndices;
	std::unordered_map<size_t, size_t> boneIndices;

	for (unsigned int blockIndex = 0; blockIndex < numBlocks; ++blockIndex)
	{
		BlockData& block = document.Blocks[blockIndex];

		size_t parentIndex = (size_t)-1;
		auto parentEntryIndex = parentEntries.find(blockIndex);

		if (parentEntryIndex != parentEntries.end())
			parentIndex = parentEntryIndex->second;

		if (block.BlockType == "NiNode")
		{
			NiNode* data = block.Data->Cast<NiNode>();

			nodeIndices[data->BlockIndex] = Package->Nodes.size();

			for (size_t i = 0; i < data->Children.size(); ++i)
			{
				if (data->Children[i] == nullptr) continue;

				unsigned int childBlock = data->Children[i]->BlockIndex;

				parents[childBlock] = &block;
				parentEntries[childBlock] = Package->Nodes.size();
			}

			NiTransform& nodeTransform = data->Transformation;

			std::shared_ptr<Engine::Transform> transform = Engine::Create<Engine::Transform>();
			transform->SetTransformation(Matrix4F(nodeTransform.Translation) * nodeTransform.Rotation * Matrix4F::NewScale(nodeTransform.Scale, nodeTransform.Scale, nodeTransform.Scale));
			transform->SetInheritsTransformation((data->Flags & 0x4 || true) != 0);// || true);
			transform->Name = block.BlockName;

			Package->Nodes.push_back(ModelPackageNode{ block.BlockName, parentIndex, (size_t)-1, false, false, nullptr, nullptr, transform });
		}
		else if (block.BlockType == "NiMesh")
		{
			NiMesh* data = block.Data->Cast<NiMesh>();

			nodeIndices[data->BlockIndex] = Package->Nodes.size();

			size_t materialIndex = (size_t)-1;

			if (data->Materials.size() > 1)
				materialIndex += 0;

			//if (data->Materials.size() > 0)
			{
				size_t currentMaterial = 0;

				for (size_t i = 0; i < data->Properties.size(); ++i)
				{
					if (data->Properties[i]->BlockType == "NiMaterialProperty")
					{
						const BlockData* materialBlock = data->Properties[i];
						NiMaterialProperty* materialData = materialBlock->Data->Cast<NiMaterialProperty>();

						if (materials.contains(materialBlock->BlockIndex))
						{
							materialIndex = materials[materialBlock->BlockIndex];

							break;
						}

						materialIndex = Package->Materials.size();

						materials[materialBlock->BlockIndex] = materialIndex;
						Package->Materials.push_back(ModelPackageMaterial{});

						ModelPackageMaterial& material = Package->Materials.back();

						material.Name = materialBlock->BlockName;
						material.ShaderName = data->Materials.size() > 0 ? data->Materials[0] : "";
						material.DiffuseColor = materialData->DiffuseColor;
						material.SpecularColor = materialData->SpecularColor;
						material.AmbientColor = materialData->AmbientColor;
						material.EmissiveColor = materialData->EmissiveColor;
						material.Shininess = materialData->Glossiness;
						material.Alpha = materialData->Alpha;

						for (size_t j = 0; j < data->Properties.size(); ++j)
						{
							const BlockData* propertyBlock = data->Properties[j];

							if (propertyBlock->BlockType == "NiTexturingProperty")
							{
								NiTexturingProperty* propertyData = propertyBlock->Data->Cast<NiTexturingProperty>();

								bool breakP = false;

								const auto fetchPath = [this, &breakP](const NiTexturingProperty::TextureData& texture) -> const std::string&
								{
									static const std::string empty("");

									if (texture.Source == nullptr) return empty;

									const NiSourceTexture* textureData = texture.Source->GetData<NiSourceTexture>();

									if (breakP)
										breakP |= true;

									return textureData->FileName;
								};

								const auto fetchTransform = [this](const NiTexturingProperty::TextureData& texture) -> ModelPackageTextureTransform
								{
									if (!texture.HasThisTexture || !texture.HasTextureTransform)
										return ModelPackageTextureTransform{};

									return ModelPackageTextureTransform
									{
										texture.HasTextureTransform,
										texture.Translation,
										texture.Scale,
										texture.Center,
										texture.Rotation,
										(int)texture.TransformMethod
									};
								};

								material.TextureApplyMode = (propertyData->Flags >> 1) & 0x3;

								material.Diffuse = fetchPath(propertyData->BaseTexture);
								material.DiffuseTransform = fetchTransform(propertyData->BaseTexture);
								material.Normal = fetchPath(propertyData->NormalTexture);
								material.NormalTransform = fetchTransform(propertyData->NormalTexture);
								material.Specular = fetchPath(propertyData->GlossTexture);
								material.SpecularTransform = fetchTransform(propertyData->GlossTexture);
								material.Glow = fetchPath(propertyData->GlowTexture);
								material.GlowTransform = fetchTransform(propertyData->GlowTexture);
								material.Decal = fetchPath(propertyData->Decal0Texture);
								material.DecalTransform = fetchTransform(propertyData->Decal0Texture);

								if (propertyData->ShaderTextures.size() > 0)
								{
									if (propertyData->ShaderTextures.size() > 1)
									{
										if (material.ShaderName == "MS2CharacterHairMaterial")
										{
											material.Anisotropic = fetchPath(propertyData->ShaderTextures[1].Map);
											material.AnisotropicTransform = fetchTransform(propertyData->ShaderTextures[1].Map);
										}
									}

									material.OverrideColor = fetchPath(propertyData->ShaderTextures[0].Map);
									material.OverrideColorTransform = fetchTransform(propertyData->ShaderTextures[0].Map);
								}

								breakP = true;

								//fetchPath(data->DarkTexture);
								//fetchPath(data->DetailTexture);
								fetchPath(propertyData->BumpTexture);
								fetchPath(propertyData->ParallaxTexture);
								//fetchPath(data->Decal0Texture);
							}
							else if (propertyBlock->BlockType == "NiAlphaProperty")
							{
								NiAlphaProperty* propertyData = propertyBlock->Data->Cast<NiAlphaProperty>();

								material.SourceBlendMode = (propertyData->Flags >> 1) & 0xF;
								material.DestBlendMode = (propertyData->Flags >> 5) & 0xF;
								material.AlphaTestMode = (propertyData->Flags >> 9) & 0xF;
								material.TestThreshold = propertyData->Threshold;
							}
							else if (propertyBlock->BlockType == "NiVertexColorProperty")
							{
								NiVertexColorProperty* propertyData = propertyBlock->Data->Cast<NiVertexColorProperty>();

								material.LightingMode = (propertyData->Flags >> 3) & 0x1;
								material.SourceVertexMode = (propertyData->Flags >> 4) & 0x3;
							}
						}

						for (size_t j = 0; j < data->ExtraData.size(); ++j)
						{
							const BlockData* propertyBlock = data->ExtraData[j];

							if (propertyBlock->BlockType == "NiColorExtraData")
							{
								NiColorExtraData* propertyData = propertyBlock->Data->Cast<NiColorExtraData>();

								if (propertyBlock->BlockName.size() != 14 && strncmp(propertyBlock->BlockName.c_str(), "OverrideColor", 13))
									continue;

								char overrideSlot = propertyBlock->BlockName[13];

								if (overrideSlot < '0' || overrideSlot > '2')
									continue;

								overrideSlot -= '0';

								switch (overrideSlot)
								{
								case 0:
									material.OverrideColor0 = propertyData->Value;
									break;
								case 1:
									material.OverrideColor1 = propertyData->Value;
									break;
								case 2:
									material.OverrideColor2 = propertyData->Value;
									break;
								default: break;
								}
							}
							else if (propertyBlock->BlockType == "NiFloatExtraData")
							{
								NiFloatExtraData* propertyData = propertyBlock->Data->Cast<NiFloatExtraData>();

								if (propertyBlock->BlockName == "FresnelBoost")
									material.FresnelBoost = propertyData->Value;
								else if (propertyBlock->BlockName == "FresnelExponent")
									material.FresnelExponent = propertyData->Value;
								else if (propertyBlock->BlockName == "ColorBoost")
									material.ColorBoost = propertyData->Value;
							}
						}

						++currentMaterial;
					}
				}

				if (currentMaterial > 1)
					currentMaterial += 0;

				if (materialIndex != (size_t)-1)
					for (size_t i = 0; i < data->Properties.size(); ++i)
						parentEntries[data->Properties[i]->BlockIndex] = materialIndex;

				for (size_t i = 0; i < data->ExtraData.size(); ++i)
				{
					parentEntries[data->ExtraData[i]->BlockIndex] = materialIndex;
				}
			}

			size_t indexBufferBinding = 0;
			std::vector<int> indexBuffer;

			for (size_t i = 0; i < data->Streams.size(); ++i)
			{
				NiDataStream* stream = data->Streams[i].Stream->Data->Cast<NiDataStream>();

				if (stream->Usage == StreamUsage::IndexBuffer)
				{
					NiDataStream* stream = data->Streams[i].Stream->Data->Cast<NiDataStream>();

					indexBufferBinding = i;

					size_t indexCount = stream->Regions[0].NumIndices;

					indexBuffer.resize(indexCount);

					const char* buffer = reinterpret_cast<const char*>(stream->StreamData.data());

					for (size_t j = 0; j < indexCount; ++j)
						stream->Attributes[0].Copy(buffer + j * stream->Attributes[0].GetSize(), indexBuffer.data() + j, Enum::AttributeDataType::Int32);

					break;
				}
			}

			std::vector<Engine::Graphics::VertexAttributeFormat> attributes;
			std::vector<void*> dataBuffers;

			size_t binding = 0;
			size_t vertexCount = 0;

			for (size_t i = 0; i < data->Streams.size(); ++i)
			{
				if (data->Streams[i].Stream->Data == nullptr) continue;

				NiDataStream* stream = data->Streams[i].Stream->Data->Cast<NiDataStream>();

				if (stream->Usage != StreamUsage::VertexBuffer) continue;

				size_t semanticsCount = data->Streams[i].ComponentSemantics.size();
				size_t attributeCount = stream->Attributes.size();

				vertexCount = stream->Regions[0].NumIndices;

				if (semanticsCount != attributeCount)
					throw "mismatching semantics and attributes";

				dataBuffers.push_back(stream->StreamData.data());

				for (size_t j = 0; j < semanticsCount; ++j)
				{
					const std::string semantic = data->Streams[i].ComponentSemantics[j].Name;

					auto index = attributeAliases.find(semantic);

					if (!SemanticsFound.contains(semantic))
						SemanticsFound.insert(semantic);

					if (index == attributeAliases.end())
						stream->Attributes[j].Name = semantic;
					else
						stream->Attributes[j].Name = index->second;

					if (data->Streams[i].ComponentSemantics[j].Index != 0)
					{
						std::stringstream name;
						name << stream->Attributes[j].Name << data->Streams[i].ComponentSemantics[j].Index;
						stream->Attributes[j].Name = name.str();
					}

					stream->Attributes[j].Binding = binding;

					attributes.push_back(stream->Attributes[j]);
				}

				++binding;
			}

			NiTransform& nodeTransform = data->Transformation;

			std::shared_ptr<Engine::Transform> transform = Engine::Create<Engine::Transform>();
			transform->SetInheritsTransformation((data->Flags & 0x4 || true) != 0);// || true);
			transform->Name = block.BlockName;

			ImportedNiMesh mesh;

			mesh.Format = Engine::Graphics::MeshFormat::GetFormat(attributes);
			mesh.Mesh = Engine::Create<Engine::Graphics::MeshData>();
			mesh.Mesh->SetFormat(mesh.Format);
			mesh.Mesh->PushVertices(vertexCount, false);
			mesh.Mesh->PushIndices(indexBuffer);

			mesh.Format->Copy(dataBuffers.data(), mesh.Mesh->GetData(), mesh.Format, vertexCount);

			Matrix4F transformation = Matrix4F(nodeTransform.Translation) * nodeTransform.Rotation * Matrix4F::NewScale(nodeTransform.Scale, nodeTransform.Scale, nodeTransform.Scale);

			transform->SetTransformation(transformation);

			ImportedMeshes.push_back(mesh);

			std::vector<size_t> bones;

			for (size_t i = 0; i < data->Modifiers.size(); ++i)
			{
				if (data->Modifiers[i]->BlockType == "NiSkinningMeshModifier")
				{
					const BlockData* skinBlock = data->Modifiers[i];
					NiSkinningMeshModifier* skinData = skinBlock->Data->Cast<NiSkinningMeshModifier>();
					size_t skinRootIndex = nodeIndices[skinData->SkeletonRoot->BlockIndex];
					
					MarkBone(skinRootIndex, boneIndices);

					bones.push_back(boneIndices[skinRootIndex]);

					for (size_t j = 0; j < skinData->Bones.size(); ++j)
					{
						const BlockData* boneData = skinData->Bones[j];
						size_t boneIndex = nodeIndices[boneData->BlockIndex];

						MarkBone(boneIndex, boneIndices);

						bones.push_back(boneIndices[boneIndex]);
					}
				}
			}

			Package->Nodes.push_back(ModelPackageNode{ block.BlockName, parentIndex, materialIndex, false, false, mesh.Format, mesh.Mesh, transform, bones });
		}
	}

	for (size_t i = 0; i < Package->Nodes.size(); ++i)
		if (Package->Nodes[i].AttachedTo != (size_t)-1)
			Package->Nodes[i].Transform->SetParent(Package->Nodes[Package->Nodes[i].AttachedTo].Transform);
}

void NifParser::MarkBone(size_t index, std::unordered_map<size_t, size_t>& boneIndices)
{
	if (Package->Nodes[index].IsInBoneList) return;

	boneIndices[index] = Package->Bones.size();
	Package->Bones.push_back(index);
	Package->Nodes[index].IsBone = true;
	Package->Nodes[index].IsInBoneList = true;

	for (size_t parent = Package->Nodes[index].AttachedTo; parent != (size_t)-1 && !Package->Nodes[parent].IsBone; parent = Package->Nodes[parent].AttachedTo)
	{
		Package->Nodes[parent].IsBone = true;
	}
}

std::unordered_set<std::string> NifParser::SemanticsFound = {};