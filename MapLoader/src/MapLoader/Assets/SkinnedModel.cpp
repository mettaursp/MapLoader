#include "SkinnedModel.h"

#include <MapLoader/Scene/RTScene.h>
#include <MapLoader/Assets/ModelLibrary.h>

namespace MapLoader
{
	SkinnedModel::SkinnedModel(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext) : VulkanContext(vulkanContext)
	{

	}

	SkinnedModel::~SkinnedModel()
	{

	}

	void SkinnedModel::SetTransformation(const Matrix4F& transformation)
	{
		Transformation = transformation;
	}

	void SkinnedModel::AddModel(struct ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback)
	{
		AddRigNodes(model, transformation, "");

		Models.push_back({});

		SpawningData parameters
		{
			.Callback = callback,
			.CurrentEntry = Models.back()
		};

		SpawnParameters = &parameters;

		auto spawnCallback = [this](MapLoader::ModelData* model, size_t i, InstDesc& instance)
		{
			return SpawnModelCallback(model, i, instance);
		};

		spawnModel(model, Transformation * transformation, spawnCallback);

		SpawnParameters = nullptr;
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
			std::cout << "rig does not have target node '" << targetNode << "'" << std::endl;

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

		AddRigNodes(model, attachmentTransformation, selfNode, parentRigNode);

		Models.push_back({});

		SpawningData parameters
		{
			.Callback = callback,
			.CurrentEntry = Models.back()
		};

		SpawnParameters = &parameters;

		auto spawnCallback = [this](MapLoader::ModelData* model, size_t i, InstDesc& instance)
		{
			return SpawnModelCallback(model, i, instance);
		};

		spawnModel(model, Transformation * RigNodes[parentRigNode].Transformation * attachmentTransformation, spawnCallback);

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

	bool SkinnedModel::SpawnModelCallback(MapLoader::ModelData* model, size_t i, InstDesc& instance)
	{
		bool doSpawn = SpawnParameters->Callback(model, i, instance);

		if (!doSpawn) return false;

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

		spawnWireframe(id, Transformation);
	}

	void SkinnedModel::UpdateGpuData()
	{
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
	}
}