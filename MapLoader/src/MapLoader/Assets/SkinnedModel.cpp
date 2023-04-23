#include "SkinnedModel.h"

#include <MapLoader/Scene/RTScene.h>
#include <MapLoader/Assets/ModelLibrary.h>
#include <MapLoader/Scene/AnimationPlayer.h>
#include <MapLoader/Assets/RigAnimationData.h>
#include <nvvk/buffers_vk.hpp>

namespace MapLoader
{
	SkinnedModel::SkinnedModel(const std::shared_ptr<GameAssetLibrary>& assetLibrary, const std::shared_ptr<RTScene>& scene) : AssetLibrary(assetLibrary), Scene(scene)
	{
		VulkanContext = AssetLibrary->GetVulkanContext();
	}

	SkinnedModel::~SkinnedModel()
	{
		ReleaseResources();
	}

	void SkinnedModel::ReleaseResources()
	{
		for (size_t i = 0; i < Models.size(); ++i)
		{
			for (size_t j = 0; j < Models[i].Meshes.size(); ++j)
			{
				auto& skinnedMesh = Models[i].Meshes[j];

				if (skinnedMesh.SkeletonSectionIndicesBuffer.buffer != nullptr)
					VulkanContext->Allocator.destroy(skinnedMesh.SkeletonSectionIndicesBuffer);

				if (skinnedMesh.VertexPosOverride.buffer != nullptr)
					VulkanContext->Allocator.destroy(skinnedMesh.VertexPosOverride);

				if (skinnedMesh.VertexBinormalOverride.buffer != nullptr)
					VulkanContext->Allocator.destroy(skinnedMesh.VertexBinormalOverride);
			}
		}
		
		if (SkeletonBuffer.buffer != nullptr)
		{
			VulkanContext->Allocator.destroy(SkeletonBuffer);
		}
	}

	void SkinnedModel::AddModel(struct ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback)
	{
		AddModels(model, transformation, callback);
	}

	void SkinnedModel::AddModel(struct ModelData* model, const Matrix4F& transformation, const std::string& selfNode, const std::string& targetNode, const ModelSpawnCallback& callback)
	{
		auto parentRigNodeIndex = NodeIndices.find(targetNode);
		size_t parentRigNode = (size_t)-1;

		if (parentRigNodeIndex == NodeIndices.end())
		{
			if (selfNode == targetNode)
			{
				parentRigNode = 0;
			}
		}
		else
		{
			parentRigNode = parentRigNodeIndex->second;
		}

		if (parentRigNode == (size_t)-1)
		{
			std::cout << "rig does not have target node '" << targetNode << "' while adding model '" << model->Entry->Name << "'" << std::endl;

			return;
		}

		Matrix4F attachmentTransformation = transformation;
		bool failedToAttachNode = false;

		if (selfNode == targetNode)
		{
			failedToAttachNode = true;

			for (size_t i = 0; i < model->Nodes.size(); ++i)
			{
				if (selfNode == model->Nodes[i].Name.substr(0, selfNode.size()))
				{
					attachmentTransformation = transformation * model->Nodes[i].Transformation.Inverted();
					failedToAttachNode = false;
			
					break;
				}
			}
		}

		if (failedToAttachNode)
		{
			std::cout << "asset '" << model->Entry->Name << "' does not have self node '" << selfNode << "'" << std::endl;

			return;
		}

		AddModels(model, attachmentTransformation, callback, selfNode, parentRigNode);
	}

	void SkinnedModel::AddModels(MapLoader::ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback, const std::string& selfNode, size_t parentIndex)
	{
		SkeletonDataIsStale = true;
		MarkStale(true);

		AddRigNodes(model, transformation, selfNode, parentIndex);

		Models.push_back({ model });

		SpawningData parameters
		{
			.Callback = callback,
			.CurrentEntry = Models.back(),
			.CmdGen = nvvk::CommandPool(VulkanContext->Device, VulkanContext->GraphicsQueueIndex)
		};

		SpawnParameters = &parameters;

		auto spawnCallback = [this](ModelSpawnParameters& spawnParameters)
		{
			return SpawnModelCallback(spawnParameters);
		};

		Matrix4F modelTransformation = GetTransform()->GetWorldTransformation();

		if (parentIndex != (size_t)-1)
			modelTransformation *= RigNodes[parentIndex].Transformation;

		auto& models = AssetLibrary->GetModels();

		models.SpawnModel(Scene.get(), model, modelTransformation * transformation, spawnCallback);

		for (size_t i = 0; i < Models.size(); ++i)
		{
			for (size_t j = 0; j < Models[i].Meshes.size(); ++j)
			{
				auto& skinnedMesh = Models[i].Meshes[j];

				if (skinnedMesh.BlasInstanceId != (size_t)-1) continue;

				skinnedMesh.BlasInstanceId = models.GetSpawnedModels()[skinnedMesh.MeshId].BlasInstanceId;
			}
		}

		SpawnParameters = nullptr;
	}

