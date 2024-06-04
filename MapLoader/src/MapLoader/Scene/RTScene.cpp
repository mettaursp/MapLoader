#include "RTScene.h"

#include <MapLoader/Assets/GameAssetLibrary.h>
#include <MapLoader/Vulkan/VulkanContext.h>
#include <MapLoader/Assets/SkinnedModel.h>
#include <MapLoader/Scene/AnimationPlayer.h>
#include <nvvk/buffers_vk.hpp>

namespace MapLoader
{
	RTScene::RTScene(const std::shared_ptr<GameAssetLibrary>& assetLibrary) : AssetLibrary(assetLibrary), VulkanContext(AssetLibrary->GetVulkanContext())
	{
		
	}

	RTScene::~RTScene()
	{
		for (size_t i = 0; i < Entries.size(); ++i)
		{
			if (Entries[i].Object != nullptr)
				Entries[i].Object->RemoveFromScene(this);
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

		AddObject(object, object->IsStatic() ? SceneObjectType::Static : SceneObjectType::Dynamic);
	}

	void RTScene::RemoveObject(const std::shared_ptr<SceneObject>& object)
	{
		size_t id = object->GetSceneId(this);

		if (id == (size_t)-1) return;

		RegenerateTLAS = true;

		RemoveObject(id);
	}

	void RTScene::RemoveObject(SceneObject* object)
	{
		size_t index = object->GetSceneId(this);

		if (index == (size_t)-1) return;

		RegenerateTLAS = true;

		RemoveObject(object->GetSceneId(this));
	}

	void RTScene::AddSkinnedModel(const std::shared_ptr<SkinnedModel>& object)
	{
		size_t index = object->GetSceneId(this);

		if (index != (size_t)-1) return;

		AddObject(object, SceneObjectType::Skinned, (size_t)-1, object.get());
	}

	void RTScene::RemoveSkinnedModel(const std::shared_ptr<SkinnedModel>& object)
	{
		size_t index = object->GetSceneId(this);

		if (index == (size_t)-1) return;

		RemoveObject(object->GetSceneId(this));
	}

	void RTScene::ClearAnimationTasks()
	{
		AnimationTasks.clear();
		MaxAnimatedVertices = 0;
	}

	void RTScene::ClearStaleBlasIds()
	{
		StaleBlasIds.clear();
	}

	void RTScene::Update(float delta)
	{

		bool regenerateTLAS = ChangedStructureObjects.size() > 0;
		bool rebuildTLAS = AccelStructureInstances.size() != StructureEntries.size();
		size_t rangeMin = (size_t)-1;
		size_t rangeMax = 0;

		const auto& spawnedModels = AssetLibrary->GetModels().GetSpawnedModels();
		const auto& blasInstances = AssetLibrary->GetModels().GetBlasInstances();

		AccelStructureInstances.resize(StructureEntries.size());

		for (size_t i = 0; i < ChangedStructureObjects.size(); ++i)
		{
			size_t index = ChangedStructureObjects[i];

			rangeMin = std::min(rangeMin, index);
			rangeMax = std::max(rangeMax, index);

			if (StructureEntries[index].ObjectId == (size_t)-1)
			{
				AccelStructureInstances[index].mask = 0;

				continue;
			}

			SceneObjectEntry& entry = Entries[StructureEntries[index].ObjectId];

			if (entry.JustAddedToStructure)
				WriteInstance(index, entry.Object.get());
			else
				UpdateInstance(index, entry.Object.get());

			size_t instanceId = entry.Object->GetInstanceId();
			size_t blasInstanceId = spawnedModels[instanceId].BlasInstanceId;

			if (blasInstanceId != (size_t)-1)
			{
				const auto& blasInstance = blasInstances[blasInstanceId];
				OverrideInstanceBlas(index, entry.Object.get(), (uint32_t)blasInstance.blasId);
			}

			entry.JustAddedToStructure = false;
		}

		ChangedStructureObjects.clear();

		if (regenerateTLAS)
		{
			RTBuilder.buildTlas(AccelStructureInstances, VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR, !rebuildTLAS);

			regenerateTLAS = false;
		}
	}

	void RTScene::UpdateAnimations(float delta)
	{
		auto& skinnedModels = EntryTypes[(int)SceneObjectType::Skinned];

		for (size_t i = 0; i < skinnedModels.Entries.size(); ++i)
		{
			if (skinnedModels.Entries[i] == (size_t)-1) continue;

			SceneObjectEntry& entry = Entries[skinnedModels.Entries[i]];

			AnimationPlayer* player = entry.SkinnedModelReference->GetAnimationPlayer();

			if (player != nullptr)
				player->Update(delta);

			const auto& model = entry.SkinnedModelReference;

			if (!model->HasChanged()) continue;

			model->SendSkeletonToGpu();
			entry.SkinnedModelReference->UpdateRigDebugMesh();
			model->MarkStale(false);

			const auto& meshNodes = model->GetMeshNodes();
			const auto& models = model->GetModels();
			const auto& modelLibrary = model->GetAssetLibrary()->GetModels();
			VkDeviceAddress skeletonAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, model->GetSkeletonBuffer().buffer);

			for (size_t j = 0; j < models.size(); ++j)
			{
				const auto& modelEntry = models[j];

				for (size_t k = 0; k < modelEntry.Meshes.size(); ++k)
				{
					const auto& mesh = modelEntry.Meshes[k];

					if (mesh.MeshId == (size_t)-1 || mesh.MeshIndex == (size_t)-1) continue;

					SceneObject* sceneObject = modelLibrary.GetSpawnedModels()[mesh.MeshId].SceneObject.get();

					Matrix4F transformation = modelLibrary.GetCurrentMapTransform() * model->GetTransform()->GetWorldTransformation() * meshNodes[mesh.MeshNodeIndex].Transformation;
					
					sceneObject->GetTransform()->SetTransformation(transformation);
					sceneObject->MarkStale(true);

					size_t entryIndex = sceneObject->GetSceneId(this);
					SceneObjectEntry& entry = Entries[entryIndex];

					ChangedStructureObjects.push_back(entry.StructureIndex);

					if (!mesh.HasSkeleton && !mesh.HasMorphAnimation) continue;

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

					animationTask.morphWeight = gpuMeshInstance.morphWeight;
					animationTask.vertexPosAddressOverride = gpuMeshInstance.vertexPosAddress;
					animationTask.vertexBinormalAddressOverride = gpuMeshInstance.vertexBinormalAddress;

					if (animationTask.vertexBinormalAddress == 0 || animationTask.vertexBinormalAddressOverride == 0)
					{
						animationTask.vertexBinormalAddress = 0;
						animationTask.vertexBinormalAddressOverride = 0;
					}

					MaxAnimatedVertices = std::max(MaxAnimatedVertices, (int)animationTask.vertices);

					StaleBlasIds.push_back(mesh.BlasInstanceId);
				}
			}
		}
	}

