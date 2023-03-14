#pragma once

#include <vector>
#include <memory>
#include <string>

#include <Engine/Math/Matrix4.h>
#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include <host_device.h>
#include <ArchiveParser/MetadataMapper.h>
#include <nvvk/resourceallocator_vk.hpp>

namespace MapLoader
{
	using MaterialObj = WaveFrontMaterial;

	class RTScene;

	struct ModelData
	{
		uint32_t Index = 0;
		std::vector<int> MeshIds;
		std::vector<Matrix4F> Transformations;
		std::vector<std::string> Shaders;
		std::vector<std::string> MaterialNames;
		std::vector<std::string> NodeNames;
		std::vector<MaterialObj> Materials;
		std::vector<std::shared_ptr<Engine::Graphics::MeshData>> Meshes;
		const Archive::Metadata::Entry* Entry = nullptr;

		bool IsLoaded(size_t index) const;

		uint32_t GetId(size_t index) const;
	};

	struct MeshDescription
	{
		uint32_t IndexCount = 0;
		uint32_t VertexCount = 0;
		nvvk::Buffer VertexBuffer;    // Device buffer of all 'Vertex'
		nvvk::Buffer IndexBuffer;     // Device buffer of the indices forming triangles
		nvvk::Buffer MatColorBuffer;  // Device buffer of array of 'Wavefront material'
		nvvk::Buffer MatIndexBuffer;  // Device buffer of array of 'Wavefront material'
	};
}