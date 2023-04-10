#include "SkinnedModel.h"

#include <MapLoader/Scene/RTScene.h>
#include <MapLoader/Assets/ModelLibrary.h>
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

		AssetLibrary->GetModels().SpawnModel(Scene.get(), model, modelTransformation * transformation, spawnCallback);

		SpawnParameters = nullptr;
	}

	void SkinnedModel::AddRigNodes(MapLoader::ModelData* model, const Matrix4F& transformation, const std::string& selfNode, size_t parentIndex)
	{
		for (size_t i = 0; i < model->Nodes.size(); ++i)
		{
			const auto& node = model->Nodes[i];

			if (NodeIndices.contains(node.Name)) continue;

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

			rigNode.BaseTransform = rigNode.Transformation.Inverted();

			if (node.IsInBoneList)
			{
				SkeletonDataIsStale = true;

				rigNode.SkeletonIndex = SkeletonData.size();
				SkeletonData.push_back(rigNode.Transformation);
			}
		}
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

			std::vector<unsigned char> meshBoneIndices(modelNode.Bones.size());

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

			skinnedMesh.VertexPosOverride = VulkanContext->Allocator.createBuffer(cmdBuf, vertices, usageFlags);

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

	void SkinnedModel::CreateRigDebugMesh(ModelLibrary& modelLibrary)
	{
		std::vector<VertexPosBinding> vertices;
		std::vector<int> indices;
		std::unordered_map<size_t, size_t> boneMap;

		for (size_t i = 0; i < RigNodes.size(); ++i)
		{
			const RigNode& node = RigNodes[i];

			if (!node.IsBone) continue;

			boneMap[i] = vertices.size();
			vertices.push_back({});

			VertexPosBinding& vertex = vertices.back();

			vertex.position = node.Transformation.Translation();
			vertex.color = 0x00FF00FF;

			if (node.ParentIndex != (size_t)-1)
			{
				indices.push_back((int)boneMap[node.ParentIndex]);
				indices.push_back((int)vertices.size() - 1);
			}
		}

		uint32_t id = modelLibrary.LoadWireframeMesh(vertices, indices);

		AssetLibrary->GetModels().SpawnWireframe(Scene.get(), id, GetTransform()->GetWorldTransformation());
	}

	void SkinnedModel::SendSkeletonToGpu()
	{
		if (!SkeletonDataIsStale) return;

		auto cmdGen = nvvk::CommandPool(VulkanContext->Device, VulkanContext->GraphicsQueueIndex);

		for (size_t i = 0; i < RigNodes.size(); ++i)
		{
			auto& rigNode = RigNodes[i];

			if (rigNode.ParentIndex != (size_t)-1)
			{
				rigNode.Transformation = RigNodes[rigNode.ParentIndex].Transformation * rigNode.LocalTransformation;
			}
			else
			{
				rigNode.Transformation = rigNode.LocalTransformation;
			}

			if (rigNode.SkeletonIndex != (size_t)-1)
			{
				SkeletonData[rigNode.SkeletonIndex] = rigNode.Transformation * rigNode.BaseTransform;
			}
		}

		if (SkeletonBuffer.buffer != nullptr && LastSkeletonDataSize != SkeletonData.size())
		{
			VulkanContext->Allocator.destroy(SkeletonBuffer);
		}

		if (SkeletonBuffer.buffer == nullptr)
		{
			VkCommandBuffer cmdBuf = cmdGen.createCommandBuffer();

			VkBufferUsageFlags usageFlags = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

			SkeletonBuffer = VulkanContext->Allocator.createBuffer(cmdBuf, SkeletonData, usageFlags, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			cmdGen.submitAndWait(cmdBuf);
			VulkanContext->Allocator.finalizeAndReleaseStaging();

			return;
		}

		auto     uboUsageStages = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR;

		VkCommandBuffer cmdBuf = cmdGen.createCommandBuffer();
		uint32_t size = sizeof(SkeletonData[0]) * (uint32_t)SkeletonData.size();

		VkBufferMemoryBarrier beforeBarrier{ VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER };
		beforeBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		beforeBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		beforeBarrier.buffer = SkeletonBuffer.buffer;
		beforeBarrier.offset = 0;
		beforeBarrier.size = size;
		vkCmdPipelineBarrier(cmdBuf, uboUsageStages, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_DEPENDENCY_DEVICE_GROUP_BIT, 0,
			nullptr, 1, &beforeBarrier, 0, nullptr);

		vkCmdUpdateBuffer(cmdBuf, SkeletonBuffer.buffer, 0, size, SkeletonData.data());

		VkBufferMemoryBarrier afterBarrier{ VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER };
		afterBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		afterBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		afterBarrier.buffer = SkeletonBuffer.buffer;
		afterBarrier.offset = 0;
		afterBarrier.size = size;
		vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_TRANSFER_BIT, uboUsageStages, VK_DEPENDENCY_DEVICE_GROUP_BIT, 0,
			nullptr, 1, &afterBarrier, 0, nullptr);
	}
}