	size_t RTScene::AddObject(const std::shared_ptr<SceneObject>& object, SceneObjectType type, size_t id, SkinnedModel* skinnedModel)
	{
		if (id != (size_t)-1) return ChangeType(id, type);

		Engine::Transform* transform = object->GetTransform();

		id = SceneObjectIds.Allocate(Entries, { object, SceneObjectType::None, skinnedModel, transform });
		TransformMap[transform] = id;
		AddTransform(transform);

		object->AddToScene(this, id, (size_t)-1, SceneObjectType::None);

		return ChangeType(id, type);
	}

	void RTScene::EntryList::Remove(size_t index)
	{
		Ids.Release(index);
		Entries[index] = (size_t)-1;
	}

	size_t RTScene::ChangeType(size_t id, SceneObjectType type)
	{
		SceneObjectEntry& entry = Entries[id];

		if (entry.Type == type) return entry.Object->GetSceneIndex(this);

		if (entry.Type != SceneObjectType::None)
		{
			EntryList& entries = EntryTypes[(int)entry.Type];
			entries.Remove(entry.Object->GetSceneIndex(this));
		}

		if (entry.StructureIndex != (size_t)-1 && type != SceneObjectType::Static && type != SceneObjectType::Dynamic)
		{
			size_t structureIndex = entry.StructureIndex;

			StructureIds.Release(structureIndex);
			entry.StructureIndex = (size_t)-1;

			if (!StructureEntries[structureIndex].RegisteredChange)
			{
				ChangedStructureObjects.push_back(structureIndex);
			}

			StructureEntries[structureIndex].RegisteredChange = true;
			StructureEntries[structureIndex].ObjectId = (size_t)-1;
		}

		entry.Type = type;

		if (type == SceneObjectType::None)
		{
			entry.Object->SetObjectType(this, type, (size_t)-1);

			return (size_t)-1;
		}

		if ((type == SceneObjectType::Static || type == SceneObjectType::Dynamic) && entry.StructureIndex == (size_t)-1)
		{
			entry.StructureIndex = StructureIds.RequestID();
			entry.JustAddedToStructure = true;

			if (entry.StructureIndex >= StructureEntries.size())
			{
				StructureEntries.push_back({ id, false });
			}

			if (!StructureEntries[entry.StructureIndex].RegisteredChange)
				ChangedStructureObjects.push_back(entry.StructureIndex);
		}

		EntryList& entries = EntryTypes[(int)entry.Type];

		size_t index = entries.Ids.Allocate(entries.Entries, id);
		
		entry.Object->SetObjectType(this, type, index);

		return index;
	}