	void SkinnedModel::AddRigNodes(MapLoader::ModelData* model, const Matrix4F& transformation, const std::string& selfNode, size_t parentIndex)
	{
		bool changedMappings = false;

		for (size_t i = 0; i < model->Nodes.size(); ++i)
		{
			const auto& node = model->Nodes[i];

			if (NodeIndices.contains(node.Name)) continue;

			changedMappings = true;

			NodeIndices[node.Name] = RigNodes.size();
			RigNodes.push_back({});

			auto& rigNode = RigNodes.back();

			if (node.AttachedTo != (size_t)-1 && node.Name != selfNode)
			{
				const auto& parentNode = model->Nodes[node.AttachedTo];
				auto parentRigNodeIndex = NodeIndices.find(parentNode.Name);

				if (parentRigNodeIndex == NodeIndices.end())
				{
					std::cout << "model '" << model->Entry->Name << "' node '" << node.Name << "' claims to have parent node '" << parentNode.Name << "' which was not registered in rig" << std::endl;
				}
				else
				{
					rigNode.ParentIndex = parentRigNodeIndex->second;
				}
			}
			else if (parentIndex != (size_t)-1)
			{
				rigNode.ParentIndex = parentIndex;
			}

			rigNode.IsBone = node.IsBone;

			if (rigNode.ParentIndex != (size_t)-1)
			{
				rigNode.LocalTransformation = node.LocalTransformation;
				rigNode.Transformation = RigNodes[rigNode.ParentIndex].Transformation * rigNode.LocalTransformation;
			}
			else
			{
				rigNode.LocalTransformation = node.LocalTransformation * transformation;
				rigNode.Transformation = rigNode.LocalTransformation;
			}

			rigNode.BaseTransform = rigNode.LocalTransformation;
			rigNode.BaseTransformInverse = rigNode.Transformation.Inverted();

			if (node.IsInBoneList)
			{
				SkeletonDataIsStale = true;

				rigNode.SkeletonIndex = SkeletonData.size();
				SkeletonData.push_back(rigNode.Transformation * rigNode.BaseTransformInverse);
			}
		}

		if (changedMappings)
			++RigVersion;
	}

