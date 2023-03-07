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

namespace MapLoader
{
	const std::unordered_map<std::string, int> ModelLibrary::MaterialTypeMap = {
		{ "MS2StandardMaterial", 0 },
		//{ "MS2ShimmerMaterial", 1 },
		//{ "MS2GlowMaterial", 2 },
		{ "MS2CharacterSkinMaterial", 3 },
		{ "MS2CharacterMaterial", 4 },
		//{ "MS2CharacterHairMaterial", 5 },
		{ "MS2GlassMaterial", 6 },
	};

	std::unordered_set<std::string> ModelLibrary::UnmappedMaterials = {};

	ModelData* ModelLibrary::FetchModel(const Archive::Metadata::Entry* entry, bool keepRawData)
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

		FetchModel(Reader->GetPath(filepath), loadedModel, keepRawData);

		return &loadedModel;
	}

	bool ModelLibrary::FetchModel(const Archive::ArchivePath& file, ModelData& loadedModel, bool keepRawData)
	{
		if (!file.Loaded())
		{
			std::cout << "failed to load model " << file.GetPath().string() << std::endl;
			return false;
		}

		Engine::Graphics::ModelPackage package;

		NifParser parser;
		parser.Package = &package;

		file.Read(NifDocumentBuffer);
		parser.Parse(NifDocumentBuffer);

		loadedModel.MeshIds.resize(parser.Package->Nodes.size());
		loadedModel.Transformations.resize(parser.Package->Nodes.size());
		loadedModel.Materials.resize(parser.Package->Nodes.size());
		loadedModel.Shaders.resize(parser.Package->Nodes.size());
		loadedModel.MaterialNames.resize(parser.Package->Nodes.size());
		loadedModel.NodeNames.resize(parser.Package->Nodes.size());
		loadedModel.Meshes.resize(parser.Package->Nodes.size());

		if (parser.Package->Nodes.size() > 0)
		{
			parser.Package->Nodes[0].Transform->Update(0);
		}

		for (size_t i = 0; i < parser.Package->Nodes.size(); ++i)
		{
			Engine::Graphics::ModelPackageNode& node = parser.Package->Nodes[i];

			loadedModel.MeshIds[i] = -1;
			loadedModel.NodeNames[i] = node.Name;

			if (node.Transform != nullptr)
				loadedModel.Transformations[i] = node.Transform->GetWorldTransformation();

			if (node.Mesh != nullptr)
			{
				if (keepRawData)
					loadedModel.Meshes[i] = node.Mesh;

				tinyobj::attrib_t attrib;

				bool hasColor = node.Format->GetAttribute("COLOR") != nullptr;
				bool hasBinormal = node.Format->GetAttribute("binormal") != nullptr;

				size_t vertices = node.Mesh->GetVertices();
				size_t indices = node.Mesh->GetTriangleVertices();

				if (vertices == 0 || indices == 0 || (indices % 3) != 0)
					vertices += 0;

				attrib.vertices.resize(vertices * 3);
				attrib.texcoords.resize(vertices * 2);
				attrib.normals.resize(vertices * 3);

				std::vector<Color4I> colors;
				std::vector<Vector3> binormal;
				std::vector<Vector3> tangent;

				if (hasColor)
				{
					colors.resize(vertices);
					attrib.colors.resize(vertices * 4);
				}

				if (hasBinormal)
				{
					binormal.resize(vertices);
					tangent.resize(vertices);
					attrib.binormals.resize(vertices * 3);
					attrib.tangents.resize(vertices * 3);
				}

				std::vector<void*> data;

				data.push_back(attrib.vertices.data());
				data.push_back(attrib.texcoords.data());
				data.push_back(attrib.normals.data());

				if (hasColor)
				{
					data.push_back(colors.data());
				}

				if (hasBinormal)
				{
					data.push_back(attrib.binormals.data());
					data.push_back(attrib.tangents.data());
				}

				struct MeshFormatRef
				{
					const std::shared_ptr<Engine::Graphics::MeshFormat>& Ref;
				};

				MeshFormatRef formats[4] = {
					ImportFormat,
					ImportFormatWithColor,
					ImportFormatWithBinormal,
					ImportFormatWithColorAndBinormal
				};

				int formatIndex = (hasColor ? 1 : 0) + (hasBinormal ? 2 : 0);

				const std::shared_ptr<Engine::Graphics::MeshFormat>& format = formats[formatIndex].Ref;

				node.Format->Copy(node.Mesh->GetData(), data.data(), format, vertices);

				if (hasColor)
				{
					for (size_t i = 0; i < vertices; ++i)
					{
						Color4 color = colors[i];

						attrib.colors[4 * i + 0] = color.R;
						attrib.colors[4 * i + 1] = color.G;
						attrib.colors[4 * i + 2] = color.B;
						attrib.colors[4 * i + 3] = color.A;
					}
				}

				ObjLoader loader;
				loader.TextureLibrary = TextureLibrary;

				std::vector<MaterialObj>& materials = loader.m_materials;

				if (node.MaterialIndex != -1)
				{
					const Engine::Graphics::ModelPackageMaterial& packageMaterial = parser.Package->Materials[node.MaterialIndex];

					loadedModel.Shaders[i] = packageMaterial.ShaderName;
					loadedModel.MaterialNames[i] = packageMaterial.Name;

					MaterialObj material;

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

					textures.diffuse.id = TextureLibrary->FetchTexture(fs::path(packageMaterial.Diffuse).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
					textures.specular.id = TextureLibrary->FetchTexture(fs::path(packageMaterial.Specular).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
					textures.normal.id = TextureLibrary->FetchTexture(fs::path(packageMaterial.Normal).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
					textures.colorOverride.id = TextureLibrary->FetchTexture(fs::path(packageMaterial.OverrideColor).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
					textures.emissive.id = TextureLibrary->FetchTexture(fs::path(packageMaterial.Glow).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
					textures.decal.id = TextureLibrary->FetchTexture(fs::path(packageMaterial.Decal).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
					textures.anisotropic.id = TextureLibrary->FetchTexture(anisotropic, VK_FORMAT_R8G8B8A8_UNORM, sampler);

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

					materials.push_back(material);
				}

				if (node.MaterialIndex == -1)
				{
					i += 0;
				}

				std::vector<tinyobj::shape_t> shapes(1);

				tinyobj::shape_t shape;

				shape.mesh.indices.reserve(indices);

				for (int index : node.Mesh->GetIndexBuffer())
				{
					shape.mesh.indices.push_back(tinyobj::index_t{ index, index, index, index });
				}

				shape.mesh.material_ids.reserve(indices / 3);

				for (int i = 0; i < indices / 3; ++i)
				{
					shape.mesh.material_ids.push_back(0);
				}

				shapes.push_back(shape);

				loader.loadModel(attrib, {}, shapes);

				loadedModel.Materials[i] = loader.m_materials[0];
				loadedModel.MeshIds[i] = (int)LoadModel(loader);
			}
		}

		return true;
	}

	ModelLibrary::ModelLibrary(
		const std::shared_ptr<Archive::ArchiveReader>& reader,
		const std::shared_ptr<MapLoader::TextureLibrary>& textureLibrary,
		const std::shared_ptr<Graphics::VulkanContext>& vulkanContext) : Reader(reader), TextureLibrary(textureLibrary), VulkanContext(vulkanContext)
	{
		std::vector<Engine::Graphics::VertexAttributeFormat> attributes;

		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "position", 0 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 2, "textureCoords", 1 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "normal", 2 });

		ImportFormat = Engine::Graphics::MeshFormat::GetFormat(attributes);

		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::UInt8, 4, "COLOR", 3 });

		ImportFormatWithColor = Engine::Graphics::MeshFormat::GetFormat(attributes);

		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "binormal", 4 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "tangent", 5 });

		ImportFormatWithColorAndBinormal = Engine::Graphics::MeshFormat::GetFormat(attributes);

		attributes.resize(3);

		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "binormal", 3 });
		attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "tangent", 4 });

		ImportFormatWithBinormal = Engine::Graphics::MeshFormat::GetFormat(attributes);
	}

	ModelLibrary::~ModelLibrary()
	{
		FreeResources();
	}

	uint32_t ModelLibrary::LoadModel(ObjLoader& loader, const Matrix4F& transform, bool invisible)
	{
		// Converting from Srgb to linear
		for (auto& m : loader.m_materials)
		{
			//const auto pow = [](const vec3 & vec, float exp)
			//{
			//	return vec3(std::pow(vec.X, exp), std::pow(vec.Y, exp), std::pow(vec.Z, exp));
			//};
			m.ambient = pow(m.ambient, 2.2f);
			m.diffuse = pow(m.diffuse, 2.2f);
			m.specular = pow(m.specular, 2.2f);
		}

		uint32_t index = (uint32_t)MeshDescriptions.size();

		MeshDescriptions.push_back({});
		MeshDescription& mesh = MeshDescriptions.back();

		mesh.IndexCount = static_cast<uint32_t>(loader.m_indices.size());
		mesh.VertexCount = static_cast<uint32_t>(loader.m_vertices.size());

		// Create the buffers on Device and copy vertices, indices and materials
		nvvk::CommandPool  cmdBufGet(VulkanContext->Device, VulkanContext->GraphicsQueueIndex);
		VkCommandBuffer    cmdBuf = cmdBufGet.createCommandBuffer();
		VkBufferUsageFlags flag = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
		VkBufferUsageFlags rayTracingFlags =  // used also for building acceleration structures
			flag | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		mesh.VertexBuffer = VulkanContext->Allocator.createBuffer(cmdBuf, loader.m_vertices, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | rayTracingFlags);
		mesh.IndexBuffer = VulkanContext->Allocator.createBuffer(cmdBuf, loader.m_indices, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | rayTracingFlags);
		mesh.MatColorBuffer = VulkanContext->Allocator.createBuffer(cmdBuf, loader.m_materials, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | flag);
		mesh.MatIndexBuffer = VulkanContext->Allocator.createBuffer(cmdBuf, loader.m_matIndx, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | flag);
		// Creates all textures found and find the offset for this model
		auto txtOffset = 0;
		TextureLibrary->FlushLoadingQueue(cmdBuf);
		cmdBufGet.submitAndWait(cmdBuf);
		VulkanContext->Allocator.finalizeAndReleaseStaging();

		std::string objNb = std::to_string(Models.size());
		VulkanContext->Debug.setObjectName(mesh.VertexBuffer.buffer, (std::string("vertex_" + objNb)));
		VulkanContext->Debug.setObjectName(mesh.IndexBuffer.buffer, (std::string("index_" + objNb)));
		VulkanContext->Debug.setObjectName(mesh.MatColorBuffer.buffer, (std::string("mat_" + objNb)));
		VulkanContext->Debug.setObjectName(mesh.MatIndexBuffer.buffer, (std::string("matIdx_" + objNb)));

		// Creating information for device access
		ObjDesc desc;
		desc.txtOffset = txtOffset | (invisible ? 0x80000000 : 0);
		desc.vertexAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, mesh.VertexBuffer.buffer);
		desc.indexAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, mesh.IndexBuffer.buffer);
		desc.materialAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, mesh.MatColorBuffer.buffer);
		desc.materialIndexAddress = nvvk::getBufferDeviceAddress(VulkanContext->Device, mesh.MatIndexBuffer.buffer);

		// Keeping the obj host model and device description
		GpuMeshData.emplace_back(desc);

		return index;
	}

	void ModelLibrary::FreeResources()
	{
		for (auto& m : MeshDescriptions)
		{
			VulkanContext->Allocator.destroy(m.VertexBuffer);
			VulkanContext->Allocator.destroy(m.IndexBuffer);
			VulkanContext->Allocator.destroy(m.MatColorBuffer);
			VulkanContext->Allocator.destroy(m.MatIndexBuffer);
		}

		Models.clear();
		ModelMap.clear();
		GpuMeshData.clear();
		MeshDescriptions.clear();
	}
}