	void RTScene::RemoveObject(size_t id)
	{
		SceneObjectEntry& entry = Entries[id];

		if (entry.StructureIndex != (size_t)-1)
		{
			size_t structureIndex = entry.StructureIndex;

			StructureIds.Release(structureIndex);
			entry.StructureIndex = (size_t)-1;

			if (!StructureEntries[structureIndex].RegisteredChange)
			{
				ChangedStructureObjects.push_back(structureIndex);
			}

			StructureEntries[structureIndex].RegisteredChange = true;
			StructureEntries[structureIndex].ObjectId = (size_t)-1;
		}

		if (entry.Type != SceneObjectType::None)
		{
			EntryList& entries = EntryTypes[(int)entry.Type];
			entries.Remove(entry.Object->GetSceneIndex(this));
		}

		SceneObjectIds.Release(id);
		TransformMap.erase(entry.Transform);
		RemoveTransform(entry.Transform);
		entry.Object->RemoveFromScene(this);
		entry = {};
	}

	void RTScene::WriteInstance(size_t index, SceneObject* sceneObject)
	{
		int32_t modelIndex = sceneObject->GetModelId();

		VkGeometryInstanceFlagsKHR flags = 0;

		size_t nodeIndex = sceneObject->GetModelIndex();

		if (nodeIndex != (size_t)-1)
		{
			const ModelNode& node = sceneObject->GetModel()->Nodes[nodeIndex];

			if (!node.HasInvisibility)
				flags |= VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR;
		}

		VkAccelerationStructureInstanceKHR& instance = AccelStructureInstances[index];
		instance.transform = nvvk::toTransformMatrixKHR(sceneObject->GetTransform()->GetWorldTransformation());
		instance.instanceCustomIndex = modelIndex;
		instance.accelerationStructureReference = RTBuilder.getBlasDeviceAddress(modelIndex);
		instance.flags = flags;//VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;
		instance.mask = sceneObject->GetVisibilityFlags();
		instance.instanceShaderBindingTableRecordOffset = 2 * sceneObject->GetShaderType();
	}

	void RTScene::UpdateInstance(size_t index, SceneObject* sceneObject)
	{
		VkAccelerationStructureInstanceKHR& instance = AccelStructureInstances[index];
		instance.transform = nvvk::toTransformMatrixKHR(sceneObject->GetTransform()->GetWorldTransformation());  // Position of the instance
	}

	void RTScene::OverrideInstanceBlas(size_t index, SceneObject* sceneObject, uint32_t blasId)
	{
		VkAccelerationStructureInstanceKHR& instance = AccelStructureInstances[index];
		instance.accelerationStructureReference = RTBuilder.getBlasDeviceAddress(blasId);
	}

	void RTScene::TransformChanged(Engine::Transform* transform, bool firstChange)
	{
		if (!firstChange) return;


	}

	void RTScene::TransformStaticChanged(Engine::Transform* transform, bool isNowStatic)
	{

	}
}