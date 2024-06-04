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

	void SkinnedModel::AddModel(struct ModelData* model, const Matrix4F& transformation, const std::string& selfNode, const std::string& targetNode, const ModelSpawnCallback& callback, float morphWeight)
	{
		bool selfMatchesTarget = selfNode == targetNode;
		size_t parentRigNode = (size_t)-1;
		size_t parentModelNode = (size_t)-1;

		if (!selfMatchesTarget)
		{
			auto parentRigNodeIndex = NodeIndices.find(targetNode);

			if (parentRigNodeIndex == NodeIndices.end())
			{
				std::cout << "rig does not have target node '" << targetNode << "' while adding model '" << model->Entry->Name << "'" << std::endl;
			}
			else
				parentRigNode = parentRigNodeIndex->second;
		}
		else
		{
			for (size_t i = 0; i < MeshNodes.size(); ++i)
			{
				const auto& meshNode = MeshNodes[i];
				if (selfNode == meshNode.Name.substr(0, selfNode.size()))
				{
					if (meshNode.ParentIndex == (size_t)-1 || (parentRigNode != (size_t)-1 && meshNode.ParentIndex != parentRigNode))
					{
						std::cout << "sibling node doesnt match parent: " << selfNode << std::endl;
					}

					parentRigNode = meshNode.ParentIndex;
				}
			}
		}

		for (size_t i = 0; i < model->Nodes.size() && parentModelNode == (size_t)-1; ++i)
			if (selfNode == model->Nodes[i].Name.substr(0, selfNode.size()))
				parentModelNode = model->Nodes[i].AttachedTo;

		if (parentModelNode == (size_t)-1)
			parentModelNode = 0;

		AddModels(model, transformation, callback, parentRigNode, parentModelNode, morphWeight);
	}

	void SkinnedModel::AddModels(MapLoader::ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback, size_t parentIndex, size_t parentModelIndex, float morphWeight)
	{
		SkeletonDataIsStale = true;
		MarkStale(true);

		AddRigNodes(model, transformation, parentIndex, parentModelIndex);

		Models.push_back({ model });

		SpawningData parameters
		{
			.Callback = callback,
			.CurrentEntry = Models.back(),
			.CmdGen = nvvk::CommandPool(VulkanContext->Device, VulkanContext->GraphicsQueueIndex),
			.MorphWeight = morphWeight
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

		models.SpawnModel(Scene.get(), model, modelTransformation * transformation, {}, false, {}, spawnCallback);

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

	void SkinnedModel::ComputeRigNodeTransform(RigNode& rigNode)
	{
		if (rigNode.ParentIndex != (size_t)-1)
			rigNode.Transformation = RigNodes[rigNode.ParentIndex].Transformation * rigNode.LocalTransformation;
		else
			rigNode.Transformation = rigNode.LocalTransformation;
	}

	void SkinnedModel::ComputeBaseRigNodeTransform(MapLoader::ModelData* model, const Matrix4F& transformation, RigNode& rigNode, size_t parentIndex, size_t modelIndex, size_t parentModelIndex)
	{
		const auto& node = model->Nodes[modelIndex];

		bool isUnneededSceneRoot = parentIndex != (size_t)-1 && node.AttachedTo == parentModelIndex;

		if (node.AttachedTo != (size_t)-1 && !isUnneededSceneRoot)
		{
			const auto& parentNode = model->Nodes[node.AttachedTo];

			if (NodeAppearances[parentNode.Name] > 1)
			{
				rigNode.ParentIndex = ModelNodeIndices[node.AttachedTo];
			}
			else
			{
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
		}
		else
		{
			rigNode.ParentIndex = parentIndex;
		}

		if (rigNode.ParentIndex != (size_t)-1 && rigNode.ParentIndex != parentIndex)
			rigNode.LocalTransformation = node.LocalTransformation;
		else
			rigNode.LocalTransformation = transformation * node.LocalTransformation;

		rigNode.BaseTransform = rigNode.LocalTransformation;

		ComputeRigNodeTransform(rigNode);

		rigNode.BaseTransformInverse = rigNode.Transformation.Inverted();
	}

	size_t SkinnedModel::AddNode(std::vector<RigNode>& nodes, std::unordered_map<std::string, size_t>& nodeIndices, const std::string& name, bool& isNew)
	{
		auto nodeIndex = nodeIndices.find(name);

		if (nodeIndex != nodeIndices.end())
		{
			isNew = false;

			return nodeIndex->second;
		}

		size_t index = nodes.size();

		nodeIndices[name] = index;
		nodes.push_back({ name });

		isNew = true;

		return index;
	}

	bool SkinnedModel::AddRigNode(MapLoader::ModelData* model, const Matrix4F& transformation, size_t parentIndex, size_t modelIndex, size_t parentModelIndex)
	{
		const auto& node = model->Nodes[modelIndex];

		std::string name = node.Name;
		size_t& appearances = NodeAppearances[name];
		bool firstAppearance = appearances == 0;

		++appearances;

		if (!firstAppearance)
		{
			std::stringstream nameStream;
			nameStream << "[" << appearances << "]: " << name;
			name = nameStream.str();
		}

		bool isNew = false;
		size_t index = AddNode(RigNodes, NodeIndices, name, isNew);

		ModelNodeIndices[modelIndex] = index;

		auto& rigNode = RigNodes[index];

		rigNode.IsBone |= node.IsBone;

		if (node.IsInBoneList && rigNode.SkeletonIndex == (size_t)-1)
		{
			SkeletonDataIsStale = true;

			rigNode.SkeletonIndex = SkeletonData.size();
			SkeletonData.push_back(rigNode.Transformation * rigNode.BaseTransformInverse);
		}

		if (!isNew) return false;

		ComputeBaseRigNodeTransform(model, transformation, rigNode, parentIndex, modelIndex, parentModelIndex);

		return true;
	}

	bool SkinnedModel::AddMeshNode(MapLoader::ModelData* model, const Matrix4F& transformation, size_t parentIndex, size_t modelIndex, size_t parentModelIndex)
	{
		const auto& node = model->Nodes[modelIndex];

		bool isNew = false;
		size_t index = AddNode(MeshNodes, MeshNodeIndices, node.Name, isNew);

		auto& rigNode = MeshNodes[index];

		ComputeBaseRigNodeTransform(model, transformation, rigNode, parentIndex, modelIndex, parentModelIndex);

		return true;
	}

	void SkinnedModel::AddRigNodes(MapLoader::ModelData* model, const Matrix4F& transformation, size_t parentIndex, size_t parentModelIndex)
	{
		bool changedMappings = false;

		NodeAppearances.clear();
		ModelNodeIndices.clear();

		for (size_t i = 0; i < model->Nodes.size(); ++i)
		{
			bool canGenerate = parentIndex == (size_t)-1;

			for (size_t node = model->Nodes[i].AttachedTo; node != (size_t)-1 && !canGenerate; node = model->Nodes[node].AttachedTo)
				canGenerate = node == parentModelIndex;

			if (!canGenerate) continue;

			const auto& node = model->Nodes[i];

			if (node.MeshId != (size_t)-1)
				changedMappings |= AddMeshNode(model, transformation, parentIndex, i, parentModelIndex);
			else
				changedMappings |= AddRigNode(model, transformation, parentIndex, i, parentModelIndex);
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
		skinnedMesh.MorphWeight = SpawnParameters->MorphWeight;
		spawnParameters.NewInstance.morphWeight = SpawnParameters->MorphWeight;

		auto& modelNode = spawnParameters.Model->Nodes[spawnParameters.MeshIndex];

		skinnedMesh.HasSkeleton = modelNode.Bones.size() > 0;
		skinnedMesh.HasMorphAnimation = modelNode.Mesh != nullptr && modelNode.Mesh->GetFormat()->GetAttribute("morphpos") != nullptr;
		skinnedMesh.MeshNodeIndex = MeshNodeIndices[modelNode.Name];

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

			spawnParameters.NewInstance.vertexPosAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, skinnedMesh.VertexPosOverride.buffer);
		}

		{
			VkCommandBuffer cmdBuf = SpawnParameters->CmdGen.createCommandBuffer();
			std::vector<VertexBinormalBinding> vertices(spawnParameters.VertexCount);

			skinnedMesh.VertexBinormalOverride = VulkanContext->Allocator.createBuffer(cmdBuf, vertices, usageFlags);

			SpawnParameters->CmdGen.submitAndWait(cmdBuf);
			VulkanContext->Allocator.finalizeAndReleaseStaging();

			spawnParameters.NewInstance.vertexBinormalAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, skinnedMesh.VertexBinormalOverride.buffer);
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

			ComputeRigNodeTransform(node);

			if (node.SkeletonIndex != (size_t)-1)
			{
				SkeletonData[node.SkeletonIndex] = node.Transformation * node.BaseTransformInverse;
				node.SkeletonIndex += 0;
			}
		}

		for (size_t i = 0; i < MeshNodes.size(); ++i)
		{
			RigNode& node = MeshNodes[i];

			if (node.ParentIndex != (size_t)-1 && RigNodes[node.ParentIndex].IsStale)
				node.IsStale = true;

			if (!node.IsStale) continue;

			ComputeRigNodeTransform(node);
		}

		for (size_t i = 0; i < RigNodes.size(); ++i)
		{
			RigNodes[i].IsStale = false;
		}

		for (size_t i = 0; i < MeshNodes.size(); ++i)
		{
			MeshNodes[i].IsStale = false;
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