	bool SkinnedModel::SpawnModelCallback(ModelSpawnParameters& spawnParameters)
	{
		bool doSpawn = SpawnParameters->Callback(spawnParameters);

		if (!doSpawn) return false;

		SpawnParameters->CurrentEntry.Meshes.push_back({});
		auto& skinnedMesh = SpawnParameters->CurrentEntry.Meshes.back();

		skinnedMesh.MeshIndex = spawnParameters.MeshIndex;
		skinnedMesh.MeshId = spawnParameters.MeshId;

		auto& modelNode = spawnParameters.Model->Nodes[spawnParameters.MeshIndex];

		skinnedMesh.HasSkeleton = modelNode.Bones.size() > 0;
		skinnedMesh.HasMorphAnimation = modelNode.Mesh != nullptr && modelNode.Mesh->GetFormat()->GetAttribute("morphpos") != nullptr;

		if (!skinnedMesh.HasSkeleton && !skinnedMesh.HasMorphAnimation) return true;

		VkBufferUsageFlags usageFlags = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

		if (skinnedMesh.HasSkeleton)
		{
			VkCommandBuffer cmdBuf = SpawnParameters->CmdGen.createCommandBuffer();

			std::vector<unsigned char> meshBoneIndices;
			meshBoneIndices.reserve(modelNode.Bones.size());

			for (size_t i = 0; i < modelNode.Bones.size(); ++i)
			{
				size_t boneIndex = spawnParameters.Model->BoneIndices[modelNode.Bones[i]];
				const std::string& boneName = spawnParameters.Model->Nodes[boneIndex].Name;

				auto nodeIndex = NodeIndices.find(boneName);

				if (nodeIndex == NodeIndices.end())
				{
					std::cout << "mesh #" << spawnParameters.MeshIndex << " '" << modelNode.Name << "' in model '" << spawnParameters.Model->Entry->Name << "' bone #" << i << " '" << boneName << "' couldn't be found in rig\n";

					meshBoneIndices.push_back(0);

					continue;
				}

				const auto& rigNode = RigNodes[nodeIndex->second];

				if (rigNode.SkeletonIndex == (size_t)-1)
				{
					std::cout << "mesh #" << spawnParameters.MeshIndex << " '" << modelNode.Name << "' in model '" << spawnParameters.Model->Entry->Name << "' bone #" << i << " '" << boneName << "' isn't mapped to skeleton index\n";

					meshBoneIndices.push_back(0);

					continue;
				}

				meshBoneIndices.push_back((unsigned char)rigNode.SkeletonIndex);
			}

			skinnedMesh.SkeletonSectionIndicesBuffer = VulkanContext->Allocator.createBuffer(cmdBuf, meshBoneIndices, usageFlags | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			SpawnParameters->CmdGen.submitAndWait(cmdBuf);
			VulkanContext->Allocator.finalizeAndReleaseStaging();
		}

		{
			VkCommandBuffer cmdBuf = SpawnParameters->CmdGen.createCommandBuffer();
			std::vector<VertexPosBinding> vertices(spawnParameters.VertexCount);

			skinnedMesh.VertexPosOverride = VulkanContext->Allocator.createBuffer(cmdBuf, vertices, usageFlags | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR);

			SpawnParameters->CmdGen.submitAndWait(cmdBuf);
			VulkanContext->Allocator.finalizeAndReleaseStaging();

			spawnParameters.NewInstance.vertexPosAddressOverride = nvvk::getBufferDeviceAddress(VulkanContext->Device, skinnedMesh.VertexPosOverride.buffer);
		}

		{
			VkCommandBuffer cmdBuf = SpawnParameters->CmdGen.createCommandBuffer();
			std::vector<VertexBinormalBinding> vertices(spawnParameters.VertexCount);

			skinnedMesh.VertexBinormalOverride = VulkanContext->Allocator.createBuffer(cmdBuf, vertices, usageFlags);

			SpawnParameters->CmdGen.submitAndWait(cmdBuf);
			VulkanContext->Allocator.finalizeAndReleaseStaging();

			spawnParameters.NewInstance.vertexBinormalAddressOverride = nvvk::getBufferDeviceAddress(VulkanContext->Device, skinnedMesh.VertexBinormalOverride.buffer);
		}

		return true;
	}

	void SkinnedModel::ComputeWireframe()
	{
		WireframeVertices.clear();
		WireframeIndices.clear();
		WireframeBoneMap.clear();

		for (size_t i = 0; i < RigNodes.size(); ++i)
		{
			const RigNode& node = RigNodes[i];

			if (!node.IsBone) continue;

			WireframeBoneMap[i] = WireframeVertices.size();
			WireframeVertices.push_back({});

			VertexPosBinding& vertex = WireframeVertices.back();
			
			Vector3SF translation = node.Transformation.Translation();

			vertex.position = translation;
			vertex.color = 0x00FF00FF;

			if (node.ParentIndex != (size_t)-1)
			{
				WireframeIndices.push_back((int)WireframeBoneMap[node.ParentIndex]);
				WireframeIndices.push_back((int)WireframeVertices.size() - 1);
			}

			size_t loopStart = WireframeVertices.size();
			const size_t count = 8;
			const float handleSize = 3.f;

			Vector3SF right = node.Transformation.RightVector();
			Vector3SF up = node.Transformation.UpVector();
			Vector3SF front = node.Transformation.FrontVector();

			for (size_t i = 0; i < count; ++i)
			{
				WireframeIndices.push_back((int)(loopStart + ((i + 1 + count) % count)));
				WireframeIndices.push_back((int)(loopStart + i));

				WireframeVertices.push_back({});

				VertexPosBinding& vertex = WireframeVertices.back();

				float angle = 2 * PI * ((float)i / (float)count);

				vertex.position = translation + handleSize * std::cosf(angle) * up + handleSize * std::sinf(angle) * front;
				vertex.color = 0x0000FFFF;
			}

			WireframeIndices.push_back((int)WireframeVertices.size());
			WireframeIndices.push_back((int)WireframeVertices.size() + 1);

			WireframeVertices.push_back({});

			{
				VertexPosBinding& vertex = WireframeVertices.back();

				float angle = 2 * PI * ((float)i / (float)count);

				vertex.position = translation;
				vertex.color = 0xFF0000FF;
			}

			WireframeVertices.push_back({});

			{
				VertexPosBinding& vertex = WireframeVertices.back();

				float angle = 2 * PI * ((float)i / (float)count);

				vertex.position = translation + handleSize * right;
				vertex.color = 0xFF0000FF;
			}
		}
	}

	void SkinnedModel::CreateRigDebugMesh()
	{
		ComputeWireframe();

		WireframeId = AssetLibrary->GetModels().LoadWireframeMesh(WireframeVertices, WireframeIndices);

		AssetLibrary->GetModels().SpawnWireframe(Scene.get(), WireframeId, GetTransform()->GetWorldTransformation());
	}

	void SkinnedModel::UpdateRigDebugMesh()
	{
		if (WireframeId == (uint32_t)-1) return;

		ComputeWireframe();

		AssetLibrary->GetModels().UpdateWireframeMesh(WireframeId, WireframeVertices, WireframeIndices);
	}

	bool SkinnedModel::HasChanged() const
	{
		return SkeletonDataIsStale || SceneObject::HasChanged();
	}

	void SkinnedModel::MarkStale(bool isStale)
	{
		SkeletonDataIsStale = isStale;
		SceneObject::MarkStale(isStale);
	}

	void SkinnedModel::SendSkeletonToGpu()
	{
		if (!SkeletonDataIsStale) return;

		auto cmdGen = nvvk::CommandPool(VulkanContext->Device, VulkanContext->GraphicsQueueIndex);

		UpdateRig();

		if (SkeletonBuffer.buffer != nullptr && LastSkeletonDataSize != SkeletonData.size())
		{
			VulkanContext->Allocator.destroy(SkeletonBuffer);
		}

		if (SkeletonBuffer.buffer == nullptr)
		{
			VkCommandBuffer cmdBuf = cmdGen.createCommandBuffer();

			VkBufferUsageFlags usageFlags = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

			VkMemoryPropertyFlags propertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

			SkeletonBuffer = VulkanContext->Allocator.createBuffer(cmdBuf, SkeletonData, usageFlags, propertyFlags);

			cmdGen.submitAndWait(cmdBuf);
			VulkanContext->Allocator.finalizeAndReleaseStaging();

			LastSkeletonDataSize = SkeletonData.size();

			return;
		}

		uint32_t size = sizeof(SkeletonData[0]) * (uint32_t)SkeletonData.size();

		Matrix4F* skeletonData = reinterpret_cast<Matrix4F*>(VulkanContext->Allocator.map(SkeletonBuffer));
		std::memcpy(skeletonData, SkeletonData.data(), size);
		VulkanContext->Allocator.unmap(SkeletonBuffer);

		SkeletonDataIsStale = false;
	}

	void SkinnedModel::SetRigAnimations(const Archive::Metadata::Entry* entry)
	{
		RigAnimationData* rig = AssetLibrary->GetAnimations().FetchRigAnimations(entry);

		if (rig == nullptr) return;

		SetRigAnimations(rig);
	}

	void SkinnedModel::SetRigAnimations(const std::string& rigName)
	{
		const Archive::Metadata::Entry* rigEntry = Archive::Metadata::Entry::FindFirstEntryByTags(rigName, "gamebryo-animation");

		if (rigEntry == nullptr) return;

		SetRigAnimations(rigEntry);
	}

	void SkinnedModel::SetRigAnimations(RigAnimationData* rig)
	{
		RigAnimations = rig;

		AnimationPlayer = std::make_unique<MapLoader::AnimationPlayer>(AssetLibrary);
		AnimationPlayer->SetRig(this);
	}

	void SkinnedModel::UpdateRig()
	{
		if (!SkeletonDataIsStale) return;

		for (size_t i = 0; i < RigNodes.size(); ++i)
		{
			RigNode& node = RigNodes[i];

			if (node.ParentIndex != (size_t)-1 && RigNodes[node.ParentIndex].IsStale)
				node.IsStale = true;

			if (!node.IsStale) continue;

			if (node.ParentIndex != (size_t)-1)
			{
				RigNode& parent = RigNodes[node.ParentIndex];

				node.Transformation = parent.Transformation * node.LocalTransformation;
			}
			else
				node.Transformation = node.LocalTransformation;

			if (node.SkeletonIndex != (size_t)-1)
			{
				SkeletonData[node.SkeletonIndex] = node.Transformation * node.BaseTransformInverse;
				node.SkeletonIndex += 0;
			}
		}

		for (size_t i = 0; i < RigNodes.size(); ++i)
		{
			RigNodes[i].IsStale = false;
		}
	}

	void SkinnedModel::SetRigNodeTransform(size_t index, const Matrix4F& transformation)
	{
		if (index >= RigNodes.size()) return;

		RigNodes[index].LocalTransformation = transformation;
		RigNodes[index].IsStale = true;

		SkeletonDataIsStale = true;
	}
}