#include "RTScene.h"

#include <MapLoader/Vulkan/VulkanContext.h>

namespace MapLoader
{
	RTScene::RTScene(const std::shared_ptr<Graphics::VulkanContext>& context) : VulkanContext(context)
	{
		
	}

	void RTScene::FreeResources()
	{
		RTBuilder.destroy();
	}

	void RTScene::Initialize()
	{
		RTBuilder.setup(VulkanContext->Device, &VulkanContext->Allocator, VulkanContext->GraphicsQueueIndex);
	}

	void RTScene::AddObject(const std::shared_ptr<SceneObject>& object)
	{
		if (object->GetSceneIndex(this) != (size_t)-1) return;

		RegenerateTLAS = true;

		if (object->IsStatic())
		{
			++AddedStaticObjects;

			size_t index = StaticObjectIds.Allocate(StaticObjects, object);

			object->AddToScene(this, index);

			return;
		}

		size_t index = DynamicObjectIds.Allocate(DynamicObjects, object);

		WriteInstance(index, object.get());

		object->AddToScene(this, index);
	}

	void RTScene::RemoveObject(const std::shared_ptr<SceneObject>& object)
	{
		size_t index = object->GetSceneIndex(this);

		if (index == (size_t)-1) return;

		RegenerateTLAS = true;

		if (object->IsStatic())
		{
			++RemovedStaticObjects;

			StaticObjectIds.Release(index);
			StaticObjects[index] = nullptr;

			if (index < DynamicObjectOffset)
				AccelStructureInstances[index].mask = 0;

			object->RemoveFromScene(this);

			return;
		}

		DynamicObjectIds.Release(index);
		DynamicObjects[index] = nullptr;
		AccelStructureInstances[index + DynamicObjectOffset].mask = 0;

		object->RemoveFromScene(this);
	}

	void RTScene::Update(float)
	{
		bool updateStaticObjects = false;

		if (AddedStaticObjects != 0 || RemovedStaticObjects != 0)
		{
			if (RemovedStaticObjects > AddedStaticObjects)
			{
				size_t removed = 0;

				for (size_t i = 0; i < StaticObjects.size(); ++i)
				{
					if (StaticObjects[i] != nullptr)
						StaticObjects[i - removed] = StaticObjects[i];
					else
						++removed;
				}

				StaticObjects.resize(StaticObjects.size() - removed);
				StaticObjectIds.ShrinkToAllocated();
			}

			long long offset = (long long)AddedStaticObjects - (long long)RemovedStaticObjects;

			if (offset != 0)
			{
				if (offset > 0)
				{
					AccelStructureInstances.resize(AccelStructureInstances.size() + offset);
				}

				size_t start = offset < 0 ? 0 : DynamicObjects.size() - 1;
				long long increment = offset < 0 ? 1 : -1;

				for (size_t i = start; i < DynamicObjects.size(); i += increment)
				{
					AccelStructureInstances[DynamicObjectOffset + i + offset] = AccelStructureInstances[DynamicObjectOffset + i];
				}

				if (offset < 0)
				{
					AccelStructureInstances.resize(AccelStructureInstances.size() + offset);
				}

				DynamicObjectOffset += offset;
			}

			for (size_t i = 0; i < StaticObjects.size(); ++i)
				WriteInstance(i, StaticObjects[i].get());
		}
		else
		{
			for (size_t i = 0; i < StaticObjects.size(); ++i)
			{
				if (StaticObjects[i]->HasChanged())
				{
					updateStaticObjects = true;

					UpdateInstance(i, StaticObjects[i].get());
				}
			}
		}

		bool updateDynamicObjects = false;

		for (size_t i = 0; i < DynamicObjects.size(); ++i)
		{
			if (DynamicObjects[i]->HasChanged())
			{
				updateDynamicObjects = true;

				UpdateInstance(i, DynamicObjects[i].get());
			}
		}

		if (RegenerateTLAS || updateStaticObjects || updateDynamicObjects)
		{
			RTBuilder.buildTlas(AccelStructureInstances, VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR, !RegenerateTLAS);
		}
	}

	void RTScene::WriteInstance(size_t index, SceneObject* sceneObject)
	{
		int32_t modelIndex = sceneObject->GetModelId();

		VkAccelerationStructureInstanceKHR& instance = AccelStructureInstances[index];
		instance.transform = nvvk::toTransformMatrixKHR(sceneObject->GetTransform()->GetWorldTransformation());
		instance.instanceCustomIndex = modelIndex;
		instance.accelerationStructureReference = RTBuilder.getBlasDeviceAddress(modelIndex);
		instance.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;
		instance.mask = sceneObject->GetVisibilityTypeBit();
		instance.instanceShaderBindingTableRecordOffset = 0;
	}

	void RTScene::UpdateInstance(size_t index, SceneObject* sceneObject)
	{
		VkAccelerationStructureInstanceKHR& instance = AccelStructureInstances[index];
		instance.transform = nvvk::toTransformMatrixKHR(sceneObject->GetTransform()->GetWorldTransformation());  // Position of the instance
	}
}