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
		size_t MeshNodeIndex = (size_t)-1;
		size_t MeshId = (size_t)-1; // Spawned model instance index
		size_t MeshIndex = (size_t)-1; // Mesh index in model
		size_t BlasInstanceId = (size_t)-1;
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
		std::string Name;
		bool IsBone = false;
		size_t ParentIndex = (size_t)-1;
		size_t SkeletonIndex = (size_t)-1;
		Matrix4F Transformation;
		Matrix4F LocalTransformation;
		Matrix4F BaseTransform;
		Matrix4F BaseTransformInverse;
		bool IsStale = false;
	};

	class AnimationPlayer;

	class SkinnedModel : public SceneObject
	{
	public:
		SkinnedModel(const std::shared_ptr<GameAssetLibrary>& assetLibrary, const std::shared_ptr<RTScene>& scene);
		~SkinnedModel();

		void AddModel(struct ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback);
		void AddModel(struct ModelData* model, const Matrix4F& transformation, const std::string& selfNode, const std::string& targetNode, const ModelSpawnCallback& callback);
		void SendSkeletonToGpu();
		void SetRigAnimations(const Archive::Metadata::Entry* entry);
		void SetRigAnimations(const std::string& rigName);
		void SetRigAnimations(struct RigAnimationData* rig);

		void SetRigNodeTransform(size_t index, const Matrix4F& transformation);

		void ReleaseResources();

		void CreateRigDebugMesh();
		void UpdateRigDebugMesh();

		virtual bool HasChanged() const override;
		virtual void MarkStale(bool isStale) override;

		size_t GetRigVersion() const { return RigVersion; }
		const auto& GetRigNodes() const { return RigNodes; }
		const auto& GetMeshNodes() const { return MeshNodes; }
		const auto& GetNodeIndices() const { return NodeIndices; }
		const auto& GetSkeletonBuffer() const { return SkeletonBuffer; }
		const auto& GetModels() const { return Models; }
		const auto& GetAssetLibrary() const { return AssetLibrary; }
		auto* GetAnimationPlayer() const { return AnimationPlayer.get(); }
		auto* GetRigAnimations() const { return RigAnimations; }

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
		std::vector<RigNode> MeshNodes;
		std::vector<SkinnedModelEntry> Models;
		std::unordered_map<std::string, size_t> NodeIndices;
		std::unordered_map<std::string, size_t> MeshNodeIndices;
		SpawningData* SpawnParameters = nullptr;
		struct RigAnimationData* RigAnimations = nullptr;
		bool SkeletonDataIsStale = false;
		size_t LastSkeletonDataSize = 0;
		nvvk::Buffer SkeletonBuffer;
		size_t RigVersion = 0;

		std::vector<VertexPosBinding> WireframeVertices;
		std::vector<int> WireframeIndices;
		std::unordered_map<size_t, size_t> WireframeBoneMap;
		uint32_t WireframeId = (uint32_t)-1;

		std::unique_ptr<AnimationPlayer> AnimationPlayer;

		void ComputeWireframe();
		void AddModels(MapLoader::ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback, size_t parentIndex = (size_t)-1);
		void ComputeRigNodeTransform(RigNode& rigNode);
		void ComputeBaseRigNodeTransform(MapLoader::ModelData* model, const Matrix4F& transformation, RigNode& rigNode, size_t parentIndex, size_t modelIndex);
		size_t AddNode(std::vector<RigNode>& nodes, std::unordered_map<std::string, size_t>& nodeIndices, const std::string& name, bool& isNew);
		bool AddRigNode(MapLoader::ModelData* model, const Matrix4F& transformation, size_t parentIndex, size_t modelIndex);
		bool AddMeshNode(MapLoader::ModelData* model, const Matrix4F& transformation, size_t parentIndex, size_t modelIndex);
		void AddRigNodes(MapLoader::ModelData* model, const Matrix4F& transformation, size_t parentIndex);
		bool SpawnModelCallback(ModelSpawnParameters& spawnParameters);
		void UpdateRig();
	};
}