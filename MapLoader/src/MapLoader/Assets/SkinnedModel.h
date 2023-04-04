#pragma once

#include <nvvk/resourceallocator_vk.hpp>
#include <MapLoader/Vulkan/VulkanContext.h>
#include <MapLoader/Scene/RTScene.h>
#include <Engine/Math/Matrix4.h>

namespace MapLoader
{
	struct SkinnedMesh
	{
		size_t ModelIndex = (size_t)-1; // Model entry
		size_t MeshIndex = (size_t)-1; // Mesh index in model
		nvvk::Buffer SkeletonSectionIndicesBuffer;
		nvvk::Buffer VertexPosOverride;
		nvvk::Buffer VertexBinormalOverride;
	};

	struct SkinnedModelEntry
	{
		struct ModelData* Model = nullptr;
		std::vector<SkinnedMesh> Meshes;
	};

	struct RigNode
	{
		bool IsBone = false;
		size_t ParentIndex = (size_t)-1;
		size_t SkeletonIndex = (size_t)-1;
		Matrix4F Transformation;
		Matrix4F LocalTransformation;
		Matrix4F BaseTransform;
	};

	class SkinnedModel
	{
	public:
		SkinnedModel(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext);
		~SkinnedModel();

		void SetTransformation(const Matrix4F& transformation);
		void AddModel(struct ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback);
		void AddModel(struct ModelData* model, const Matrix4F& transformation, const std::string& selfNode, const std::string& targetNode, const ModelSpawnCallback& callback);

		void CreateRigDebugMesh(class ModelLibrary& modelLibrary);

	private:
		struct SpawningData
		{
			const ModelSpawnCallback& Callback;
			SkinnedModelEntry& CurrentEntry;
		};

		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		std::vector<Matrix4F> SkeletonData;
		std::vector<RigNode> RigNodes;
		std::vector<SkinnedModelEntry> Models;
		std::unordered_map<std::string, size_t> NodeIndices;
		SpawningData* SpawnParameters = nullptr;
		bool SkeletonDataIsStale = false;
		Matrix4F Transformation;

		void AddRigNodes(MapLoader::ModelData* model, const Matrix4F& transformation, const std::string& selfNode, size_t parentIndex = (size_t)-1);
		bool SpawnModelCallback(MapLoader::ModelData* model, size_t i, InstDesc& instance);
		void UpdateGpuData();
	};
}