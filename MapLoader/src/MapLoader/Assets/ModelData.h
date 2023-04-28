#pragma once

#include <vector>
#include <memory>
#include <string>

#include <Engine/Math/Matrix4.h>
#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include <host_device.h>
#include <ArchiveParser/MetadataMapper.h>
#include <nvvk/resourceallocator_vk.hpp>

namespace Engine
{
	namespace Graphics
	{
		struct ModelPackageAnimation;
	}
}

namespace MapLoader
{
	using MaterialObj = WaveFrontMaterial;

	class RTScene;

	struct ModelNode
	{
		std::string Name;
		int MeshId = -1;
		bool IsBone = false;
		bool IsInBoneList = false;
		size_t AttachedTo = (size_t)-1;
		Matrix4F Transformation;
		Matrix4F LocalTransformation;
		std::string Shader;
		std::string MaterialName;
		MaterialObj Material;
		std::shared_ptr<Engine::Graphics::MeshData> Mesh;
		std::vector<size_t> Bones;
		size_t Vertices = 0;
		size_t Indices = 0;
		bool HasTransparency = false;
		bool HasInvisibility = false;
	};

	struct ModelData
	{
		uint32_t Index = 0;
		std::vector<ModelNode> Nodes;
		std::vector<size_t> BoneIndices;
		const Archive::Metadata::Entry* Entry = nullptr;
		int DuplicateFormatUses = 0;
		std::vector<Engine::Graphics::ModelPackageAnimation> Animations;
		//ParentNifTransforms NodeTransforms;

		bool IsLoaded(size_t index) const;

		uint32_t GetId(size_t index) const;
	};

	struct MeshDescription
	{
		uint32_t IndexCount = 0;
		uint32_t VertexCount = 0;
		size_t BlasIndex = (size_t)-1;
		uint32_t drawFlags = VisibilityFlags::eStandardVisibility | VisibilityFlags::eHasShadow;
		nvvk::Buffer VertexPosBuffer;    // Device buffer of all 'Vertex'
		nvvk::Buffer VertexAttribBuffer;    // Device buffer of all 'Vertex'
		nvvk::Buffer VertexColorBuffer;    // Device buffer of all 'Vertex'
		nvvk::Buffer VertexBinormalBuffer;    // Device buffer of all 'Vertex'
		nvvk::Buffer VertexMorphBuffer;    // Device buffer of all 'Vertex'
		nvvk::Buffer VertexBlendBuffer;    // Device buffer of all 'Vertex'
		nvvk::Buffer IndexBuffer;     // Device buffer of the indices forming triangles
	};

	struct WireframeDescription
	{
		uint32_t IndexCount = 0;
		uint32_t VertexCount = 0;
		nvvk::Buffer VertexBuffer;
		nvvk::Buffer IndexBuffer;
	};
}