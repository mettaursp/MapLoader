#include "ModelLibrary.h"

#include <Engine/Math/Color4.h>
#include <Engine/Math/Color4I.h>
#include <Engine/Objects/Transform.h>
#include <Engine/VulkanGraphics/FileFormats/NifParser.h>
#include <ArchiveParser/ParserUtils.h>
#include <tinyobjloader/tiny_obj_loader.h>
#include <MapLoader/hello_vulkan.h>
#include <MapLoader/obj_loader.h>
#include <nvvk/buffers_vk.hpp>
#include <MapLoader/Assets/GameAssetLibrary.h>

namespace MapLoader
{
	const std::unordered_map<std::string, int> ModelLibrary::MaterialTypeMap = {
		{ "MS2StandardMaterial", 0 },
		//{ "MS2ShimmerMaterial", 1 },
		//{ "MS2GlowMaterial", 2 },
		{ "MS2CharacterSkinMaterial", 3 },
		{ "MS2CharacterMaterial", 4 },
		{ "MS2CharacterHairMaterial", 5 },
		{ "MS2GlassMaterial", 6 },
	};

	std::unordered_set<std::string> ModelLibrary::UnmappedMaterials = {};

	ModelData* ModelLibrary::FetchModel(const Archive::Metadata::Entry* entry, bool keepRawData, ModelData* parentRig)
	{
		if (entry == nullptr) return nullptr;

		fs::path filepath = "Resource";
		filepath += entry->RelativePath;

		std::string name = lower(entry->Name);

		const auto& asset = ModelMap.find(entry);

		if (asset != ModelMap.end())
		{
			return Models[asset->second].get();
		}

		ModelMap[entry] = Models.size();
		Models.push_back(std::move(std::make_unique<ModelData>()));

		ModelData& loadedModel = *Models.back();

		loadedModel.Entry = entry;
		loadedModel.Index = (uint32_t)Models.size() - 1;

		FetchModel(AssetLibrary.GetReader()->GetPath(filepath), loadedModel, keepRawData, parentRig);

		return &loadedModel;
	}

	ModelData* ModelLibrary::FindModel(const Archive::Metadata::Entry* entry)
	{
		if (entry == nullptr) return nullptr;

		const auto& asset = ModelMap.find(entry);

		if (asset != ModelMap.end())
		{
			return Models[asset->second].get();
		}

		return nullptr;
	}

	void ModelLibrary::SetCurrentMapTransform(const Matrix4F& mapTransform)
	{
		CurrentMapTransform = mapTransform;
	}

