#pragma once

#include <functional>
#include <MapLoader/Assets/ModelData.h>
#include <Engine/Math/Matrix4.h>
#include <host_device.h>
#include <Engine/IdentifierHeap.h>
#include <vulkan/vulkan_core.h>
#include "SceneObject.h"
#include "nvvk/raytraceKHR_vk.hpp"
#include <host_device.h>
#include <Engine/Objects/Simulation.h>

namespace Graphics
{
	class VulkanContext;
}

namespace MapLoader
{
	class SkinnedModel;
	class GameAssetLibrary;

	class RTScene : public Engine::Simulation
	{
	public:
		RTScene(const std::shared_ptr<GameAssetLibrary>& assetLibrary);
		~RTScene();

		void Initialize();
		void FreeResources();
		void Update(float delta);
		void UpdateAnimations(float delta);
		void AddObject(const std::shared_ptr<SceneObject>& object);
		void RemoveObject(const std::shared_ptr<SceneObject>& object);
		void RemoveObject(SceneObject* object);
		void AddWireframeObject(const std::shared_ptr<SceneObject>& object);
		void RemoveWireframeObject(const std::shared_ptr<SceneObject>& object);
		void AddSkinnedModel(const std::shared_ptr<SkinnedModel>& object);
		void RemoveSkinnedModel(const std::shared_ptr<SkinnedModel>& object);
		nvvk::RaytracingBuilderKHR& GetRTBuilder() { return RTBuilder; }

		void ClearAnimationTasks();
		void ClearStaleBlasIds();

		virtual void TransformChanged(Engine::Transform* transform, bool firstChange) override;
		virtual void TransformStaticChanged(Engine::Transform* transform, bool isNowStatic) override;

		const auto& GetAnimationTasks() const { return AnimationTasks; }
		const auto& GetStaleBlasIds() const { return StaleBlasIds; }
		int GetMaxAnimatedVertices() const { return MaxAnimatedVertices; }

	private:
		struct SceneObjectEntry
		{
			std::shared_ptr<SceneObject> Object;
			SceneObjectType Type = SceneObjectType::None;
			SkinnedModel* SkinnedModelReference = nullptr;
			Engine::Transform* Transform = nullptr;
			size_t ChangedIndex = (size_t)-1;
			size_t StructureIndex = (size_t)-1;
			bool JustAddedToStructure = false;
		};

		struct EntryList
		{
			IDHeap Ids;
			std::vector<size_t> Entries;

			void Remove(size_t index);
		};

		struct StructureEntry
		{
			size_t ObjectId = (size_t)-1;
			bool RegisteredChange = false;
		};

		std::shared_ptr<GameAssetLibrary> AssetLibrary;
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		bool RegenerateTLAS = false;
		IDHeap SceneObjectIds;
		std::vector<VkAccelerationStructureInstanceKHR> AccelStructureInstances;
		EntryList EntryTypes[(int)SceneObjectType::Count] = {};
		std::vector<size_t> ChangedStructureObjects;
		std::vector<StructureEntry> StructureEntries;
		IDHeap StructureIds;
		std::vector<SceneObjectEntry> Entries;
		std::vector<AnimationTask> AnimationTasks;
		int MaxAnimatedVertices = 0;
		nvvk::RaytracingBuilderKHR RTBuilder;
		IDHeap BlasIds;
		std::unordered_map<Engine::Transform*, size_t> TransformMap;
		std::vector<size_t> StaleBlasIds;

		size_t AddObject(const std::shared_ptr<SceneObject>& object, SceneObjectType type, size_t id = (size_t)-1, SkinnedModel* skinnedModel = nullptr);
		size_t ChangeType(size_t id, SceneObjectType type);
		void RemoveObject(size_t id);

		void WriteInstance(size_t index, SceneObject* sceneObject);
		void UpdateInstance(size_t index, SceneObject* sceneObject);
		void OverrideInstanceBlas(size_t index, SceneObject* sceneObject, uint32_t blasId);
	};
}