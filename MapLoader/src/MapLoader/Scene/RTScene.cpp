#include "RTScene.h"

#include <MapLoader/Vulkan/VulkanContext.h>
#include <MapLoader/Assets/SkinnedModel.h>
#include <nvvk/buffers_vk.hpp>

namespace MapLoader
{
	RTScene::RTScene(const std::shared_ptr<Graphics::VulkanContext>& context) : VulkanContext(context)
	{
		
	}

	RTScene::~RTScene()
	{
		for (size_t i = 0; i < StaticObjects.size(); ++i)
		{
			if (StaticObjects[i] != nullptr)
				StaticObjects[i]->RemoveFromScene(this);
		}

		for (size_t i = 0; i < StaticObjects.size(); ++i)
		{
			if (DynamicObjects[i] != nullptr)
				DynamicObjects[i]->RemoveFromScene(this);
		}

		for (size_t i = 0; i < StaticObjects.size(); ++i)
		{
			if (SkinnedModels[i] != nullptr)
				SkinnedModels[i]->RemoveFromScene(this);
		}
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

			object->AddToScene(this, index, SceneObjectType::Static);

			return;
		}

		size_t index = DynamicObjectIds.Allocate(DynamicObjects, object);

		WriteInstance(index, object.get());

		object->AddToScene(this, index, SceneObjectType::Dynamic);
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

	void RTScene::RemoveObject(SceneObject* object)
	{
		size_t index = object->GetSceneIndex(this);

		if (index == (size_t)-1) return;

		RegenerateTLAS = true;

		SceneObjectType type = object->GetObjectType(this);

		if (type == SceneObjectType::None) return;

		if (type == SceneObjectType::Static)
		{
			++RemovedStaticObjects;

			StaticObjectIds.Release(index);
			StaticObjects[index] = nullptr;

			if (index < DynamicObjectOffset)
				AccelStructureInstances[index].mask = 0;

			object->RemoveFromScene(this);

			return;
		}

		if (type == SceneObjectType::Dynamic)
		{
			DynamicObjectIds.Release(index);
			DynamicObjects[index] = nullptr;
			AccelStructureInstances[index + DynamicObjectOffset].mask = 0;

			object->RemoveFromScene(this);

			return;
		}

		if (type == SceneObjectType::Skinned)
		{
			SkinnedObjectIds.Release(index);
			SkinnedModels[index] = nullptr;

			object->RemoveFromScene(this);

			return;
		}
	}

	void RTScene::AddSkinnedModel(const std::shared_ptr<SkinnedModel>& object)
	{
		size_t index = object->GetSceneIndex(this);

		if (index != (size_t)-1) return;

		index = SkinnedObjectIds.Allocate(SkinnedModels, object);

		object->AddToScene(this, index, SceneObjectType::Skinned);
	}

	void RTScene::RemoveSkinnedModel(const std::shared_ptr<SkinnedModel>& object)
	{
		size_t index = object->GetSceneIndex(this);

		if (index == (size_t)-1) return;

		SkinnedObjectIds.Release(index);
		SkinnedModels[index] = nullptr;

		object->RemoveFromScene(this);
	}

	void RTScene::ClearAnimationTasks()
	{
		AnimationTasks.clear();
		MaxAnimatedVertices = 0;
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

		for (size_t i = 0; i < SkinnedModels.size(); ++i)
		{
			const auto& model = SkinnedModels[i];

			if (!model->HasChanged()) continue;

			model->MarkStale(false);
			model->SendSkeletonToGpu();

			const auto& models = model->GetModels();

			const auto& modelLibrary = model->GetAssetLibrary()->GetModels();
			VkDeviceAddress skeletonAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, model->GetSkeletonBuffer().buffer);

			for (size_t j = 0; j < models.size(); ++j)
			{
				const auto& modelEntry = models[j];

				for (size_t k = 0; k < modelEntry.Meshes.size(); ++k)
				{
					const auto& mesh = modelEntry.Meshes[k];

					if (!mesh.HasSkeleton && !mesh.HasMorphAnimation) continue;
					if (mesh.MeshId == (size_t)-1 || mesh.MeshIndex == (size_t)-1) continue;

					uint32_t meshId = modelEntry.Model->GetId(mesh.MeshIndex);

					const auto& gpuMeshInstance = modelLibrary.GetGpuEntityData()[mesh.MeshId];
					const auto& gpuMeshData = modelLibrary.GetGpuData()[meshId];

					AnimationTasks.push_back({});

					auto& animationTask = AnimationTasks.back();
					animationTask.vertices = (int)modelEntry.Model->Nodes[mesh.MeshIndex].Vertices;

					animationTask.vertexPosAddress = gpuMeshData.vertexPosAddress;
					animationTask.vertexBinormalAddress = gpuMeshData.vertexBinormalAddress;
					animationTask.vertexMorphAddress = gpuMeshData.vertexMorphAddress;
					animationTask.vertexBlendAddress = gpuMeshData.vertexBlendAddress;
					animationTask.indexAddress = gpuMeshData.indexAddress;

					animationTask.skeletonAddress = skeletonAddress;
					animationTask.skeletonIndicesAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, mesh.SkeletonSectionIndicesBuffer.buffer);

					animationTask.vertexPosAddressOverride = gpuMeshInstance.vertexPosAddressOverride;
					animationTask.vertexBinormalAddressOverride = gpuMeshInstance.vertexBinormalAddressOverride;

					if (animationTask.vertexBinormalAddress == 0 || animationTask.vertexBinormalAddressOverride == 0)
					{
						animationTask.vertexBinormalAddress = 0;
						animationTask.vertexBinormalAddressOverride = 0;
					}

					MaxAnimatedVertices = std::max(MaxAnimatedVertices, (int)animationTask.vertices);
				}
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