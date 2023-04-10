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

namespace Graphics
{
	class VulkanContext;
}

namespace MapLoader
{
	class SkinnedModel;

	class RTScene
	{
	public:
		RTScene(const std::shared_ptr<Graphics::VulkanContext>& context);
		~RTScene();

		void Initialize();
		void FreeResources();
		void Update(float);
		void AddObject(const std::shared_ptr<SceneObject>& object);
		void RemoveObject(const std::shared_ptr<SceneObject>& object);
		void RemoveObject(SceneObject* object);
		void AddWireframeObject(const std::shared_ptr<SceneObject>& object);
		void RemoveWireframeObject(const std::shared_ptr<SceneObject>& object);
		void AddSkinnedModel(const std::shared_ptr<SkinnedModel>& object);
		void RemoveSkinnedModel(const std::shared_ptr<SkinnedModel>& object);
		nvvk::RaytracingBuilderKHR& GetRTBuilder() { return RTBuilder; }

		void ClearAnimationTasks();

		const auto& GetAnimationTasks() const { return AnimationTasks; }
		int GetMaxAnimatedVertices() const { return MaxAnimatedVertices; }

	private:
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		bool RegenerateTLAS = false;
		size_t AddedStaticObjects = 0;
		size_t RemovedStaticObjects = 0;
		size_t DynamicObjectOffset = 0;
		IDHeap DynamicObjectIds;
		IDHeap StaticObjectIds;
		IDHeap SkinnedObjectIds;
		std::vector<VkAccelerationStructureInstanceKHR> AccelStructureInstances;
		std::vector<std::shared_ptr<SceneObject>> StaticObjects;
		std::vector<std::shared_ptr<SceneObject>> DynamicObjects;
		std::vector<std::shared_ptr<SceneObject>> WireframeObjects;
		std::vector<AnimationTask> AnimationTasks;
		int MaxAnimatedVertices = 0;
		std::vector< std::shared_ptr<SkinnedModel>> SkinnedModels;
		nvvk::RaytracingBuilderKHR RTBuilder;

		void WriteInstance(size_t index, SceneObject* sceneObject);
		void UpdateInstance(size_t index, SceneObject* sceneObject);
	};
}