	bool ModelLibrary::FetchModel(const Archive::ArchivePath& file, ModelData& loadedModel, bool keepRawData, ModelData* parentRig)
	{
		if (!file.Loaded())
		{
			std::cout << "failed to load model " << file.GetPath().string() << std::endl;
			return false;
		}

		Engine::Graphics::ModelPackage package;

		NifParser parser;
		parser.Package = &package;
		parser.Name = loadedModel.Entry->RelativePath.string();

		//if (parentRig != nullptr)
		//{
		//	ParentNifTransforms& parentTransforms = parentRig->NodeTransforms;
		//
		//	parser.ParentNodes = &parentTransforms;
		//
		//	if (parentRig->NodeTransforms.size() == 0)
		//	{
		//		parentTransforms.Nodes.resize(parentRig->Nodes.size());
		//
		//		for (size_t i = 0; i < parentRig->Nodes.size(); ++i)
		//		{
		//			parentTransforms.Nodes[i].Name = parentRig->Nodes[i].Name;
		//			parentTransforms.Nodes[i].Transform = parentRig->Nodes[i].LocalTransformation;
		//		}
		//	}
		//}

		file.Read(NifDocumentBuffer);
		parser.Parse(NifDocumentBuffer);

		size_t nodeCount = parser.Package->Nodes.size();

		loadedModel.Animations = std::move(package.Animations);
		loadedModel.Nodes.resize(nodeCount);
		loadedModel.BoneIndices = parser.Package->Bones;

		if (parser.Package->Nodes.size() > 0)
		{
			parser.Package->Nodes[0].Transform->Update(0);
		}

		std::unordered_map<unsigned int, int> formatUseCount;

		for (size_t i = 0; i < parser.Package->Nodes.size(); ++i)
		{
			Engine::Graphics::ModelPackageNode& node = parser.Package->Nodes[i];
			ModelNode& modelNode = loadedModel.Nodes[i];

			modelNode.Name = node.Name;
			modelNode.IsBone = node.IsBone;
			modelNode.IsInBoneList = node.IsInBoneList;
			modelNode.Bones = node.Bones;
			modelNode.AttachedTo = node.AttachedTo;

			if (node.Transform != nullptr)
			{
				modelNode.Transformation = node.Transform->GetWorldTransformation();
				modelNode.LocalTransformation = node.Transform->GetTransformation();
			}

			if (node.Mesh != nullptr)
			{
				if (keepRawData)
					modelNode.Mesh = node.Mesh;

				modelNode.Vertices = node.Mesh->GetVertices();
				modelNode.Indices = node.Mesh->GetIndices();

				MeshBuffers meshBuffers;

				LoadBuffers(meshBuffers, node);
				
				MaterialObj& material = meshBuffers.Material;

				if (node.MaterialIndex != -1)
				{
					const Engine::Graphics::ModelPackageMaterial& packageMaterial = parser.Package->Materials[node.MaterialIndex];

					modelNode.Shader = packageMaterial.ShaderName;
					modelNode.MaterialName = packageMaterial.Name;

					LoadMaterial(meshBuffers.Material, packageMaterial);
				}

				if (node.MaterialIndex == -1)
				{
					i += 0;
				}

				modelNode.Material = meshBuffers.Material;
				modelNode.MeshId = (int)LoadModel(meshBuffers);
			}
		}

		for (const auto& pair : formatUseCount)
		{
			if (pair.second > 1)
				loadedModel.DuplicateFormatUses += pair.second - 1;
		}

		DuplicateFormatUses += loadedModel.DuplicateFormatUses;

		return true;
	}

