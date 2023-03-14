#pragma once

#include <functional>
#include <MapLoader/Assets/ModelData.h>
#include <Engine/Math/Matrix4.h>
#include <host_device.h>
#include <Engine/IdentifierHeap.h>
#include <vulkan/vulkan_core.h>
#include "SceneObject.h"
#include "nvvk/raytraceKHR_vk.hpp"

struct SpawnedEntity;
typedef std::function<bool(MapLoader::ModelData*, size_t, InstDesc&)> ModelSpawnCallback;

SpawnedEntity* spawnModel(MapLoader::ModelData* model, const Matrix4F& transform = Matrix4F(), const ModelSpawnCallback& callback = nullptr);

namespace Graphics
{
	class VulkanContext;
}

namespace MapLoader
{
	class RTScene
	{
	public:
		RTScene(const std::shared_ptr<Graphics::VulkanContext>& context);

		void Initialize();
		void FreeResources();
		void Update(float);
		void AddObject(const std::shared_ptr<SceneObject>& object);
		void RemoveObject(const std::shared_ptr<SceneObject>& object);
		nvvk::RaytracingBuilderKHR& GetRTBuilder() { return RTBuilder; }

	private:
		std::shared_ptr<Graphics::VulkanContext> VulkanContext;
		bool RegenerateTLAS = false;
		size_t AddedStaticObjects = 0;
		size_t RemovedStaticObjects = 0;
		size_t DynamicObjectOffset = 0;
		IDHeap DynamicObjectIds;
		IDHeap StaticObjectIds;
		std::vector<VkAccelerationStructureInstanceKHR> AccelStructureInstances;
		std::vector<std::shared_ptr<SceneObject>> StaticObjects;
		std::vector<std::shared_ptr<SceneObject>> DynamicObjects;
		nvvk::RaytracingBuilderKHR RTBuilder;

		void WriteInstance(size_t index, SceneObject* sceneObject);
		void UpdateInstance(size_t index, SceneObject* sceneObject);
	};
}