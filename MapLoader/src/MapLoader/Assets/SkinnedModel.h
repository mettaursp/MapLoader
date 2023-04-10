#pragma once

#include <nvvk/resourceallocator_vk.hpp>
#include <MapLoader/Vulkan/VulkanContext.h>
#include <MapLoader/Scene/RTScene.h>
#include <Engine/Math/Matrix4.h>
#include <MapLoader/Assets/GameAssetLibrary.h>
#include <MapLoader/Scene/SceneObject.h>

namespace MapLoader
{
	class GameAssetLibrary;
	class RTScene;

	struct SkinnedMesh
	{
		bool HasSkeleton = false;
		bool HasMorphAnimation = false;
		size_t MeshId = (size_t)-1; // Spawned model instance index
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

	class SkinnedModel : public SceneObject
	{
	public:
		SkinnedModel(const std::shared_ptr<GameAssetLibrary>& assetLibrary, const std::shared_ptr<RTScene>& scene);
		~SkinnedModel();

		void AddModel(struct ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback);
		void AddModel(struct ModelData* model, const Matrix4F& transformation, const std::string& selfNode, const std::string& targetNode, const ModelSpawnCallback& callback);
		void SendSkeletonToGpu();

		void ReleaseResources();

		void CreateRigDebugMesh(class ModelLibrary& modelLibrary);

		const auto& GetRigNodes() const { return RigNodes; }
		const auto& GetSkeletonBuffer() const { return SkeletonBuffer; }
		const auto& GetModels() const { return Models; }
		const auto& GetAssetLibrary() const { return AssetLibrary; }

	private:
		struct SpawningData
		{
			const ModelSpawnCallback& Callback;
			SkinnedModelEntry& CurrentEntry;
			nvvk::CommandPool CmdGen;
		};

		struct SceneEntry
		{
			RTScene* Scene = nullptr;
			size_t Index = (size_t)-1;
		};

		std::shared_ptr<GameAssetLibrary> AssetLibrary;
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		std::shared_ptr<RTScene> Scene;
		std::vector<Matrix4F> SkeletonData;
		std::vector<RigNode> RigNodes;
		std::vector<SkinnedModelEntry> Models;
		std::unordered_map<std::string, size_t> NodeIndices;
		SpawningData* SpawnParameters = nullptr;
		bool SkeletonDataIsStale = false;
		size_t LastSkeletonDataSize = 0;
		nvvk::Buffer SkeletonBuffer;

		void AddModels(MapLoader::ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback, const std::string& selfNode = "", size_t parentIndex = (size_t)-1);
		void AddRigNodes(MapLoader::ModelData* model, const Matrix4F& transformation, const std::string& selfNode = "", size_t parentIndex = (size_t)-1);
		bool SpawnModelCallback(ModelSpawnParameters& spawnParameters);
		void UpdateGpuData();
	};
}