	ModelLibrary::ModelLibrary(GameAssetLibrary& assetLibrary) : AssetLibrary(assetLibrary)
	{
		std::vector<Engine::Graphics::VertexAttributeFormat> attributes;

		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "position", 0 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 2, "texcoord", 0 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "normal", 0 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::UInt8, 4, "color", 0 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "binormal", 1 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "tangent", 1 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "morphpos", 2 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::UInt8, 4, "blendindices", 3 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 4, "blendweight", 3 });

		MeshFormat = Engine::Graphics::MeshFormat::GetFormat(attributes);
	}

	ModelLibrary::~ModelLibrary()
	{
		FreeResources();
	}

	void ModelLibrary::LoadMaterial(MaterialObj& material, const Engine::Graphics::ModelPackageMaterial& packageMaterial)
	{
		material.diffuse[0] = packageMaterial.DiffuseColor.R;
		material.diffuse[1] = packageMaterial.DiffuseColor.G;
		material.diffuse[2] = packageMaterial.DiffuseColor.B;

		material.specular[0] = packageMaterial.SpecularColor.R;
		material.specular[1] = packageMaterial.SpecularColor.G;
		material.specular[2] = packageMaterial.SpecularColor.B;

		material.ambient[0] = packageMaterial.AmbientColor.R;
		material.ambient[1] = packageMaterial.AmbientColor.G;
		material.ambient[2] = packageMaterial.AmbientColor.B;

		material.emission[0] = packageMaterial.EmissiveColor.R;
		material.emission[1] = packageMaterial.EmissiveColor.G;
		material.emission[2] = packageMaterial.EmissiveColor.B;

		material.shininess = packageMaterial.Shininess;
		material.dissolve = packageMaterial.Alpha;
		material.colorBoost = packageMaterial.ColorBoost;
		material.fresnelBoost = packageMaterial.FresnelBoost;
		material.fresnelExponent = packageMaterial.FresnelExponent;

		int shaderType = 0;

		const auto& materialTypeIndex = MaterialTypeMap.find(packageMaterial.ShaderName);

		if (materialTypeIndex != MaterialTypeMap.end())
		{
			shaderType = materialTypeIndex->second;
		}
		else
		{
			if (!UnmappedMaterials.contains(packageMaterial.ShaderName) && packageMaterial.ShaderName != "")
				UnmappedMaterials.insert(packageMaterial.ShaderName);
		}

		std::string diffuse = packageMaterial.Diffuse.substr(0, diffuse.size() - 4);

		if (strcmp(diffuse.c_str() + diffuse.size() - 4, ".dds") == 0)
		{
			diffuse = diffuse;
		}

		VkSamplerCreateInfo sampler = TextureAsset::GetDefaultSampler();

		std::string anisotropic = fs::path(packageMaterial.Anisotropic).stem().string();

		if (lower(anisotropic) == "hair_a")
			anisotropic = "Resource/Model/Textures/item_hair/hair_a";

		material.textures = (int)MaterialTextures.size();

		MaterialTextures.push_back({});

		::MaterialTextures& textures = MaterialTextures.back();

		auto& textureLibrary = AssetLibrary.GetTextures();

		textures.diffuse.id = textureLibrary.FetchTexture(fs::path(packageMaterial.Diffuse).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
		textures.specular.id = textureLibrary.FetchTexture(fs::path(packageMaterial.Specular).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
		textures.normal.id = textureLibrary.FetchTexture(fs::path(packageMaterial.Normal).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
		textures.colorOverride.id = textureLibrary.FetchTexture(fs::path(packageMaterial.OverrideColor).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
		textures.emissive.id = textureLibrary.FetchTexture(fs::path(packageMaterial.Glow).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
		textures.decal.id = textureLibrary.FetchTexture(fs::path(packageMaterial.Decal).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
		textures.anisotropic.id = textureLibrary.FetchTexture(anisotropic, VK_FORMAT_R8G8B8A8_UNORM, sampler);

		const auto getTransform = [this](const Engine::Graphics::ModelPackageTextureTransform& modelTransform) -> int
		{
			if (!modelTransform.Active)
			{
				return -1;
			}

			int id = (int)TextureTransforms.size();

			TextureTransforms.push_back(TextureTransform{});

			TextureTransform& transform = TextureTransforms.back();

			transform.translation = vec2{ modelTransform.Translation.X, modelTransform.Translation.Y };
			transform.scale = vec2{ modelTransform.Scale.X, modelTransform.Scale.Y };
			transform.pivot = vec2{ modelTransform.Pivot.X, modelTransform.Pivot.Y };
			transform.rotation = modelTransform.Rotation;
			transform.mode = modelTransform.Mode;

			return id;
		};

		textures.diffuse.transformId = getTransform(packageMaterial.DiffuseTransform);
		textures.specular.transformId = getTransform(packageMaterial.SpecularTransform);
		textures.normal.transformId = getTransform(packageMaterial.NormalTransform);
		textures.colorOverride.transformId = getTransform(packageMaterial.OverrideColorTransform);
		textures.emissive.transformId = getTransform(packageMaterial.GlowTransform);
		textures.decal.transformId = getTransform(packageMaterial.DecalTransform);
		textures.anisotropic.transformId = getTransform(packageMaterial.AnisotropicTransform);

		//material.overrideColor0[0] = packageMaterial.OverrideColor0.R;
		//material.overrideColor0[1] = packageMaterial.OverrideColor0.G;
		//material.overrideColor0[2] = packageMaterial.OverrideColor0.B;
		//
		//material.overrideColor1[0] = packageMaterial.OverrideColor1.R;
		//material.overrideColor1[1] = packageMaterial.OverrideColor1.G;
		//material.overrideColor1[2] = packageMaterial.OverrideColor1.B;
		//
		//material.overrideColor2[0] = packageMaterial.OverrideColor2.R;
		//material.overrideColor2[1] = packageMaterial.OverrideColor2.G;
		//material.overrideColor2[2] = packageMaterial.OverrideColor2.B;

		bool debugDrawObject = packageMaterial.Name == "" && packageMaterial.ShaderName == "";

		material.shaderType = (shaderType << 16) | (int)debugDrawObject;

		material.textureModes = (int)packageMaterial.TextureApplyMode; // 2 bits
		material.textureModes |= ((int)packageMaterial.SourceVertexMode << 2); // 2 bits
		material.textureModes |= ((int)packageMaterial.LightingMode << 4); // 1 bit
		material.textureModes |= ((int)packageMaterial.SourceBlendMode << 5); // 4 bits
		material.textureModes |= ((int)packageMaterial.DestBlendMode << 9); // 4 bits
		material.textureModes |= ((int)packageMaterial.AlphaTestMode << 13); // 4 bits
		material.textureModes |= ((int)packageMaterial.TestThreshold << 17); // 4 bits
	}

	void ModelLibrary::LoadBuffers(MeshBuffers& buffers, Engine::Graphics::ModelPackageNode& node)
	{
		std::vector<Engine::Graphics::VertexAttributeFormat> attributes;

		for (size_t binding = 0; binding < 6; ++binding)
		{
			bool foundInBinding = false;

			for (const auto& attribute : MeshFormat->GetAttributes())
			{
				if (attribute.Binding == binding && node.Format->GetAttribute(attribute.Name) != nullptr)
				{
					foundInBinding = true;

					break;
				}
			}

			if (!foundInBinding) continue;

			for (const auto& attribute : MeshFormat->GetAttributes())
			{
				if (attribute.Binding == binding)
				{
					attributes.push_back(attribute);
				}
			}
		}
		
		auto bufferFormat = Engine::Graphics::MeshFormat::GetFormat(attributes);

		const auto& nodeAttributes = node.Format->GetAttributes();

		size_t vertices = node.Mesh->GetVertices();
		size_t indices = node.Mesh->GetIndices();

		const auto enableBinding = [](auto& buffers, const auto& format, size_t binding, auto& vector, size_t size)
		{
			if (binding >= format->GetBindingCount() || format->GetVertexSize(binding) == 0) return;

			vector.resize(size);
			buffers.VertexBindings[binding] = vector.data();
		};

		enableBinding(buffers, bufferFormat, 0, buffers.VertexPositions, vertices);
		enableBinding(buffers, bufferFormat, 1, buffers.VertexBinormals, vertices);
		enableBinding(buffers, bufferFormat, 2, buffers.VertexMorphPos, vertices);
		enableBinding(buffers, bufferFormat, 3, buffers.VertexBlend, vertices);

		buffers.IndexBuffer = node.Mesh->GetIndexBuffer();

		node.Format->Copy(node.Mesh->GetData(), buffers.VertexBindings, bufferFormat, vertices);
	}

	uint32_t ModelLibrary::LoadModel(MeshBuffers& buffers, const Matrix4F& transform, bool invisible)
	{
		uint32_t index = (uint32_t)MeshDescriptions.size();

		MeshDescriptions.push_back({});
		MeshDescription& mesh = MeshDescriptions.back();

		mesh.IndexCount = (uint32_t)buffers.IndexBuffer.size();
		mesh.VertexCount = (uint32_t)buffers.VertexPositions.size();

		const auto& vulkanContext = AssetLibrary.GetVulkanContext();

		const auto bindBuffer = [](const auto& vulkanContext, VkCommandBuffer cmdBuf, auto& vector, void* pointer, VkBufferUsageFlags flags)
		{
			if (pointer == nullptr) return nvvk::Buffer();

			return vulkanContext->Allocator.createBuffer(cmdBuf, vector, flags);
		};

		// Create the buffers on Device and copy vertices, indices and materials
		nvvk::CommandPool  cmdBufGet(vulkanContext->Device, vulkanContext->GraphicsQueueIndex);
		VkCommandBuffer    cmdBuf = cmdBufGet.createCommandBuffer();
		VkBufferUsageFlags flag = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
		VkBufferUsageFlags rayTracingFlags =  // used also for building acceleration structures
			flag | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		VkBufferUsageFlags vertexBufferFlags = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | rayTracingFlags;

		mesh.VertexPosBuffer = bindBuffer(vulkanContext, cmdBuf, buffers.VertexPositions, buffers.VertexBindings[0], vertexBufferFlags);
		mesh.VertexBinormalBuffer = bindBuffer(vulkanContext, cmdBuf, buffers.VertexBinormals, buffers.VertexBindings[1], vertexBufferFlags);
		mesh.VertexMorphBuffer = bindBuffer(vulkanContext, cmdBuf, buffers.VertexMorphPos, buffers.VertexBindings[2], vertexBufferFlags);
		mesh.VertexBlendBuffer = bindBuffer(vulkanContext, cmdBuf, buffers.VertexBlend, buffers.VertexBindings[3], vertexBufferFlags);

		mesh.IndexBuffer = bindBuffer(vulkanContext, cmdBuf, buffers.IndexBuffer, buffers.IndexBuffer.data(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT | rayTracingFlags);

		std::vector<int32_t> materialIndices(mesh.IndexCount / 3);

		mesh.MatColorBuffer = vulkanContext->Allocator.createBuffer(cmdBuf, std::vector<MaterialObj> { buffers.Material }, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | flag);
		mesh.MatIndexBuffer = vulkanContext->Allocator.createBuffer(cmdBuf, materialIndices, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | flag);
		// Creates all textures found and find the offset for this model
		auto txtOffset = 0;
		AssetLibrary.GetTextures().FlushLoadingQueue(cmdBuf);
		cmdBufGet.submitAndWait(cmdBuf);
		vulkanContext->Allocator.finalizeAndReleaseStaging();

		std::string objNb = std::to_string(Models.size());
		
		vulkanContext->Debug.setObjectName(mesh.VertexPosBuffer.buffer, (std::string("vertexPos_" + objNb)));

		if (mesh.VertexAttribBuffer.buffer)
			vulkanContext->Debug.setObjectName(mesh.VertexAttribBuffer.buffer, (std::string("vertexAttrib_" + objNb)));

		if (mesh.VertexColorBuffer.buffer)
			vulkanContext->Debug.setObjectName(mesh.VertexColorBuffer.buffer, (std::string("vertexColor_" + objNb)));

		if (mesh.VertexBinormalBuffer.buffer)
			vulkanContext->Debug.setObjectName(mesh.VertexBinormalBuffer.buffer, (std::string("vertexBinormal_" + objNb)));

		if (mesh.VertexMorphBuffer.buffer)
			vulkanContext->Debug.setObjectName(mesh.VertexMorphBuffer.buffer, (std::string("vertexMorph_" + objNb)));

		if (mesh.VertexBlendBuffer.buffer)
			vulkanContext->Debug.setObjectName(mesh.VertexBlendBuffer.buffer, (std::string("vertexBlend_" + objNb)));

		vulkanContext->Debug.setObjectName(mesh.IndexBuffer.buffer, (std::string("index_" + objNb)));
		vulkanContext->Debug.setObjectName(mesh.MatColorBuffer.buffer, (std::string("mat_" + objNb)));
		vulkanContext->Debug.setObjectName(mesh.MatIndexBuffer.buffer, (std::string("matIdx_" + objNb)));

		// Creating information for device access
		MeshDesc desc;
		desc.displayFlags = (invisible ? 1 : 0);
		desc.vertexPosAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.VertexPosBuffer.buffer);

		if (mesh.VertexBinormalBuffer.buffer)
			desc.vertexBinormalAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.VertexBinormalBuffer.buffer);

		if (mesh.VertexMorphBuffer.buffer)
			desc.vertexMorphAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.VertexMorphBuffer.buffer);

		if (mesh.VertexBlendBuffer.buffer)
			desc.vertexBlendAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.VertexBlendBuffer.buffer);

		desc.indexAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.IndexBuffer.buffer);
		desc.materialAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.MatColorBuffer.buffer);
		desc.materialIndexAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.MatIndexBuffer.buffer);

		// Keeping the obj host model and device description
		GpuMeshData.emplace_back(desc);

		return index;
	}

	uint32_t ModelLibrary::LoadWireframeMesh(const std::vector<VertexPosBinding>& vertices, const std::vector<int>& indices)
	{
		uint32_t index = (uint32_t)WireframeDescriptions.size();

		WireframeDescriptions.push_back({});
		WireframeDescription& mesh = WireframeDescriptions.back();

		mesh.IndexCount = (uint32_t)indices.size();
		mesh.VertexCount = (uint32_t)vertices.size();

		const auto& vulkanContext = AssetLibrary.GetVulkanContext();

		// Create the buffers on Device and copy vertices, indices and materials
		nvvk::CommandPool  cmdBufGet(vulkanContext->Device, vulkanContext->GraphicsQueueIndex);
		VkCommandBuffer    cmdBuf = cmdBufGet.createCommandBuffer();
		VkBufferUsageFlags flag = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

		mesh.VertexBuffer = vulkanContext->Allocator.createBuffer(cmdBuf, vertices, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | flag);
		mesh.IndexBuffer = vulkanContext->Allocator.createBuffer(cmdBuf, indices, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | flag);

		cmdBufGet.submitAndWait(cmdBuf);
		vulkanContext->Allocator.finalizeAndReleaseStaging();

		std::string objNb = std::to_string(index);

		vulkanContext->Debug.setObjectName(mesh.VertexBuffer.buffer, (std::string("wireframeVertexPos_" + objNb)));

		vulkanContext->Debug.setObjectName(mesh.IndexBuffer.buffer, (std::string("wireframeIndex_" + objNb)));

		// Creating information for device access
		WireframeDesc desc;
		desc.vertexAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.VertexBuffer.buffer);
		desc.indexAddress = nvvk::getBufferDeviceAddress(vulkanContext->Device, mesh.IndexBuffer.buffer);

		// Keeping the obj host model and device description
		GpuWireframeData.emplace_back(desc);

		return index;
	}

	void ModelLibrary::UpdateWireframeMesh(uint32_t index, const std::vector<VertexPosBinding>& vertices, const std::vector<int>& indices)
	{
		if (index >= WireframeDescriptions.size()) return;

		WireframeDescription& mesh = WireframeDescriptions[index];

		const auto& vulkanContext = AssetLibrary.GetVulkanContext();
		VkBuffer deviceUBO = mesh.VertexBuffer.buffer;

		nvvk::CommandPool  cmdBufGet(vulkanContext->Device, vulkanContext->GraphicsQueueIndex);
		VkCommandBuffer    cmdBuf = cmdBufGet.createCommandBuffer();

		// Ensure that the modified UBO is not visible to previous frames.
		VkBufferMemoryBarrier vertexBeforeBarrier{ VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER };
		vertexBeforeBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
		vertexBeforeBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		vertexBeforeBarrier.buffer = mesh.VertexBuffer.buffer;
		vertexBeforeBarrier.offset = 0;
		vertexBeforeBarrier.size = (VkDeviceSize)(vertices.size() * sizeof(vertices[0]));

		vkCmdPipelineBarrier(cmdBuf, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_DEPENDENCY_DEVICE_GROUP_BIT, 0,
			nullptr, 1, &vertexBeforeBarrier, 0, nullptr);

		vkCmdUpdateBuffer(cmdBuf, vertexBeforeBarrier.buffer, vertexBeforeBarrier.offset, vertexBeforeBarrier.size, vertices.data());

		VkBufferMemoryBarrier indexBeforeBarrier = vertexBeforeBarrier;
		indexBeforeBarrier.buffer = mesh.IndexBuffer.buffer;
		indexBeforeBarrier.size = (VkDeviceSize)(indices.size() * sizeof(indices[0]));

		vkCmdPipelineBarrier(cmdBuf, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_DEPENDENCY_DEVICE_GROUP_BIT, 0,
			nullptr, 1, &indexBeforeBarrier, 0, nullptr);

		vkCmdUpdateBuffer(cmdBuf, indexBeforeBarrier.buffer, indexBeforeBarrier.offset, indexBeforeBarrier.size, indices.data());

		VkBufferMemoryBarrier vertexAfterBarrier = vertexBeforeBarrier;
		vertexAfterBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		vertexAfterBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_DEPENDENCY_DEVICE_GROUP_BIT, 0,
			nullptr, 1, &vertexAfterBarrier, 0, nullptr);

		VkBufferMemoryBarrier indexAfterBarrier = indexBeforeBarrier;
		indexAfterBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		indexAfterBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_DEPENDENCY_DEVICE_GROUP_BIT, 0,
			nullptr, 1, &indexAfterBarrier, 0, nullptr);

		cmdBufGet.submitAndWait(cmdBuf);
	}

	SpawnedEntity* ModelLibrary::SpawnModel(RTScene* scene, MapLoader::ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback)
	{
		if (model == nullptr)
			return nullptr;

		int entityId = (int)SpawnedEntities.size();
		SpawnedEntities.push_back(SpawnedEntity{ model });
		auto& spawnedEntity = SpawnedEntities.back();

		for (size_t i = 0; i < model->Nodes.size(); ++i)
		{
			if (model->IsLoaded(i))
			{
				InstDesc instance;

				if (callback != nullptr)
				{
					const auto& meshDescription = GetMeshDescriptions()[model->Nodes[i].MeshId];

					ModelSpawnParameters parameters
					{
						.Model = model,
						.MeshIndex = i,
						.NewInstance = instance,
						.MeshId = GpuEntityData.size(),
						.VertexCount = meshDescription.VertexCount,
						.IndexCount = meshDescription.IndexCount
					};

					if (!callback(parameters))
						continue;
				}

				Matrix4F modelTransform = model->Nodes[i].Transformation;

				LoadModelInstance(model->GetId(i), CurrentMapTransform * transformation * modelTransform);

				SpawnedModels.push_back(SpawnedModel{ entityId, (int)i });

				std::shared_ptr<Engine::Transform> transform = Engine::Create<Engine::Transform>();
				std::shared_ptr<MapLoader::SceneObject> sceneObject = Engine::Create<MapLoader::SceneObject>();

				transform->SetTransformation(CurrentMapTransform * transformation * modelTransform);
				sceneObject->SetTransform(transform.get());
				sceneObject->SetModel(model, i);
				sceneObject->SetStatic(true);
				sceneObject->SetParent(transform);
				scene->AddObject(sceneObject);
				spawnedEntity.Meshes.push_back({ transform, sceneObject });

				GpuEntityData.push_back(instance);
			}
		}

		return &spawnedEntity;
	}

	void ModelLibrary::SpawnWireframe(RTScene* scene, uint32_t index, const Matrix4F& transform)
	{
		LoadWireframeInstance(index, CurrentMapTransform * transform);
	}

	void ModelLibrary::FreeResources()
	{
		const auto& vulkanContext = AssetLibrary.GetVulkanContext();

		for (auto& m : MeshDescriptions)
		{
			vulkanContext->Allocator.destroy(m.VertexPosBuffer);
			vulkanContext->Allocator.destroy(m.VertexAttribBuffer);
			vulkanContext->Allocator.destroy(m.VertexColorBuffer);
			vulkanContext->Allocator.destroy(m.VertexBinormalBuffer);
			vulkanContext->Allocator.destroy(m.VertexMorphBuffer);
			vulkanContext->Allocator.destroy(m.VertexBlendBuffer);
			vulkanContext->Allocator.destroy(m.IndexBuffer);
			vulkanContext->Allocator.destroy(m.MatColorBuffer);
			vulkanContext->Allocator.destroy(m.MatIndexBuffer);
		}

		for (auto& m : WireframeDescriptions)
		{
			vulkanContext->Allocator.destroy(m.VertexBuffer);
			vulkanContext->Allocator.destroy(m.IndexBuffer);
		}

		Models.clear();
		ModelMap.clear();
		GpuMeshData.clear();
		GpuWireframeData.clear();
		MeshDescriptions.clear();
		WireframeDescriptions.clear();
	}

	void ModelLibrary::LoadModelInstance(uint32_t index, Matrix4F transform)
	{
		ObjInstance instance;
		instance.transform = transform;
		instance.objIndex = index;
		SpawnedInstances.push_back(instance);
	}

	void ModelLibrary::LoadWireframeInstance(uint32_t index, Matrix4F transform)
	{
		ObjInstance instance;
		instance.transform = transform;
		instance.objIndex = index;
		SpawnedWireframeInstances.push_back(instance);
	}
}