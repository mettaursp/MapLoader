/*
 * Copyright (c) 2014-2021, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-FileCopyrightText: Copyright (c) 2014-2021 NVIDIA CORPORATION
 * SPDX-License-Identifier: Apache-2.0
 */


// ImGui - standalone example application for Glfw + Vulkan, using programmable
// pipeline If you are new to ImGui, see examples/README.txt and documentation
// at the top of imgui.cpp.


#include <filesystem>
#include <array>
#include <fstream>
#include <unordered_map>
#include <numeric>
#include <functional>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/imgui.h>

#include "hello_vulkan.h"
#include "imgui/imgui_camera_widget.h"
#include "nvh/cameramanipulator.hpp"
#include "nvh/fileoperations.hpp"
#include <nvp/nvpsystem.hpp>
#include "nvvk/commands_vk.hpp"
#include "nvvk/context_vk.hpp"
#include "obj_loader.h"
#ifdef near
#undef near
#endif

#ifdef far
#undef far
#endif
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
#include <Engine/VulkanGraphics/FileFormats/NifParser.h>
#include <Engine/VulkanGraphics/FileFormats/PackageNodes.h>
#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include <Engine/Math/Matrix4-decl.h>
#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Vector3.h>
#include <Engine/Math/Color3.h>
#include <Engine/Math/Color4.h>
#include <Engine/Math/Color4I.h>
#include <Engine/Objects/Transform.h>
#include <ArchiveParser/ParserUtils.h>
#include <ArchiveParser/ArchiveReader.h>
#include <ArchiveParser/ArchiveParser.h>
#include <ArchiveParser/MetadataMapper.h>


const auto PROJECT_NAME = "MapLoader";

//////////////////////////////////////////////////////////////////////////
#define UNUSED(x) (void)(x)
//////////////////////////////////////////////////////////////////////////

// Default search path for shaders
std::vector<std::string> defaultSearchPaths;


// GLFW Callback functions
static void onErrorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Extra UI
void renderUI(HelloVulkan& helloVk)
{
	ImGuiH::CameraWidget();
	if(ImGui::CollapsingHeader("Light"))
	{
	ImGui::RadioButton("Point", &helloVk.m_pcRaster.lightType, 0);
	ImGui::SameLine();
	ImGui::RadioButton("Infinite", &helloVk.m_pcRaster.lightType, 1);

	ImGui::SliderFloat3("Position", &helloVk.m_pcRaster.lightPosition.X, -20.f, 20.f);
	ImGui::SliderFloat("Intensity", &helloVk.m_pcRaster.lightIntensity, 0.f, 150.f);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
static int const SAMPLE_WIDTH  = 1280;
static int const SAMPLE_HEIGHT = 720;

namespace fs = std::filesystem;

mat4 convert(const Matrix4F& matrix)
{
	return *reinterpret_cast<const mat4*>(&matrix);
}

struct LoadedModel
{
	std::vector<int> ModelIds;
	std::vector<Matrix4F> Transformations;
	std::vector<std::string> Shaders;
	std::vector<std::string> MaterialNames;
	std::vector<std::string> NodeNames;
	std::vector<MaterialObj> Materials;
	std::vector<std::shared_ptr<Engine::Graphics::MeshData>> Meshes;
	const Archive::Metadata::Entry* Entry = nullptr;

	bool IsLoaded(size_t index)
	{
		if (index < 0 || index >= ModelIds.size())
			return false;

		return ModelIds[index] != -1;
	}

	uint32_t GetId(size_t index)
	{
		return (uint32_t)ModelIds[index];
	}
};

struct EntityData;

struct SpawnedEntity
{
	LoadedModel* Model = nullptr;
	const EntityData* Flat = nullptr;
	std::string Id;
	std::string Name;
	Vector3SF Position;
	Vector3SF WorldPosition;
	int MapIndex = -1;
	int PortalIndex = -1;
	int LineNumber = -1;
};

struct SpawnedModel
{
	int EntityId = -1;
	int ModelId = -1;
	int MaterialId = -1;
};

struct LoadedMap
{
	std::string Id;
	std::string Name;
	std::unordered_map<int, int> Portals;
	Matrix4F MapTransform;
	std::string XBlockPath;
};

struct SpawnedPortal
{
	std::string TargetField;
	int TargetPortal;
	int PortalId;
};

enum class Gender
{
	Male = 0,
	Female = 1,
	Either = 2
};

struct DyeColor
{
	Color4 Primary;
	Color4 Secondary;
};

struct Item
{
	int Id = 0;
	DyeColor Color;
	int Preset = 0;
};

struct HairItem : public Item
{
	//float Scale = 0;
	//int Pony = 0;
	//Vector3SF HatPosition;
	//Vector3SF HatRotation;
	//float HatScale = 1;
};

struct FaceDecorItem : public Item
{

};

struct HatItem : public Item
{
	bool CustomAttach = false;
	Vector3SF AttachDirection;
	Vector3SF AttachRotation;
};

struct EquipTab
{
	HatItem Hat;
	Item Shirt;
	Item Pants;
	Item Gloves;
	Item Shoes;
	bool ShirtCoversPants = false;
	Item Earring;
	Item Pendant;
	Item Ring;
	Item Cape;
	Item Belt;
	Item Weapon;
};

struct Character
{
	Gender Gender = Gender::Male;
	DyeColor SkinColor;
	HairItem Hair;
	FaceDecorItem FaceDecor;
	Item Face;
	EquipTab Gear;
	EquipTab Cosmetics;
	std::string Emotion = "default";
	int EmotionFrame = 0;
};

struct DyeColorInfo
{
	std::string Name;
	int Id = 0;
	int Palette = 0;
	int Index = 0;
	Color4 Primary;
	Color4 Unused;
	Color4 Secondary;
	Color4 Display;
	bool DisplayBoth = false;
	bool HasEyeOverride = false;
	Color4 EyePrimary;
	Color4 EyeSecondary;
};

struct EmotionTexture
{
	std::string File;
	std::string Control;
	int Delay = 0;
	bool Loop = false;
};

struct Emotion
{
	std::string Animation;
	std::string IdleAnimation;
	std::string BoreAnimation1;
	std::string BoreAnimation2;
	std::string Target;
	std::string Effect;
	std::vector<EmotionTexture> Faces;
};

std::map<const Archive::Metadata::Entry*, std::unique_ptr<LoadedModel>> models;

HelloVulkan* helloVkPtr = nullptr;
Archive::ArchiveReader Reader;
std::string documentBuffer;
std::string flatDocumentBuffer;
std::string nifDocumentBuffer;

const char* localeName = "NA";
const char* environmentName = "Live";
fs::path ms2Root = "B:/Files/Maplstory 2 Client/appdata";
fs::path ms2RootExtracted = "B:/Files/ms2export/export/";
fs::path tableroot = fs::path("Xml/table/");
bool loadLights = true;
std::shared_ptr<Engine::Graphics::MeshFormat> importFormat;
std::shared_ptr<Engine::Graphics::MeshFormat> importFormatWithColor;
std::shared_ptr<Engine::Graphics::MeshFormat> importFormatWithBinormal;
std::shared_ptr<Engine::Graphics::MeshFormat> importFormatWithColorAndBinormal;
std::vector<SpawnedModel> spawnedModels;
std::vector<SpawnedEntity> spawnedEntities;
std::vector<LoadedMap> loadedMaps;
std::vector<SpawnedPortal> spawnedPortals;
std::unordered_map<std::string, std::string> mapNames;
std::unordered_map<std::string, int> mapIndices;
std::vector<DyeColorInfo> dyeColors;
std::vector<DyeColorInfo> dyeColorsNA;
std::unordered_map<std::string, DyeColorInfo*> dyeColorMap;
std::unordered_map<std::string, Emotion> maleEmotions;
std::unordered_map<std::string, Emotion> femaleEmotions;

std::unordered_map<std::string, int> materialTypeMap = {
	{ "MS2StandardMaterial", 0 },
	//{ "MS2ShimmerMaterial", 1 },
	//{ "MS2GlowMaterial", 2 },
	{ "MS2CharacterSkinMaterial", 3 },
	{ "MS2CharacterMaterial", 4 },
	//{ "MS2CharacterHairMaterial", 5 },
	{ "MS2GlassMaterial", 6 },
};
std::unordered_set<std::string> unmappedMaterials;

const float PI = 3.14159265359f;

Matrix4F ms2ToWorld = Matrix4F::NewScale(0.02f / 3.f, 0.02f / 3.f, 0.02f / 3.f) * Matrix4F::PitchRotation(-PI / 2);

struct RayHit
{
	float Distance = std::numeric_limits<float>::max();
	bool Hit = false;
	Vector3SF Intersection;
	Vector3SF Normal;
};

std::string padId(std::string id)
{
	while (id.size() > 0 && id.size() < 8)
		id = "0" + id;

	return id;
}

RayHit castRay(const LoadedModel* model, Vector3SF rayStart, Vector3SF rayDirection)
{
	RayHit hit;

	for (const std::shared_ptr<Engine::Graphics::MeshData>& mesh : model->Meshes)
	{
		if (mesh == nullptr) continue;

		size_t positionIndex = mesh->GetFormat()->GetAttributeIndex("position");
		size_t normalIndex = mesh->GetFormat()->GetAttributeIndex("normal");

		const std::vector<int>& indexBuffer = mesh->GetIndexBuffer();

		for (size_t i = 0; i < indexBuffer.size(); i += 3)
		{
			size_t vertexAIndex = (size_t)indexBuffer[i];
			size_t vertexBIndex = (size_t)indexBuffer[i + 1];
			size_t vertexCIndex = (size_t)indexBuffer[i + 2];

			const Vector3SF& vertexA = mesh->GetAttribute<Vector3SF>(vertexAIndex, positionIndex);
			const Vector3SF& vertexB = mesh->GetAttribute<Vector3SF>(vertexBIndex, positionIndex);
			const Vector3SF& vertexC = mesh->GetAttribute<Vector3SF>(vertexCIndex, positionIndex);

			Vector3SF faceNormal = (vertexB - vertexA).Cross(vertexC - vertexA);

			float length = faceNormal.SquareLength();

			if (length <= 1e-9)
			{
				continue; // degenerate triangle (0 area)
			}

			float normalDot = faceNormal * rayDirection;
			float distance = (faceNormal * (vertexA - rayStart)) / normalDot;

			if (distance > hit.Distance || distance < 0)
				continue;

			Vector3SF intersection = rayStart + distance * rayDirection;

			float dot1 = (vertexB - vertexA).Cross(intersection - vertexA).Dot(faceNormal);
			float dot2 = (vertexC - vertexB).Cross(intersection - vertexB).Dot(faceNormal);
			float dot3 = (vertexA - vertexC).Cross(intersection - vertexC).Dot(faceNormal);

			if (!(std::signbit(dot1) == std::signbit(dot2) && std::signbit(dot1) == std::signbit(dot3)))
				continue;

			hit.Hit = true;
			hit.Intersection = intersection;
			hit.Distance = distance;

			float u = dot2 * length;
			float v = dot3 * length;
			float w = 1 - u - v;

			const Vector3SF& normalA = mesh->GetAttribute<Vector3SF>(vertexAIndex, normalIndex);
			const Vector3SF& normalB = mesh->GetAttribute<Vector3SF>(vertexBIndex, normalIndex);
			const Vector3SF& normalC = mesh->GetAttribute<Vector3SF>(vertexCIndex, normalIndex);

			hit.Normal = u * normalA + v * normalB + w * normalC;

			if (hit.Normal.SquareLength() <= 1e-9f)
				hit.Normal = faceNormal.Unit();
		}
	}
	
	return hit;
}

struct Bounds
{
	Vector3SF Min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() , std::numeric_limits<float>::max() };
	Vector3SF Max = { -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max() , -std::numeric_limits<float>::max() };
};

void getBounds(const LoadedModel* model, Bounds& bounds)
{
	for (const std::shared_ptr<Engine::Graphics::MeshData>& mesh : model->Meshes)
	{
		if (mesh == nullptr) continue;

		mesh->ForEach<Vector3SF>(mesh->GetFormat()->GetAttributeIndex("position"), [&bounds](const Vector3SF& vertex)
			{
				bounds.Min.X = std::min(bounds.Min.X, vertex.X);
				bounds.Min.Y = std::min(bounds.Min.Y, vertex.Y);
				bounds.Min.Z = std::min(bounds.Min.Z, vertex.Z);
				bounds.Max.X = std::max(bounds.Max.X, vertex.X);
				bounds.Max.Y = std::max(bounds.Max.Y, vertex.Y);
				bounds.Max.Z = std::max(bounds.Max.Z, vertex.Z);
			}
		);
	}
}

bool getModel(const Archive::ArchivePath& file, LoadedModel& loadedModel, bool saveMesh = false)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load model " << file.GetPath().string() << std::endl;
		return false;
	}

	Engine::Graphics::ModelPackage package;

	NifParser parser;
	parser.Package = &package;

	file.Read(nifDocumentBuffer);
	parser.Parse(nifDocumentBuffer);

	loadedModel.ModelIds.resize(parser.Package->Nodes.size());
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

		loadedModel.ModelIds[i] = -1;
		loadedModel.NodeNames[i] = node.Name;

		if (node.Transform != nullptr)
			loadedModel.Transformations[i] = node.Transform->GetWorldTransformation();

		if (node.Mesh != nullptr)
		{
			if (saveMesh)
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
				importFormat,
				importFormatWithColor,
				importFormatWithBinormal,
				importFormatWithColorAndBinormal
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

			ObjLoader loader(helloVkPtr->textureCache, helloVkPtr->textureFormats, helloVkPtr->textureSamplers); 

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

				const auto& materialTypeIndex = materialTypeMap.find(packageMaterial.ShaderName);

				if (materialTypeIndex != materialTypeMap.end())
				{
					shaderType = materialTypeIndex->second;
				}
				else
				{
					if (!unmappedMaterials.contains(packageMaterial.ShaderName) && packageMaterial.ShaderName != "")
						unmappedMaterials.insert(packageMaterial.ShaderName);
				}

				std::string diffuse = packageMaterial.Diffuse.substr(0, diffuse.size() - 4);

				if (strcmp(diffuse.c_str() + diffuse.size() - 4, ".dds") == 0)
				{
					diffuse = diffuse;
				}

				VkSamplerCreateInfo sampler = HelloVulkan::GetDefaultSampler();

				std::string anisotropic = fs::path(packageMaterial.Anisotropic).stem().string();

				if (lower(anisotropic) == "hair_a")
					anisotropic = "Resource/Model/Textures/item_hair/hair_a";

				material.textures.diffuse.id = helloVkPtr->GetTexture(fs::path(packageMaterial.Diffuse).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
				material.textures.specular.id = helloVkPtr->GetTexture(fs::path(packageMaterial.Specular).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
				material.textures.normal.id = helloVkPtr->GetTexture(fs::path(packageMaterial.Normal).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
				material.textures.colorOverride.id = helloVkPtr->GetTexture(fs::path(packageMaterial.OverrideColor).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
				material.textures.emissive.id = helloVkPtr->GetTexture(fs::path(packageMaterial.Glow).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
				material.textures.decal.id = helloVkPtr->GetTexture(fs::path(packageMaterial.Decal).stem().string(), VK_FORMAT_R8G8B8A8_UNORM, sampler);
				material.textures.anisotropic.id = helloVkPtr->GetTexture(anisotropic, VK_FORMAT_R8G8B8A8_UNORM, sampler);

				const auto getTransform = [](const Engine::Graphics::ModelPackageTextureTransform& modelTransform) -> int
				{
					if (!modelTransform.Active)
					{
						return -1;
					}

					int id = (int)helloVkPtr->textureTransforms.size();

					helloVkPtr->textureTransforms.push_back(TextureTransform{});

					TextureTransform& transform = helloVkPtr->textureTransforms.back();

					transform.translation = vec2{ modelTransform.Translation.X, modelTransform.Translation.Y };
					transform.scale = vec2{ modelTransform.Scale.X, modelTransform.Scale.Y };
					transform.pivot = vec2{ modelTransform.Pivot.X, modelTransform.Pivot.Y };
					transform.rotation = modelTransform.Rotation;
					transform.mode = modelTransform.Mode;

					return id;
				};

				material.textures.diffuse.transformId = getTransform(packageMaterial.DiffuseTransform);
				material.textures.specular.transformId = getTransform(packageMaterial.SpecularTransform);
				material.textures.normal.transformId = getTransform(packageMaterial.NormalTransform);
				material.textures.colorOverride.transformId = getTransform(packageMaterial.OverrideColorTransform);
				material.textures.emissive.transformId = getTransform(packageMaterial.GlowTransform);
				material.textures.decal.transformId = getTransform(packageMaterial.DecalTransform);
				material.textures.anisotropic.transformId = getTransform(packageMaterial.AnisotropicTransform);

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
			loadedModel.ModelIds[i] = (int)helloVkPtr->loadModel(loader);
		}
	}

	return true;
}

LoadedModel* getModel(const Archive::Metadata::Entry* entry, bool saveMesh = false)
{
	if (entry == nullptr) return nullptr;

	fs::path filepath = "Resource";
	filepath += entry->RelativePath;

	std::string name = lower(entry->Name);

	const auto& asset = models.find(entry);

	if (asset != models.end())
	{
		return asset->second.get();
	}

	models[entry] = std::move(std::make_unique<LoadedModel>());

	LoadedModel& loadedModel = *models[entry];

	loadedModel.Entry = entry;

	getModel(Reader.GetPath(filepath), loadedModel, saveMesh);

	return &loadedModel;
}

enum class EntityLightType
{
	Point,
	Directional,
	Ambient
};

struct EntityLight
{
	EntityLightType Type = EntityLightType::Point;
	float Dimmer = 0;
	Color3 DiffuseColor;
	Color3 SpecularColor;
	Color3 AmbientColor;
	float Range = 0;
	Vector3SF Position;
	Vector3SF Direction;
	float Scale;
	bool Enabled = false;
	bool CastsShadows = true;
};

struct EntityData
{
	LoadedModel* Model = nullptr;
	const Archive::Metadata::Entry* Entry = nullptr;
	Matrix4F Transformation;
	Vector3SF VisualOffset;
	Vector3SF Position;
	Vector3SF Rotation;
	float Scale;
	bool IsVisible = true;
	const Archive::Metadata::Entry* ModelEntry = nullptr;
	std::string Id;
	Color3 MaterialColor = Color3(1.0f, 1, 1);
	bool IsLight = false;
	EntityLight Light;
	std::string TargetField;
	bool IsPortal = false;
	int TargetPortal = -1;
	int PortalId = -1;
};

typedef std::function<bool(LoadedModel*, size_t, InstDesc&)> ModelSpawnCallback;

SpawnedEntity* spawnModel(LoadedModel* model, const Matrix4F& transform = Matrix4F(), const ModelSpawnCallback& callback = nullptr)
{
	if (model == nullptr)
		return nullptr;

	int entityId = (int)spawnedEntities.size();
	spawnedEntities.push_back(SpawnedEntity{ model });

	for (size_t i = 0; i < model->ModelIds.size(); ++i)
	{
		if (model->IsLoaded(i))
		{
			InstDesc instance;

			if (callback != nullptr)
			{
				if (!callback(model, i, instance))
					continue;
			}

			//model->Package.Nodes[i].Mesh->
			Matrix4F modelTransform;

			//if (model->Package.Nodes[i].Transform->InheritsTransformation())
				modelTransform = model->Transformations[i];

			helloVkPtr->loadModelInstance(model->GetId(i), convert(ms2ToWorld * transform * modelTransform));

			spawnedModels.push_back(SpawnedModel{ entityId, (int)i });

			helloVkPtr->instanceDescriptions.push_back(instance);
		}
	}

	return &spawnedEntities.back();
}

std::map<const Archive::Metadata::Entry*, EntityData> loadedFlats;

float degToRad(float deg)
{
	return deg / 180 * PI;
}

Matrix4F getMatrix(const Vector3SF& position, const Vector3SF& rotation, float scale, bool isDegrees = true)
{
	// roll = yaw
	// yaw = pitch
	// pitch = roll
	float x = rotation.X;
	float y = rotation.Y;
	float z = rotation.Z;

	if (isDegrees)
	{
		x = degToRad(x);
		y = degToRad(y);
		z = degToRad(z);
	}

	Matrix4F roll = Matrix4F::RollRotation(z);
	Matrix4F yaw = Matrix4F::YawRotation(y);
	Matrix4F pitch = Matrix4F::PitchRotation(x);
	Matrix4F rotationMatrix = pitch * yaw * roll;
	//Matrix4F::EulerAnglesRotation(degToRad(rotation.X), degToRad(rotation.Y), degToRad(rotation.Z))
	return Matrix4F(position) * rotationMatrix * Matrix4F::NewScale(scale, scale, scale);
}

template <>
Vector3SF readValue<Vector3SF>(const tinyxml2::XMLAttribute* attribute)
{
	const char* value = attribute->Value();
	Vector3SF vector;

	vector.X = (float)std::atof(value);

	while (value[0] && (value[0] != ' ' && value[0] != ','))
		++value;

	while (value[0] && (value[0] == ' ' || value[0] == ','))
		++value;

	vector.Y = (float)std::atof(value);

	while (value[0] && (value[0] != ' ' && value[0] != ','))
		++value;

	while (value[0] && (value[0] == ' ' || value[0] == ','))
		++value;

	vector.Z = (float)std::atof(value);

	return vector;
}

template <>
Color3 readValue<Color3>(const tinyxml2::XMLAttribute* attribute)
{
	const char* value = attribute->Value();
	Color3 color;

	color.R = (float)std::atof(value);

	while (value[0] && (value[0] != ' ' && value[0] != ','))
		++value;

	while (value[0] && (value[0] == ' ' || value[0] == ','))
		++value;

	color.G = (float)std::atof(value);

	while (value[0] && (value[0] != ' ' && value[0] != ','))
		++value;

	while (value[0] && (value[0] == ' ' || value[0] == ','))
		++value;

	color.B = (float)std::atof(value);

	return color;
}

const char* adjustPath(const char* path)
{
	for (int i = 0; i < 3 && path[i]; ++i)
	{
		if (strncmp(path + i, "Data/", 5) == 0)
		{
			return path + i + 5;
		}
	}

	return path;
}

struct ItemAsset
{
	std::string NifPath;
	const Archive::Metadata::Entry* ModelEntry = nullptr;
	LoadedModel* Model = nullptr;
	std::string SelfNode;
	std::string TargetNode;
	std::string AttachNode;
	bool Replace = false;
	bool EarFold = false;
	bool HasPonytail = false;
	bool IsWeapon = false;
};

struct ItemSlotScale
{
	Vector3SF Value;
	float Min = 0;
	float Max = 0;
	bool Reverse = false;
};

struct ItemDecalTransform
{
	Vector3SF Position;
	Vector3SF Rotation;
	int TextureTransformId = -1;
};

struct ItemDecal
{
	std::string TexturePath;
	std::string ControlTexturePath;
	std::vector<ItemDecalTransform> Transforms;
	int Texture = -1;
	int ControlTexture = -1;
};

struct ItemSlot
{
	std::string Name;
	std::vector<ItemAsset> Assets;
	std::vector<ItemSlotScale> Scales;
	std::vector<ItemDecal> Decals;
};

struct ItemCustomizationFlags
{
	bool HairScale = false;
	bool HairPonytail = false;
	bool FaceDecorTranslation = false;
	bool FaceDecorRotation = false;
	bool FaceDecorScale = false;
	bool HatRotationX = false;
	bool HatRotationY = false;
	bool HatRotationZ = false;
	bool HatScale = false;
	bool HatAttach = false;
	bool HasDefaultHatTransform = false;
	Matrix4F DefaultHatTransform;
};

struct ItemModel
{
	int Id = 0;
	std::string Name;
	std::vector<ItemSlot> Slots;
	std::vector<std::string> Cutting;
	ItemCustomizationFlags Customization;
};

std::unordered_map<int, ItemModel> maleItems;
std::unordered_map<int, ItemModel> femaleItems;

const ItemModel* LoadItem(const Character& character, const Item& item)
{
	if (item.Id == 0) return nullptr;

	const std::unordered_map<int, ItemModel>& itemMap = character.Gender == Gender::Male ? maleItems : femaleItems;
	const auto& itemIndex = itemMap.find(item.Id);

	if (itemIndex != itemMap.end())
	{
		return &itemIndex->second;
	}

	std::stringstream idString;
	idString << item.Id;

	std::string id = idString.str();
	char itemDir[6] = {
		((item.Id / 10000000) % 10) + '0',
		'/',
		((item.Id / 1000000) % 10) + '0',
		((item.Id / 100000) % 10) + '0',
		'/',
		0
	};

	Archive::ArchivePath file = Reader.GetPath("Xml/Item/" + std::string(itemDir) + (id + ".xml"));

	if (!file.Loaded())
	{
		std::cout << "failed to load item " << file.GetPath().string() << std::endl;
		return nullptr;
	}

	tinyxml2::XMLDocument document;

	file.Read(documentBuffer);
	document.Parse(documentBuffer.data(), documentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();
	tinyxml2::XMLElement* envElement = nullptr;

	SupportSettings feature;
	SupportSettings locale;

	ItemModel& model = (character.Gender == Gender::Male ? maleItems : femaleItems)[item.Id];
	
	model.Id = item.Id;

	for (tinyxml2::XMLElement* currentEnvElement = rootElement->FirstChildElement(); currentEnvElement; currentEnvElement = currentEnvElement->NextSiblingElement())
	{
		if (!isNodeEnabled(currentEnvElement, &feature, &locale))
			continue;

		envElement = currentEnvElement;
	}

	for (tinyxml2::XMLElement* componentElement = envElement->FirstChildElement(); componentElement; componentElement = componentElement->NextSiblingElement())
	{
		const char* name = componentElement->Name();

		if (strcmp(name, "slots") == 0)
		{
			for (tinyxml2::XMLElement* slotElement = componentElement->FirstChildElement(); slotElement; slotElement = slotElement->NextSiblingElement())
			{
				model.Slots.push_back(ItemSlot{});

				ItemSlot& slot = model.Slots.back();

				slot.Name = readAttribute<const char*>(slotElement, "name", "");

				for (tinyxml2::XMLElement* attributeElement = slotElement->FirstChildElement(); attributeElement; attributeElement = attributeElement->NextSiblingElement())
				{
					const char* attributeName = attributeElement->Name();

					if (strcmp(attributeName, "asset") == 0)
					{
						Gender gender = (Gender)readAttribute<int>(attributeElement, "gender", 2);

						if (gender != Gender::Either && gender != character.Gender) continue;

						slot.Assets.push_back(ItemAsset{});

						ItemAsset& asset = slot.Assets.back();

						const char* nifPath = readAttribute<const char*>(attributeElement, "name", "");

						if (strncmp(nifPath, "urn:", 4) == 0)
						{
							int lastColon = 3;

							for (int i = 4; nifPath[i]; ++i)
								if (nifPath[i] == ':')
									lastColon = i;

							if (nifPath[lastColon + 1])
							{
								asset.ModelEntry = Archive::Metadata::Entry::FindFirstEntryByTags(nifPath + lastColon + 1, "gamebryo-scenegraph");

								if (asset.ModelEntry)
								{
									asset.NifPath = "Resource" + asset.ModelEntry->RelativePath.string();
									asset.Model = getModel(asset.ModelEntry, slot.Name == "HR");
								}
							}
						}
						else
						{
							asset.NifPath = nifPath + 5;
							asset.ModelEntry = Archive::Metadata::Entry::FindFirstEntryByTagWithRelPath(nifPath + 5 + 8, "gamebryo-scenegraph");
							asset.Model = getModel(asset.ModelEntry, slot.Name == "HR");
						}

						asset.SelfNode = readAttribute<const char*>(attributeElement, "selfnode", "");
						asset.TargetNode = readAttribute<const char*>(attributeElement, "targetnode", "");
						asset.AttachNode = readAttribute<const char*>(attributeElement, "attachnode", "");
						asset.Replace = readAttribute<int>(attributeElement, "replace", 0) != 0;
						asset.EarFold = readAttribute<int>(attributeElement, "earfold", 0) != 0;
						asset.HasPonytail = readAttribute<int>(attributeElement, "pony", 0) != 0;
						asset.IsWeapon = readAttribute<int>(attributeElement, "weapon", 0) != 0;

						continue;
					}

					if (strcmp(attributeName, "scale") == 0)
					{
						slot.Scales.push_back(ItemSlotScale{});

						ItemSlotScale& scale = slot.Scales.back();

						scale.Value = readAttribute<Vector3SF>(attributeElement, "value", Vector3SF());
						scale.Min = readAttribute<float>(attributeElement, "min", 0);
						scale.Max = readAttribute<float>(attributeElement, "max", 0);
						scale.Reverse = readAttribute<int>(attributeElement, "reverse", 0) != 0;

						continue;
					}

					if (strcmp(attributeName, "decal") == 0)
					{
						slot.Decals.push_back(ItemDecal{});

						ItemDecal& decal = slot.Decals.back();

						decal.TexturePath = adjustPath(readAttribute<const char*>(attributeElement, "texture", ""));
						decal.ControlTexturePath = adjustPath(readAttribute<const char*>(attributeElement, "controlTexture", ""));

						for (tinyxml2::XMLElement* customElement = attributeElement->FirstChildElement(); customElement; customElement = customElement->NextSiblingElement())
						{
							if (strcmp(customElement->Name(), "custom") != 0)
								continue;

							decal.Transforms.push_back(ItemDecalTransform{});

							ItemDecalTransform& transform = decal.Transforms.back();

							transform.Position = readAttribute<Vector3SF>(customElement, "position", {});
							transform.Rotation = readAttribute<Vector3SF>(customElement, "rotation", {});
							transform.TextureTransformId = (int)helloVkPtr->textureTransforms.size();
							
							helloVkPtr->textureTransforms.push_back(TextureTransform{});
							
							TextureTransform& textureTransform = helloVkPtr->textureTransforms.back();
							textureTransform.scale = { 1, 1 };
							textureTransform.translation = { -transform.Position.X, -transform.Position.Y };
							textureTransform.pivot = { 0.5f, 0.5f };
							textureTransform.rotation = -transform.Rotation.Z;// *PI / 180;
							textureTransform.mode = 1;
							
							if (slot.Scales.size() > 0)
							{
								textureTransform.scale = { 1 / slot.Scales[0].Value.X, 1 / slot.Scales[0].Value.X };
							}
						}

						VkSamplerCreateInfo sampler = HelloVulkan::GetDefaultSampler();
						sampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
						sampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
						sampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;

						decal.Texture = helloVkPtr->GetTexture(decal.TexturePath, VK_FORMAT_R8G8B8A8_UNORM, sampler);
						decal.ControlTexture = helloVkPtr->GetTexture(decal.ControlTexturePath, VK_FORMAT_R8G8B8A8_UNORM, sampler);

						continue;
					}

					attributeName += 0;
				}
			}

			continue;
		}

		if (strcmp(name, "cutting") == 0)
		{
			for (tinyxml2::XMLElement* meshElement = componentElement->FirstChildElement(); meshElement; meshElement = meshElement->NextSiblingElement())
			{
				if (strcmp(meshElement->Name(), "mesh") != 0)
					continue;
				
				if ((Gender)readAttribute<int>(meshElement, "gender", 2) != character.Gender) continue;

				model.Cutting.push_back(readAttribute<const char*>(meshElement, "name", ""));
			}

			continue;
		}

		if (strcmp(name, "customize") == 0)
		{
			for (tinyxml2::XMLElement* slotElement = componentElement->FirstChildElement(); slotElement; slotElement = slotElement->NextSiblingElement())
			{
				const char* slotName = slotElement->Name();

				if (strcmp(slotName, "HR") == 0)
				{
					model.Customization.HairScale = readAttribute<int>(slotElement, "scale", 0) != 0;
					model.Customization.HairPonytail = readAttribute<int>(slotElement, "pony", 0) != 0;

					continue;
				}

				if (strcmp(slotName, "FD") == 0)
				{
					model.Customization.FaceDecorTranslation = readAttribute<int>(slotElement, "translation", 0) != 0;
					model.Customization.FaceDecorRotation = readAttribute<int>(slotElement, "rotation", 0) != 0;
					model.Customization.FaceDecorScale = readAttribute<int>(slotElement, "scale", 0) != 0;

					continue;
				}

				if (strcmp(slotName, "CP") == 0)
				{
					model.Customization.HatRotationX = readAttribute<int>(slotElement, "xrotation", 0) != 0;
					model.Customization.HatRotationY = readAttribute<int>(slotElement, "yrotation", 0) != 0;
					model.Customization.HatRotationZ = readAttribute<int>(slotElement, "zrotation", 0) != 0;
					model.Customization.HatScale = readAttribute<int>(slotElement, "scale", 0) != 0;
					model.Customization.HatAttach = readAttribute<int>(slotElement, "attach", 0) != 0;

					for (tinyxml2::XMLElement* transformElement = slotElement->FirstChildElement(); transformElement; transformElement = transformElement->NextSiblingElement())
					{
						if (strcmp(transformElement->Name(), "transform") != 0)
							continue;

						model.Customization.HasDefaultHatTransform = true;

						Vector3SF position = readAttribute<Vector3SF>(transformElement, "position", {});
						Vector3SF rotation = readAttribute<Vector3SF>(transformElement, "rotation", {});
						float scale = readAttribute<float>(transformElement, "scale", 1);

						model.Customization.DefaultHatTransform = getMatrix(position, rotation, scale, false);
					}

					continue;
				}
			}

			continue;
		}
	}

	helloVkPtr->flushNewTextures();

	return &model;
}

struct EquippedSlot
{
	const Item* Customization = nullptr;
	const ItemModel* Item = nullptr;
	const ItemSlot* Slot = nullptr;
	bool Replaces = false;
};

struct LoadedCharacter
{
	Character* Customization = nullptr;
	bool HideEars = false;
	std::unordered_map<std::string, EquippedSlot> ActiveSlots;
	std::vector<std::string> CutMeshes;
	std::unordered_map<std::string, Matrix4F> Transforms;
};

template <typename T>
bool contains(const std::vector<T>& vector, const T& searchFor)
{
	for (const T& value : vector)
		if (value == searchFor)
			return true;

	return false;
}

void EquipItem(LoadedCharacter& character, const ItemModel* item, Item& customization)
{
	if (item == nullptr) return;
	 
	for (const ItemSlot& slot : item->Slots)
	{
		if (!character.ActiveSlots.contains(slot.Name))
		{
			bool replaces = false;

			for (const ItemAsset& asset : slot.Assets)
			{
				character.HideEars |= asset.EarFold;
				replaces |= asset.Replace;
				character.Transforms[asset.TargetNode] = Matrix4F();

				if (asset.AttachNode != "")
					character.Transforms[asset.AttachNode] = Matrix4F();
			}

			character.ActiveSlots[slot.Name] = EquippedSlot{ &customization, item, &slot, replaces };
		}
		else
			item += 0;
	}

	for (const std::string& meshName : item->Cutting)
	{
		bool alreadyHas = false;

		if (!contains(character.CutMeshes, meshName))
		{
			character.CutMeshes.push_back(meshName);
		}
	}
}

void EquipItem(LoadedCharacter& character, Character& data, Item& item)
{
	EquipItem(character, LoadItem(data, item), item);
}

void LoadTab(LoadedCharacter& character, Character& data, EquipTab& equips)
{
	EquipItem(character, data, equips.Hat);
	EquipItem(character, data, equips.Shirt);
	EquipItem(character, data, equips.Pants);
	EquipItem(character, data, equips.Gloves);
	EquipItem(character, data, equips.Shoes);
	EquipItem(character, data, equips.Earring);
	EquipItem(character, data, equips.Pendant);
	EquipItem(character, data, equips.Ring);
	EquipItem(character, data, equips.Cape);
	EquipItem(character, data, equips.Belt);
	EquipItem(character, data, equips.Weapon);
}

EmotionTexture GetFace(Gender gender, const std::string& emotionName, int index, int id)
{
	std::unordered_map<std::string, Emotion>& container = gender == Gender::Male ? maleEmotions : femaleEmotions;

	const auto emotionIndex = container.find(emotionName);

	const Emotion& emotion = emotionIndex != container.end() ? emotionIndex->second : container["default"];

	index = std::min((int)emotion.Faces.size() - 1, std::max(0, index));

	const EmotionTexture& faceData = emotion.Faces[index];
	EmotionTexture face = { faceData.File, faceData.Control };

	id %= 10000000;

	for (int i = 0; i < 8; ++i)
	{
		int digit = id % 10;
		id /= 10;

		face.File[10 + 7 - i] = '0' + digit;
		face.Control[10 + 7 - i] = '0' + digit;
	}

	return face;
}

void LoadCharacter(Character& data, const Matrix4F transform = Matrix4F())
{
	LoadedCharacter character{ &data };
	EquipItem(character, data, data.Face);
	EquipItem(character, data, data.FaceDecor);

	LoadTab(character, data, data.Cosmetics);
	LoadTab(character, data, data.Gear);

	EquipItem(character, data, data.Hair);

	std::string rigPath = data.Gender == Gender::Male ? "/Model/Character/male/m_body.nif" : "/Model/Character/female/f_body.nif";

	const Archive::Metadata::Entry* rigEntry = Archive::Metadata::Entry::FindFirstEntryByTagWithRelPath(rigPath, "gamebryo-scenegraph");

	LoadedModel* rig = getModel(rigEntry, true);

	if (character.HideEars)
		character.CutMeshes.push_back("FA_EA");

	DyeColor dyeColor = data.SkinColor;
	bool spawningRig = true;

	EquippedSlot* currentSlot = nullptr;

	const auto faceDecor = character.ActiveSlots.find("FD");

	EmotionTexture face = GetFace(data.Gender, data.Emotion, data.EmotionFrame, data.Face.Id);

	const auto spawnCallback = [&character, &dyeColor, &spawningRig, &currentSlot, &faceDecor, &face](LoadedModel* model, size_t i, InstDesc& instance)
	{
		const std::string& meshName = model->NodeNames[i];

		if (contains(character.CutMeshes, meshName))
			return false;

		const auto equippedIndex = character.ActiveSlots.find(meshName.substr(0, 2));

		if (spawningRig && equippedIndex != character.ActiveSlots.end() && equippedIndex->second.Replaces && meshName != "FA_EA")
			return false;

		const DyeColor& color = model->Shaders[i] == "MS2CharacterSkinMaterial" ? character.Customization->SkinColor : dyeColor;

		instance.primaryColor = vec3(color.Primary.R, color.Primary.G, color.Primary.B);
		instance.secondaryColor = vec3(color.Secondary.R, color.Secondary.G, color.Secondary.B);

		if (meshName == "FA")
		{
			instance.flags |= 2;
		}

		if (currentSlot != nullptr && (currentSlot->Slot->Decals.size() > 0 || currentSlot->Slot->Name == "FA"))
		{
			instance.textureOverride = (int)helloVkPtr->textureOverrides.size();

			helloVkPtr->textureOverrides.push_back(model->Materials[i].textures);

			MaterialTextures& overrides = helloVkPtr->textureOverrides.back();

			for (const ItemDecal& decal : currentSlot->Slot->Decals)
			{
				int preset = std::max(-1, std::min((int)decal.Transforms.size() - 1, currentSlot->Customization->Preset));

				if (decal.Texture != -1)
				{
					overrides.decal.id = decal.Texture;

					if (decal.Transforms.size() > 0)
					{
						overrides.decal.transformId = decal.Transforms[preset].TextureTransformId;
					}
				}

				if (decal.ControlTexture != -1)
				{
					overrides.colorOverride.id = decal.ControlTexture;

					if (decal.Transforms.size() > 0)
					{
						overrides.colorOverride.transformId = decal.Transforms[preset].TextureTransformId;
					}
				}
			}

			if (currentSlot->Slot->Name == "FA" && model->NodeNames[i] == "FA")
			{
				int diffuseTexture = helloVkPtr->GetTexture("Resource/Model/Textures/" + face.File, VK_FORMAT_R8G8B8A8_UNORM);
				int controlTexture = helloVkPtr->GetTexture("Resource/Model/Textures/" + face.Control, VK_FORMAT_R8G8B8A8_UNORM);

				if (diffuseTexture != -1)
				{
					overrides.diffuse.id = diffuseTexture;
				}

				if (controlTexture != -1)
				{
					overrides.colorOverride.id = controlTexture;
				}
			}

			if (currentSlot->Slot->Name == "FA" && model->NodeNames[i] == "FA_Skin" && faceDecor != character.ActiveSlots.end())
			{
				for (const ItemDecal& decal : faceDecor->second.Slot->Decals)
				{
					int preset = std::max(-1, std::min((int)decal.Transforms.size() - 1, faceDecor->second.Customization->Preset));

					if (decal.Texture != -1)
					{
						overrides.decal.id = decal.Texture;

						if (decal.Transforms.size() > 0)
						{
							overrides.decal.transformId = decal.Transforms[preset].TextureTransformId;
						}
					}

					if (decal.ControlTexture != -1)
					{
						overrides.colorOverride.id = decal.ControlTexture;

						if (decal.Transforms.size() > 0)
						{
							overrides.colorOverride.transformId = decal.Transforms[preset].TextureTransformId;
						}
					}
				}
			}
		}

		return true;
	};

	spawnModel(rig, transform, spawnCallback);

	spawningRig = false;

	for (size_t i = 0; i < rig->Transformations.size(); ++i)
	{
		const auto transformIndex = character.Transforms.find(rig->NodeNames[i]);

		if (transformIndex != character.Transforms.end())
			transformIndex->second = rig->Transformations[i];
	}

	std::vector<const ItemModel*> addedModels;

	Matrix4F hatTransform;

	for (auto& activeSlot : character.ActiveSlots)
	{
		currentSlot = &activeSlot.second;

		const ItemSlot* slot = currentSlot->Slot;

		dyeColor = currentSlot->Customization->Color;

		if (currentSlot->Item->Customization.HasDefaultHatTransform)
		{
			const auto transformIndex = character.Transforms.find("HR");

			if (transformIndex != character.Transforms.end())
				hatTransform = currentSlot->Item->Customization.DefaultHatTransform;
		}

		for (const ItemAsset& asset : slot->Assets)
		{
			Matrix4F assetTransform;

			const auto transformIndex = character.Transforms.find(asset.TargetNode);

			if (transformIndex != character.Transforms.end())
				assetTransform = transformIndex->second;

			if (slot->Name == "CP")
				assetTransform = assetTransform * hatTransform;
			
			for (size_t i = 0; i < asset.Model->NodeNames.size(); ++i)
			{
				if (asset.SelfNode == asset.Model->NodeNames[i].substr(0, asset.SelfNode.size()))
				{
					assetTransform = assetTransform * asset.Model->Transformations[i].Inverted();

					break;
				}
			}

			spawnModel(asset.Model, transform * assetTransform, spawnCallback);
		}
	}
}

void LoadEntity(EntityData& entity, tinyxml2::XMLElement* entityElement)
{
	entity.Id = readAttribute<const char*>(entityElement, "id", "");

	const Archive::Metadata::Entry* modelEntry = nullptr;

	for (tinyxml2::XMLElement* traitElement = entityElement->FirstChildElement(); traitElement; traitElement = traitElement->NextSiblingElement())
	{
		const char* name = readAttribute<const char*>(traitElement, "name", "");
		tinyxml2::XMLElement* setElement = traitElement->FirstChildElement("set");

		if (setElement == nullptr)
		{
			if (strcmp(name, "Light") == 0)
			{
				entity.IsLight = true;

				continue;
			}
			
			if (strcmp(name, "Portal") == 0)
			{
				entity.IsPortal = true;

				continue;
			}
			
			if (strcmp(name, "DirectionalLight") == 0)
			{
				entity.Light.Type = EntityLightType::Directional;

				continue;
			}

			if (strcmp(name, "PointLight") == 0)
			{
				entity.Light.Type = EntityLightType::Point;

				continue;
			}

			if (strcmp(name, "AmbientLight") == 0)
			{
				entity.Light.Type = EntityLightType::Ambient;

				continue;
			}

			continue;
		}

		if (strcmp(name, "Position") == 0)
		{
			entity.Position = readAttribute<Vector3SF>(setElement, "value", Vector3SF());

			continue;
		}

		if (strcmp(name, "Rotation") == 0)
		{
			entity.Rotation = readAttribute<Vector3SF>(setElement, "value", Vector3SF());

			continue;
		}

		if (strcmp(name, "Scale") == 0)
		{
			entity.Scale = readAttribute<float>(setElement, "value", 1);

			continue;
		}

		if (strcmp(name, "VisualizerOffset") == 0)
		{
			entity.VisualOffset = readAttribute<Vector3SF>(setElement, "value", Vector3SF());

			continue;
		}

		if (strcmp(name, "NifAsset") == 0)// || strcmp(name, "ProxyNifAsset") == 0)
		{
			const char* uuid = readAttribute<const char*>(setElement, "value", "urn:llid:null") + 9;

			modelEntry = Archive::Metadata::Entry::FindFirstEntryByTagsWithLink(Archive::ParseHexInt(uuid, 0), "gamebryo-scenegraph");

			continue;
		}

		if (strcmp(name, "IsVisible") == 0 && false)
		{
			entity.IsVisible = lower(readAttribute<const char*>(setElement, "value", "true")) == "true";

			continue;
		}

		if (strcmp(name, "MaterialColor") == 0)
		{
			entity.MaterialColor = readAttribute<Color3>(setElement, "value", Color3(1.f, 1, 1));

			continue;
		}

		if (entity.IsPortal)
		{
			if (strcmp(name, "TargetFieldSN") == 0)
			{
				entity.TargetField = padId(readAttribute<std::string>(setElement, "value", ""));

				continue;
			}

			if (strcmp(name, "TargetPortalID") == 0)
			{
				entity.TargetPortal = readAttribute<int>(setElement, "value", -1);

				continue;
			}

			if (strcmp(name, "PortalID") == 0)
			{
				entity.PortalId = readAttribute<int>(setElement, "value", -1);

				continue;
			}
		}

		if (entity.IsLight)
		{
			if (strcmp(name, "Dimmer") == 0)
			{
				entity.Light.Dimmer = readAttribute<float>(setElement, "value", 0);

				continue;
			}

			if (strcmp(name, "DiffuseColor") == 0)
			{
				entity.Light.DiffuseColor = readAttribute<Color3>(setElement, "value", Color3(0.f, 0, 0));

				continue;
			}

			if (strcmp(name, "SpecularColor") == 0)
			{
				entity.Light.SpecularColor = readAttribute<Color3>(setElement, "value", Color3(0.f, 0, 0));

				continue;
			}

			if (strcmp(name, "AmbientColor") == 0)
			{
				entity.Light.AmbientColor = readAttribute<Color3>(setElement, "value", Color3(0.f, 0, 0));

				continue;
			}

			if (strcmp(name, "CastShadows") == 0)
			{
				entity.Light.CastsShadows = lower(readAttribute<const char*>(setElement, "value", "false")) == "true";

				continue;
			}

			if (strcmp(name, "Range") == 0)
			{
				entity.Light.Range = readAttribute<float>(setElement, "value", 0);

				continue;
			}
		}
	}

	if (modelEntry != nullptr && modelEntry != entity.ModelEntry && entity.IsVisible)
	{
		entity.Model = getModel(modelEntry);
		entity.ModelEntry = modelEntry;
	}

	if (entity.IsVisible && entity.Model == nullptr && modelEntry != nullptr)
	{
		entity.Model = getModel(modelEntry);
	}

	entity.Transformation = getMatrix(entity.Position, entity.Rotation, entity.Scale);

	if (entity.IsLight)
	{
		entity.Light.Position = entity.Position;
		entity.Light.Direction = entity.Transformation.FrontVector();
		entity.Light.Scale = entity.Scale;
		entity.Light.Enabled = entity.IsVisible;
	}
}

EntityData* loadFlat(const std::string& name)
{
	const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTags(name, "emergent-flat-model");

	const auto& cachedFlat = loadedFlats.find(entry);

	if (cachedFlat != loadedFlats.end())
		return &cachedFlat->second;

	if (entry == nullptr)
		return nullptr;

	Archive::ArchivePath flatFile = Reader.GetPath("Resource" + entry->RelativePath.string());

	if (!flatFile.Loaded())
	{
		std::cout << "failed to load map resource: " << flatFile.GetPath().string() << std::endl;
		return nullptr;
	}

	loadedFlats[entry] = EntityData();
	EntityData& flat = loadedFlats[entry];

	flat.Entry = entry;

	tinyxml2::XMLDocument document;

	flatFile.Read(documentBuffer);
	document.Parse(documentBuffer.data(), documentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();

	LoadEntity(flat, rootElement);

	return &flat;
}

void loadMap(const std::string& mapId)
{
	Archive::ArchivePath mapFile = Reader.GetPath("Xml/map/" + padId(mapId) + ".xml");

	if (!mapFile.Loaded())
	{
		std::cout << "failed to load map: " << mapFile.GetPath().string() << std::endl;
		return;
	}

	std::string xblockName;

	{
		tinyxml2::XMLDocument document;

		mapFile.Read(documentBuffer);
		document.Parse(documentBuffer.data(), documentBuffer.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		SupportSettings feature;
		SupportSettings locale;

		for (tinyxml2::XMLElement* envElement = rootElement->FirstChildElement(); envElement; envElement = envElement->NextSiblingElement())
		{
			if (!isNodeEnabled(envElement, &feature, &locale))
				continue;

			tinyxml2::XMLElement* xblock = envElement->FirstChildElement("xblock");

			if (xblock != nullptr)
				xblockName = readAttribute<std::string>(xblock, "name", "");
		}
	}

	const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTags(xblockName, "emergent-world");

	if (entry == nullptr)
		return;

	Archive::ArchivePath xblockFile = Reader.GetPath("Resource/" + entry->RelativePath.string());

	if (!xblockFile.Loaded())
	{
		std::cout << "failed to load map " << xblockFile.GetPath().string() << std::endl;
		return;
	}

	tinyxml2::XMLDocument document;

	xblockFile.Read(flatDocumentBuffer);
	document.Parse(flatDocumentBuffer.data(), flatDocumentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();
	tinyxml2::XMLElement* entitySet = rootElement->FirstChildElement("entitySet");

	if (entitySet == nullptr) return;

	mapIndices[mapId] = (int)loadedMaps.size();
	loadedMaps.push_back(LoadedMap{ mapId, mapNames[mapId], {}, ms2ToWorld, xblockFile.GetPath().string()});

	size_t directionalLight = -1;

	EntityLight ambient;
	bool hasAmbient = false;

	for (tinyxml2::XMLElement* entityElement = entitySet->FirstChildElement(); entityElement; entityElement = entityElement->NextSiblingElement())
	{
		std::string entityName = readAttribute<const char*>(entityElement, "name", "");
		std::string modelName = readAttribute<std::string>(entityElement, "modelName", "");

		EntityData* flat = loadFlat(modelName);

		if (flat == nullptr)
			flat = loadFlat(modelName);
		LoadedModel* model = flat->Model;

		if (flat == nullptr)
			continue;

		EntityData entity = *flat;

		LoadEntity(entity, entityElement);

		if (entity.IsLight && loadLights)
		{
			if (entity.Light.Type == EntityLightType::Ambient)
			{
				hasAmbient = true;
				ambient = entity.Light;
			}
			else
			{
				Vector3F direction = -(/*ms2ToWorld */ entity.Transformation.FrontVector()).Unit();
				Vector3F position = /*ms2ToWorld */ Vector3F(entity.Position, 1);

				helloVkPtr->lights.push_back(LightDesc{});

				LightDesc& light = helloVkPtr->lights.back();

				if (entity.Light.Type == EntityLightType::Directional && directionalLight == -1)
					directionalLight = helloVkPtr->lights.size() - 1;

				light.position = vec3(position.X, position.Y, position.Z);
				light.direction = vec3(direction.X, direction.Y, direction.Z);
				light.brightness = entity.Light.Dimmer;
				light.type = (int)entity.Light.Type;
				light.range = entity.Light.Range;
				light.diffuse = vec3(entity.Light.DiffuseColor.R, entity.Light.DiffuseColor.G, entity.Light.DiffuseColor.B);
				light.specular = vec3(entity.Light.SpecularColor.R, entity.Light.SpecularColor.G, entity.Light.SpecularColor.B);
				light.ambient = vec3(entity.Light.AmbientColor.R, entity.Light.AmbientColor.G, entity.Light.AmbientColor.B);
				light.castsShadows = entity.Light.CastsShadows;
			}
		}

		model = entity.Model;
		
		if (model == nullptr)
			continue;

		SpawnedEntity* newModel = spawnModel(model, entity.Transformation, [&entity](LoadedModel* model, size_t i, InstDesc& instance)
			{
				instance.color = vec3(entity.MaterialColor.R, entity.MaterialColor.G, entity.MaterialColor.B);
				instance.flags = entity.IsVisible ? 0 : 1;

				return true;
			}
		);// *flat->Transformation);
		newModel->Id = entity.Id;
		newModel->Name = entityName;
		newModel->Flat = flat;
		newModel->Position = entity.Position;
		newModel->WorldPosition = ms2ToWorld * Vector3F(entity.Position, 1);
		newModel->MapIndex = (int)loadedMaps.size() - 1;
		newModel->LineNumber = entityElement->GetLineNum();

		if (entity.IsPortal)
		{
			newModel->PortalIndex = (int)spawnedPortals.size();
			loadedMaps.back().Portals[entity.PortalId] = (int)spawnedEntities.size() - 1;

			spawnedPortals.push_back(SpawnedPortal{ entity.TargetField, entity.TargetPortal, entity.PortalId });
		}
	}

	if (hasAmbient && directionalLight == -1)
	{
		helloVkPtr->lights.push_back(LightDesc{});

		LightDesc& light = helloVkPtr->lights.back();

		light.brightness = ambient.Dimmer;
		light.type = (int)ambient.Type;
		light.range = ambient.Range;
		light.diffuse = vec3(ambient.DiffuseColor.R, ambient.DiffuseColor.G, ambient.DiffuseColor.B);
		light.specular = vec3(ambient.SpecularColor.R, ambient.SpecularColor.G, ambient.SpecularColor.B);
		light.ambient = vec3(ambient.AmbientColor.R, ambient.AmbientColor.G, ambient.AmbientColor.B);
		light.castsShadows = ambient.CastsShadows;
	}
	else if (hasAmbient && directionalLight != -1)
	{
		LightDesc& light = helloVkPtr->lights[directionalLight];

		light.ambient += (ambient.Dimmer / light.brightness) * vec3(ambient.AmbientColor.R, ambient.AmbientColor.G, ambient.AmbientColor.B);
	}
}

void loadMapNames(const Archive::ArchivePath& file)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load map names " << file.GetPath().string() << std::endl;
		return;
	}

	tinyxml2::XMLDocument document;

	file.Read(documentBuffer);
	document.Parse(documentBuffer.data(), documentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();

	for (tinyxml2::XMLElement* keyElement = rootElement->FirstChildElement(); keyElement; keyElement = keyElement->NextSiblingElement())
	{
		mapNames[readAttribute<std::string>(keyElement, "id", "")] = readAttribute<std::string>(keyElement, "name", "");
	}
}

void loadDyes(const Archive::ArchivePath& file, std::vector<DyeColorInfo>& container)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load dyes " << file.GetPath().string() << std::endl;
		return;
	}

	tinyxml2::XMLDocument document;

	file.Read(documentBuffer);

	document.Parse(documentBuffer.data(), documentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();

	for (tinyxml2::XMLElement* paletteElement = rootElement->FirstChildElement(); paletteElement; paletteElement = paletteElement->NextSiblingElement())
	{
		int paletteId = readAttribute<int>(paletteElement, "id", 0);

		for (tinyxml2::XMLElement* colorElement = paletteElement->FirstChildElement(); colorElement; colorElement = colorElement->NextSiblingElement())
		{
			DyeColorInfo dyeColor;

			dyeColor.Palette = paletteId;
			dyeColor.Index = readAttribute<int>(colorElement, "colorSN", 0);
			dyeColor.Id = readAttribute<int>(colorElement, "stringKey", 0);
			char* pointer;

			unsigned long ch0 = strtoul(readAttribute<const char*>(colorElement, "ch0", "0xFFFFFFFF") + 2, &pointer, 16);
			unsigned long ch1 = strtoul(readAttribute<const char*>(colorElement, "ch1", "0xFFFFFFFF") + 2, &pointer, 16);
			unsigned long ch2 = strtoul(readAttribute<const char*>(colorElement, "ch2", "0xFFFFFFFF") + 2, &pointer, 16);
			unsigned long display = strtoul(readAttribute<const char*>(colorElement, "palette", "0xFFFFFFFF") + 2, &pointer, 16);

			dyeColor.DisplayBoth = readAttribute<int>(colorElement, "show2color", 0) == 1;

			unsigned long ch0_eye = 0xFFFFFFFF;
			unsigned long ch2_eye = 0xFFFFFFFF;

			const char* ch0_eyeStr = readAttribute<const char*>(colorElement, "ch0_eye", nullptr);
			const char* ch2_eyeStr = readAttribute<const char*>(colorElement, "ch2_eye", nullptr);

			dyeColor.HasEyeOverride = ch0_eyeStr != nullptr && ch2_eyeStr != nullptr;

			if (dyeColor.HasEyeOverride)
			{
				ch0_eye = strtoul(ch0_eyeStr + 2, &pointer, 16);
				ch2_eye = strtoul(ch2_eyeStr + 2, &pointer, 16);
			}

			const auto loadColor = [](unsigned int color) -> Color4
			{
				unsigned int alpha = (color & 0xFF000000) >> 24;
				color <<= 8;
				return Color4(color | alpha);
			};

			dyeColor.Primary = loadColor((unsigned int)ch0);
			dyeColor.Secondary = loadColor((unsigned int)ch2);
			dyeColor.Unused = loadColor((unsigned int)ch1);
			dyeColor.Display = loadColor((unsigned int)display);
			dyeColor.EyePrimary = loadColor((unsigned int)ch0_eye);
			dyeColor.EyeSecondary = loadColor((unsigned int)ch2_eye);

			container.push_back(dyeColor);
		}
	}
}

void loadDyeNames(const Archive::ArchivePath& file, std::vector<DyeColorInfo>& container)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load dye names " << file.GetPath().string() << std::endl;
		return;
	}

	tinyxml2::XMLDocument document;

	file.Read(documentBuffer);
	document.Parse(documentBuffer.data(), documentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();

	for (tinyxml2::XMLElement* keyElement = rootElement->FirstChildElement(); keyElement; keyElement = keyElement->NextSiblingElement())
	{
		int id = readAttribute<int>(keyElement, "id", 0);

		for (DyeColorInfo& dyeColor : container)
		{
			if (dyeColor.Id == id)
			{
				dyeColor.Name = readAttribute<std::string>(keyElement, "name", "");

				if (dyeColor.Name != "")
					dyeColorMap[lower(dyeColor.Name)] = &dyeColor;
			}
		}
	}
}

void loadEmotions(const Archive::ArchivePath& file, std::unordered_map<std::string, Emotion>& container)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load emotions " << file.GetPath().string() << std::endl;
		return;
	}

	tinyxml2::XMLDocument document;

	file.Read(documentBuffer);
	document.Parse(documentBuffer.data(), documentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();

	for (tinyxml2::XMLElement* emotionElement = rootElement->FirstChildElement(); emotionElement; emotionElement = emotionElement->NextSiblingElement())
	{
		std::string emotionName = readAttribute<std::string>(emotionElement, "name", "");

		Emotion& emotion = container[emotionName];

		for (tinyxml2::XMLElement* propertyElement = emotionElement->FirstChildElement(); propertyElement; propertyElement = propertyElement->NextSiblingElement())
		{
			const char* name = propertyElement->Name();

			if (strcmp(name, "anim") == 0)
			{
				emotion.Animation = readAttribute<std::string>(propertyElement, "name", "");

				continue;
			}

			if (strcmp(name, "idleAnim") == 0)
			{
				emotion.IdleAnimation = readAttribute<std::string>(propertyElement, "name", "");

				continue;
			}

			if (strcmp(name, "boreAnim") == 0)
			{
				emotion.BoreAnimation1 = readAttribute<std::string>(propertyElement, "name", "");

				size_t i = 0;

				for (i; i < emotion.BoreAnimation1.size() && emotion.BoreAnimation1[i] != ','; ++i);

				if (i < emotion.BoreAnimation1.size())
				{
					emotion.BoreAnimation2 = emotion.BoreAnimation1.substr(i + 1, emotion.BoreAnimation1.size() - i - 1);
					emotion.BoreAnimation1 = emotion.BoreAnimation1.substr(0, i);
				}

				continue;
			}

			if (strcmp(name, "textureani") == 0)
			{
				emotion.Target = readAttribute<std::string>(propertyElement, "target", "");

				for (tinyxml2::XMLElement* textureElement = propertyElement->FirstChildElement(); textureElement; textureElement = textureElement->NextSiblingElement())
				{
					emotion.Faces.push_back(EmotionTexture{});

					EmotionTexture& face = emotion.Faces.back();

					face.File = readAttribute<std::string>(textureElement, "file", "");
					face.Control = readAttribute<std::string>(textureElement, "control", "");
					face.Delay = readAttribute<int>(textureElement, "delay", 0);

					if (face.File.size() > 0)
						face.File = face.File.substr(0, 10) + "00000000" + face.File.substr(13, face.File.size() - 13);

					if (face.Control.size() > 0)
						face.Control = face.Control.substr(0, 10) + "00000000" + face.Control.substr(13, face.Control.size() - 13);
				}

				continue;
			}

			if (strcmp(name, "effect") == 0)
			{
				emotion.Effect = readAttribute<std::string>(propertyElement, "file", "");

				continue;
			}
		}
	}
}

DyeColor getDyeColor(const std::string& name, bool isEye = false)
{
	const auto& dyeIndex = dyeColorMap.find(lower(name));

	if (dyeIndex == dyeColorMap.end()) return DyeColor{};
	if (dyeIndex->second == nullptr) return DyeColor{};

	if (isEye && dyeIndex->second->HasEyeOverride)
		return DyeColor{ dyeIndex->second->EyePrimary, dyeIndex->second->EyeSecondary };

	return DyeColor{ dyeIndex->second->Primary, dyeIndex->second->Secondary };
}

DyeColor getDyeColor(int index, int palette = 11000072)
{
	for (const DyeColorInfo& color : dyeColors)
	{
		if (color.Palette == palette && color.Index == index)
			return DyeColor{ color.Primary, color.Secondary };
	}

	return DyeColor{};
}

//--------------------------------------------------------------------------------------------------
// Application Entry
//
int main(int argc, char** argv)
{
	const char* mapId = nullptr;

	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "--root") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2Root = argv[i];
		}

		if (strcmp(argv[i], "--rootExtracted") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find extracted root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2RootExtracted = argv[i];
		}

		if (strcmp(argv[i], "--locale") == 0 && ++i < argc)
		{
			localeName = argv[i];

			if (++i < argc)
			{
				environmentName = argv[i];
			}
		}

		if (strcmp(argv[i], "--map") == 0 && ++i < argc)
		{
			mapId = argv[i];
		}
	}

	std::cout << "using root path: " << ms2Root.string() << std::endl;
	std::cout << "path found: " << fs::exists(ms2Root) << std::endl;
	std::cout << "locale: " << localeName << "; env: " << environmentName << std::endl;

	Reader.Load(ms2Root / "Data", true);

	fs::path webMetaCache = "./cache/asset-web-metadata-cache";

	if (!Archive::Metadata::Entry::LoadCached(webMetaCache))
	{
		Archive::Metadata::Entry::LoadEntries(Reader, "Resource/asset-web-metadata", documentBuffer);
		Archive::Metadata::Entry::Cache(webMetaCache);
	}

	if (!loadFeatures(Reader.GetPath("Xml/table"), localeName, environmentName, documentBuffer)) return -1;

	std::cout << "loaded features" << std::endl;
	
	// Setup GLFW window
	glfwSetErrorCallback(onErrorCallback);
	if(!glfwInit())
	{
	return 1;
	}

	std::cout << "glfw initialized" << std::endl;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(SAMPLE_WIDTH, SAMPLE_HEIGHT, PROJECT_NAME, nullptr, nullptr);


	// Setup camera
	CameraManip.setWindowSize(SAMPLE_WIDTH, SAMPLE_HEIGHT);
	CameraManip.setLookat(vec3(5, 4, -4), vec3(0, 1, 0), vec3(0, 1, 0));

	// Setup Vulkan
	if(!glfwVulkanSupported())
	{
	printf("GLFW: Vulkan Not Supported\n");
	return 1;
	}

	// setup some basic things for the sample, logging file for example
	NVPSystem system(PROJECT_NAME);

	// Search path for shaders and other media
	defaultSearchPaths = {
		"./",
		NVPSystem::exePath()
	};

	// Vulkan required extensions
	assert(glfwVulkanSupported() == 1);
	uint32_t count{0};
	auto     reqExtensions = glfwGetRequiredInstanceExtensions(&count);

	// Requesting Vulkan extensions and layers
	nvvk::ContextCreateInfo contextInfo;
	contextInfo.setVersion(1, 2);                       // Using Vulkan 1.2
	for(uint32_t ext_id = 0; ext_id < count; ext_id++)  // Adding required extensions (surface, win32, linux, ..)
	contextInfo.addInstanceExtension(reqExtensions[ext_id]);
	contextInfo.addInstanceLayer("VK_LAYER_LUNARG_monitor", true);              // FPS in titlebar
	//contextInfo.addInstanceExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, true);  // Allow debug names
	contextInfo.addDeviceExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);            // Enabling ability to present rendering

	// #VKRay: Activate the ray tracing extension
	VkPhysicalDeviceAccelerationStructureFeaturesKHR accelFeature{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR};
	contextInfo.addDeviceExtension(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME, false, &accelFeature);  // To build acceleration structures
	VkPhysicalDeviceRayTracingPipelineFeaturesKHR rtPipelineFeature{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR};
	contextInfo.addDeviceExtension(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME, false, &rtPipelineFeature);  // To use vkCmdTraceRaysKHR
	contextInfo.addDeviceExtension(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);  // Required by ray tracing pipeline

	// Creating Vulkan base application
	nvvk::Context vkctx{};
	vkctx.initInstance(contextInfo);
	// Find all compatible devices
	auto compatibleDevices = vkctx.getCompatibleDevices(contextInfo);
	assert(!compatibleDevices.empty());
	// Use a compatible device
	vkctx.initDevice(compatibleDevices[0], contextInfo);

	// Create example
	HelloVulkan helloVk;

	helloVkPtr = &helloVk;
	helloVk.Reader = &Reader;

	// Window need to be opened to get the surface on which to draw
	const VkSurfaceKHR surface = helloVk.getVkSurface(vkctx.m_instance, window);
	vkctx.setGCTQueueWithPresent(surface);

	helloVk.setup(vkctx.m_instance, vkctx.m_device, vkctx.m_physicalDevice, vkctx.m_queueGCT.familyIndex);
	helloVk.createSwapchain(surface, SAMPLE_WIDTH, SAMPLE_HEIGHT);
	helloVk.createDepthBuffer();
	helloVk.createRenderPass();
	helloVk.createFrameBuffers();

	// Setup Imgui
	helloVk.initGUI(0);  // Using sub-pass 0

	loadDyes(Reader.GetPath("Xml/table/colorpalette.xml"), dyeColors);
	loadDyes(Reader.GetPath("Xml/table/na/colorpalette_achieve.xml"), dyeColorsNA);
	loadDyeNames(Reader.GetPath("Xml/string/en/stringcolorpalette.xml"), dyeColorsNA);
	loadEmotions(Reader.GetPath("Xml/emotion/common/femalecustom.xml"), femaleEmotions);
	loadEmotions(Reader.GetPath("Xml/emotion/common/malecustom.xml"), maleEmotions);

	loadMapNames(Reader.GetPath("Xml/string/en/mapname.xml"));

	std::vector<Engine::Graphics::VertexAttributeFormat> attributes;

	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "position", 0 });
	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 2, "textureCoords", 1 });
	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "normal", 2 });

	importFormat = Engine::Graphics::MeshFormat::GetFormat(attributes);

	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::UInt8, 4, "COLOR", 3 });

	importFormatWithColor = Engine::Graphics::MeshFormat::GetFormat(attributes);

	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "binormal", 4 });
	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "tangent", 5 });

	importFormatWithColorAndBinormal = Engine::Graphics::MeshFormat::GetFormat(attributes);

	attributes.resize(3);

	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "binormal", 3 });
	attributes.push_back(Engine::Graphics::VertexAttributeFormat{ Engine::Graphics::AttributeDataTypeEnum::Float32, 3, "tangent", 4 });

	importFormatWithBinormal = Engine::Graphics::MeshFormat::GetFormat(attributes);


	struct mapPlacement
	{
		std::string id;
		Matrix4F offset;
	};

	std::vector<mapPlacement> maps = {
		{ "02000001" }, // tria
		{ "02000064", Matrix4F(100, 6, 40) }, //queenstown
		{ "02000118", Matrix4F(-83, -3, 46) }, //north royal road
		{ "02000119", Matrix4F(24, 14, -87) }, //middleton
		{ "02000107", Matrix4F(-24, 13, -70) }, //beauty street
		{ "02000002", Matrix4F(-28, 4, 89) }, //evansville
		{ "52000186", Matrix4F(-103, 6, 104) * Matrix4F::YawRotation(PI) }, //frontier hq
		{ "02000117", Matrix4F(-112, 1, -37) }, //crooked canyon
		{ "02000116", Matrix4F(-157, -3, -18) }, //hushwood
		{ "02000115", Matrix4F(-182, -10, 43) }, //south royal road
		{ "02000114", Matrix4F(-210, -9, 61) }, //royal road plaza
		{ "02000062", Matrix4F(-272, -5, 60) }, //lith
		{ "02000087", Matrix4F(-10, -8, 141) }, //andrea barony
		{ "52000002", Matrix4F(78, 8, 71) }, //balmy farm
		{ "02000088", Matrix4F(61, -6, 134) }, //trinian crossing
		{ "02000006", Matrix4F(152, 5, 125) }, //ellin grove
		{ "02000089", Matrix4F(137, 34, 100) }, //torhara spring
		{ "02000036", Matrix4F(137, 5, 178) }, //decor haven
		{ "02000101", Matrix4F(157, 13, 172) }, //orne town
		{ "02000023", Matrix4F(182, -9, 190) }, //ellinia
		{ "02000005", Matrix4F(115, 10, 200) }, //ellin town
		{ "02000024", Matrix4F(228, 4, 204) }, //ellbos hollow
		{ "02000042", Matrix4F(40, -25, 203) }, //ellosylva
		{ "02000113", Matrix4F(64, -9, 282) }, //greenia falls
		{ "02000129", Matrix4F(112, -6, 265) }, //fungeeburg stump
		{ "02000183", Matrix4F(-92, -49, 208) }, //barbosa beach
		{ "02000182", Matrix4F(-31, -38, 223) }, //tidepool cliffs
		{ "02000063", Matrix4F(29, -11, 285) }, //cheliska bay
		{ "02000067", Matrix4F(14, -9, 360) }, //tortuga seaside cliffs
		{ "02000181", Matrix4F(117, -11, 286) }, //mirror castle
		{ "02000215", Matrix4F(229, 16, 135) }, //ellua forest path
		{ "02000112", Matrix4F(180, -17, 323) }, //godspring
		{ "02000102", Matrix4F(223, 6, 316) }, //eileen town
		{ "02000377", Matrix4F(-56, -9, 339) }, //coco island
		{ "02000053", Matrix4F(277, 18, 331) }, //corona lake
		{ "02000180", Matrix4F(143, -11, 370) }, //caustic garden
		{ "02000172", Matrix4F(288, -21, 390) }, //moonglow forest
		{ "02000004", Matrix4F(275, 8, 260) }, //trinket woods
		{ "02000131", Matrix4F(182, 1, 397) }, //overtop beanstalk
		{ "02000090", Matrix4F(340, 4, 350) }, //forest of lost memories
		{ "02000022", Matrix4F(231, 20, 82) }, //ellua riverside
		{ "02000132", Matrix4F(214, -13, 433) }, //rose castle
		{ "02000214", Matrix4F(281, -14, 460) }, //twin moonlight castle
		{ "02000103", Matrix4F(338, -6, 305) }, //baum tree
		{ "02000060", Matrix4F(319, 14, 242) }, //razed forest
		{ "02000108", Matrix4F(213, 8, 360) }, //forelle town
		{ "02000278", Matrix4F(212, -18, 482) }, //serene docks
		{ "02000048", Matrix4F(355, 8, 253) }, //stonehill dig site
		{ "02000128", Matrix4F(270, -1, 106) }, //great ellin tree
		{ "02000130", Matrix4F(312, 19, 25) }, //ellin ruins
		{ "02000096", Matrix4F(315, 29, 116) }, //lava springs
		{ "02000010", Matrix4F(424, 6, 209) }, //paruvan plateau
		{ "02000267", Matrix4F(420, 1, 295) }, //windsong ravine
		{ "02000003", Matrix4F(227, 42, 20) }, //verdant heights
		{ "02000095", Matrix4F(326, 15, 174) }, //picchu picchu gardens
		{ "02000051", Matrix4F(487, 6, 222) }, //perion
		{ "02000017", Matrix4F(154, 12, 8) }, //sylvan woods trail
		{ "02000059", Matrix4F(287, 40, -34) }, //loggers hill
		{ "02000217", Matrix4F(482, -6, 264) }, //brave peak
		{ "02000050", Matrix4F(436, 13, 170) }, //crows eye village
		{ "02000043", Matrix4F(213, 19, -35) }, //boulderwhite
		{ "02000041", Matrix4F(115, 8, -43) }, //fairy tree lake
		{ "02000085", Matrix4F(279, 56, -102) }, //frostheart
		{ "02000046", Matrix4F(391, 39, 170) }, //molten hourglass
		{ "02000168", Matrix4F(530, 16, 253) }, //serpent town
		{ "02000054", Matrix4F(338, 74, -67) }, //spectrumwood
		{ "02000045", Matrix4F(366, 21, 130) }, //bonebridge worksite
		{ "02000049", Matrix4F(539, 32, 180) }, //pigming clan altar
		{ "02000094", Matrix4F(597, 26, 273) }, //red wall
		{ "02000056", Matrix4F(361, 75, -12) }, //prism falls
		{ "02000039", Matrix4F(369, 40, 65) }, //hotottot river
		{ "02000169", Matrix4F(551, 22, 140) }, //whistler cliffs
		{ "02000133", Matrix4F(645, 26, 275) }, //highcliff temple
		{ "02000061", Matrix4F(620, 39, 255) }, //raptor dive pass
		{ "02000076", Matrix4F(370, 67, -88) }, //henesys
		{ "02000104", Matrix4F(407, 81, -12) }, //crystal vale
		{ "02000170", Matrix4F(526, 33, 100) }, //wolfclaw canyon
		{ "02000097", Matrix4F(690, 47, 233) }, //skyreach pass
		{ "02000203", Matrix4F(398, 73, -123) }, //nerman forge
		{ "02000058", Matrix4F(468, 89, -35) }, //stone quarry
		{ "02000171", Matrix4F(589, 29, 86) }, //kolopua crag
		{ "02000093", Matrix4F(654, 56, 193) }, //karnifs fang
		{ "02000044", Matrix4F(684, 51, 129) }, //fractured canyon 
		{ "02000173", Matrix4F(525, 89, -22) }, //ant tunnel entrance
		{ "02000014", Matrix4F(-41, 19, -136) }, //ludibrium crater
		{ "02000092", Matrix4F(43, 16, -153) }, //revoldic dam 
		{ "02000083", Matrix4F(131, 22, -93) }, //kerning interchange
		{ "02000111", Matrix4F(231, 59, -146) }, //beachway 111
		{ "02000143", Matrix4F(357, 58, -141) }, //blooming farm
		{ "02000105", Matrix4F(476, 62, -115) }, //aner park
		{ "02000134", Matrix4F(3, 3, -185) }, //goldus pharmeceuticals
		{ "02000135", Matrix4F(68, 34, -223) }, //mounthills
		{ "02000084", Matrix4F(136, 36, -180) }, //kerning junkyard
		{ "02000086", Matrix4F(239, 62, -213) }, //lavaworks
		{ "02000057", Matrix4F(330, 76, -208) }, //west wind hill
		{ "02000013", Matrix4F(454, 76, -164) }, //forgotten keep
		{ "02000174", Matrix4F(587, 63, -7) }, //ant tunnel plaza
		{ "02000411", Matrix4F(721, 88, 144) }, //expedition base
		{ "02000136", Matrix4F(28, 38, -249) }, //fellowstone construction
		{ "02000110", Matrix4F(208, 52, -261) }, //barrota shore
		{ "02000091", Matrix4F(321, 76, -250) }, //west watchtower
		{ "02000186", Matrix4F(378, 91, -235) }, //sweetskirts
		{ "02000256", Matrix4F(630, 66, 59) }, //ant tunnel passage
		{ "02000412", Matrix4F(785, 85, 153) }, //aurora labratory
		{ "02000145", Matrix4F(-46, 25, -256) }, //neuron dna research center
		{ "02000146", Matrix4F(-78, 40, -327) }, //shadow gate
		{ "02000266", Matrix4F(-4, 47, -321) }, //muros media park
		{ "02000137", Matrix4F(92, 33, -296) }, //majore lake park
		{ "02000139", Matrix4F(177, 86, -340) }, //barrota port
		{ "02000147", Matrix4F(312, 85, -293) }, //flora avenue
		{ "02000185", Matrix4F(410, 118, -275) }, //sweet tooth valley
		{ "02000015", Matrix4F(500, 78, -225) }, //henesys docks
		{ "02000175", Matrix4F(714, 58, 41) }, //frostember void
		{ "02000413", Matrix4F(825, 89, 114) }, //lulu village
		{ "52000091", Matrix4F(-155, 34, -291) * Matrix4F::YawRotation(PI / 2.f)}, //revealed stronghold
		{ "02000279", Matrix4F(7, 58, -390) }, //chronoff train station
		{ "02000265", Matrix4F(65, 58, -355) }, //kerning techno valley
		{ "02000148", Matrix4F(156, 85, -383) }, //suffering wasteland
		{ "02000100", Matrix4F(322, 84, -340) }, //kerning city
		{ "02000165", Matrix4F(380, 97, -336) }, //resortville
		{ "02000007", Matrix4F(477, 103, -320) }, //breezy hills
		{ "02000021", Matrix4F(538, 85, -278) }, //precipice fortess
		{ "02000040", Matrix4F(747, 81, -42) }, //lavaluna cave
		{ "02000192", Matrix4F(807, 72, 88) }, //cave of eternity
		{ "02000414", Matrix4F(858, 97, 130) }, //forsaken fields
		{ "02000496", Matrix4F(-153, 21, -386) * Matrix4F::YawRotation(PI / 2.f) }, //storms eye
		{ "02000162", Matrix4F(-6, 48, -427) }, //magma research center
		{ "02000167", Matrix4F(253, 85, -336) }, //oasis town
		{ "02000216", Matrix4F(232, 94, -417) }, //black market
		{ "02000164", Matrix4F(273, 99, -403) }, //silverstone bridge
		{ "02000166", Matrix4F(347, 109, -420) }, //new goldus
		{ "02000142", Matrix4F(426, 95, -365) }, //clock tower square
		{ "02000008", Matrix4F(502, 116, -397) }, //ludibrium crevasse
		{ "02000009", Matrix4F(548, 109, -336) }, //sand dunes
		{ "02000038", Matrix4F(587, 94, -272) }, //rainbow mountain
		{ "02000011", Matrix4F(794, 86, -66) }, //lava crest
		{ "02000176", Matrix4F(900, 67, 107) }, //frozencrest
		{ "02000415", Matrix4F(930, 82, 170) }, //lions gate
		{ "52000093", Matrix4F(-226, 37, -356) * Matrix4F::YawRotation(PI / 2.f) }, //shadow canyon
		{ "52000094", Matrix4F(-150, 33, -240) * Matrix4F::YawRotation(PI) }, //empty field
		{ "02000271", Matrix4F(-63, 54, -465) }, //new kerningdom
		{ "02000269", Matrix4F(20, 34, -498) }, //cellimental test bunker
		{ "02000231", Matrix4F(428, 94, -457) }, //ludi fantasia
		{ "02000184", Matrix4F(450, 118, -410) }, //slumberland
		{ "02000255", Matrix4F(514, 123, -501) }, //ludi station
		{ "02000268", Matrix4F(855, 54, -45) }, //magma gorge
		{ "02000261", Matrix4F(910, 84, 60) }, //snowscarf haven
		{ "02000264", Matrix4F(981, 81, 142) }, //igloo hill
		{ "02000260", Matrix4F(953, 69, 69) }, //frostpeak mountain
		{ "02000263", Matrix4F(1019, 104, 85) }, //crystalfrost wall
		{ "02000200", Matrix4F(910, 72, -68) }, //darkmist path
		{ "02000235", Matrix4F(860, 95, -105) }, //wailing mine
		{ "02000018", Matrix4F(370, 98, -539) }, //berrysweet castle
		{ "02000280", Matrix4F(488, 111, -570) }, //harrot hill
		{ "02000257", Matrix4F(560, 102, -481) }, //macaroon acres
		{ "02000272", Matrix4F(-118, 48, -465) }, //old kerningdom
		{ "02000270", Matrix4F(-105, 49, -490) }, //taliskar
		{ "02000163", Matrix4F(-51, 65, -500) }, //msl electronics institute
		{ "02000236", Matrix4F(916, 106, -79) }, //magma trail
		{ "02000262", Matrix4F(498, 121, -625) }, //luditon carnival
		{ "02000258", Matrix4F(575, 113, -583) }, //frostbunny park
		{ "02000273", Matrix4F(-120, 33, -545) }, //steamerbrook
		{ "02000276", Matrix4F(-30, 67, -594) }, //kernel energy research
		{ "02000187", Matrix4F(13, 72, -570) }, //msl robot dev center
		{ "02000277", Matrix4F(54, 75, -524) }, //msl factory
		{ "02000416", Matrix4F(960, 101, -62) }, //blazing ravine
		{ "02000259", Matrix4F(579, 137, -600) }, //ludi arcade
		{ "02000274", Matrix4F(-136, 50, -600) }, //water supply center
		{ "02000417", Matrix4F(997, 104, -24) }, //smoldering fortress
		{ "02000275", Matrix4F(-219, 25, -618) }, //phantoma cyborg center
		{ "02000418", Matrix4F(1065, 107, -46) }, //gate of trials
	};

	Matrix4F ms2toworld = ms2ToWorld;

	for (size_t i = 0; i < maps.size() && mapId == nullptr; ++i)
	{
		ms2ToWorld = maps[i].offset * ms2toworld;

		std::cout << "loading map " << maps[i].id << std::endl;

		loadMap(maps[i].id);

		loadLights = false;
	}

	ms2ToWorld = ms2toworld;
	loadLights = true;

	if (mapId != nullptr)
		loadMap(mapId);

	Character baadf00d;

	baadf00d.Gender = Gender::Female;
	baadf00d.Face = Item{ 10300097, getDyeColor("Light Green", true) };
	baadf00d.FaceDecor = FaceDecorItem{ 10400010 };
	baadf00d.SkinColor = getDyeColor(3);
	baadf00d.Hair = HairItem{ 10200250, getDyeColor("Pink") };
	baadf00d.Cosmetics.Hat = HatItem{ 11300743, getDyeColor("Red") };
	baadf00d.Cosmetics.Shirt = Item{ 11401065, getDyeColor("Light Pink") };
	baadf00d.Cosmetics.Pants = Item{ 11500163, getDyeColor("Pink") };
	baadf00d.Cosmetics.Gloves = Item{ 11620024, getDyeColor("Red") };
	baadf00d.Cosmetics.Shoes = Item{ 11700313, getDyeColor("Light Pink") };

	LoadCharacter(baadf00d, Matrix4F(0, 0, 3000) * Matrix4F::RollRotation(PI));

	Character hornetsp;

	hornetsp.Gender = Gender::Male;
	hornetsp.Face = Item{ 10300014, getDyeColor("Blue") };
	hornetsp.FaceDecor = FaceDecorItem{ 10400006, getDyeColor("Blue"), 0 };
	hornetsp.SkinColor = getDyeColor(12);
	hornetsp.Hair = HairItem{ 10200001, getDyeColor("Green") };
	hornetsp.Cosmetics.Hat = HatItem{ 11380431, getDyeColor("Green") };
	hornetsp.Cosmetics.Shirt = Item{ 11480386, getDyeColor("Green") };
	hornetsp.Cosmetics.Pants = Item{ 11500660, getDyeColor("Green") };
	hornetsp.Cosmetics.Gloves = Item{ 11600864, getDyeColor("Green") };
	hornetsp.Cosmetics.Shoes = Item{ 11790671, getDyeColor("Green") };
	hornetsp.Cosmetics.Cape = Item{ 11890080, getDyeColor("Green") };
	hornetsp.Gear.Earring = Item{ 11200064, getDyeColor("Green") };
	hornetsp.Gear.Pendant = Item{ 11900122, getDyeColor("Green") };
	hornetsp.Gear.Belt = Item{ 12100112, getDyeColor("Green") };
	hornetsp.Gear.Ring = Item{ 12060106, getDyeColor("Green") };
	hornetsp.Gear.Weapon = Item{ 15460178, getDyeColor("Green") };

	LoadCharacter(hornetsp, Matrix4F(120, 0, 3000) * Matrix4F::RollRotation(PI));


	//loadMap("02000376"); //sb map
	//loadMap("02010011"); // ludari promenade
	//loadMap("02000415"); // lions gate
	//loadMap("99999887"); // test
	//loadMap("02000422"); // sky fort
	//loadMap("02000496"); // storms eye
	//loadMap("02020130"); // 
	//loadMap("02000083"); 

	// Creation of the example
	//helloVk.loadModel(nvh::findFile("media/scenes/Medieval_building.obj", defaultSearchPaths, true));
	//helloVk.loadModel(nvh::findFile("media/scenes/plane.obj", defaultSearchPaths, true));

	helloVk.createOffscreenRender();
	helloVk.createDescriptorSetLayout();
	helloVk.createGraphicsPipeline();
	helloVk.createUniformBuffer();
	helloVk.createObjDescriptionBuffer();
	helloVk.updateDescriptorSet();

	// #VKRay
	helloVk.initRayTracing();
	helloVk.createBottomLevelAS();
	helloVk.createTopLevelAS();
	helloVk.createRtDescriptorSet();
	helloVk.createRtPipeline();
	helloVk.createRtShaderBindingTable();

	helloVk.createPostDescriptor();
	helloVk.createPostPipeline();
	helloVk.updatePostDescriptorSet();


	vec4 clearColor   = vec4(1, 1, 1, 1.00f);
	bool          useRaytracer = true;


	helloVk.setupGlfwCallbacks(window);
	ImGui_ImplGlfw_InitForVulkan(window, true);

	// Main loop
	while(!glfwWindowShouldClose(window))
	{
	glfwPollEvents();
	if(helloVk.isMinimized())
		continue;

	// Start the Dear ImGui frame
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	// Show UI window.
	if(helloVk.showGui())
	{
		ImGuiH::Panel::Begin();
		ImGui::ColorEdit3("Clear color", reinterpret_cast<float*>(&clearColor));
		ImGui::Checkbox("Ray Tracer mode", &useRaytracer);  // Switch between raster and ray tracing

		if (ImGui::BeginTabBar("Render"))
		{
			if (ImGui::BeginTabItem("Debug Info"))
			{
				int modelId = helloVk.mouseIO.objectIndex;

				ImGui::Text("Mouse Hit: %d", modelId);
				ImGui::Text("Mouse Hit Pos: %.3f, %.3f, %.3f", helloVk.mouseIO.hitPosition[0], helloVk.mouseIO.hitPosition[1], helloVk.mouseIO.hitPosition[2]);
				ImGui::Text("Mouse Intersection: %d", helloVk.hostUBO.hitIndex);

				if (ImGui::IsKeyPressed(ImGuiKey_PageDown))
					helloVk.hostUBO.hitIndex = std::max(0, helloVk.hostUBO.hitIndex - 1);
				if (ImGui::IsKeyPressed(ImGuiKey_PageUp))
					helloVk.hostUBO.hitIndex = std::min(10, helloVk.hostUBO.hitIndex + 1);

				helloVk.hostUBO.mouseX = (int)helloVk.mousePosXF;
				helloVk.hostUBO.mouseY = (int)helloVk.mousePosYF;
				ImGui::Text("Mouse: %d, %d", helloVk.hostUBO.mouseX, helloVk.hostUBO.mouseY);

				if (modelId >= 0 && modelId < (int)spawnedModels.size())
				{
					int entityId = spawnedModels[modelId].EntityId;

					const SpawnedEntity& entity = spawnedEntities[entityId];


					struct ModifierKeysEnum
					{
						enum Modifiers : byte
						{
							None = 0,
							Ctrl = 1,
							Shift = 2,
							Alt = 4,
							Tab = 8
						};
					};

					typedef ModifierKeysEnum::Modifiers ModifierKeys;

					int modifiers = 0;

					if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl))
						modifiers = modifiers | ModifierKeys::Ctrl;

					if (ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift))
						modifiers |= ModifierKeys::Shift;

					if (ImGui::IsKeyDown(ImGuiKey_LeftAlt) || ImGui::IsKeyDown(ImGuiKey_RightAlt))
						modifiers |= ModifierKeys::Alt;

					if (ImGui::IsKeyDown(ImGuiKey_Tab))
						modifiers |= ModifierKeys::Tab;

					if (entity.MapIndex != -1)
					{
						ImGui::Text("Map: [%s] %s", loadedMaps[entity.MapIndex].Id.c_str(), loadedMaps[entity.MapIndex].Name.c_str());
					}

					int spawnedModelId = spawnedModels[modelId].ModelId;

					ImGui::Text("Entity Name: %s", entity.Name.c_str());

					if (entity.Flat != nullptr)
					{
						ImGui::Text("Entity Flat Name: %s", entity.Flat->Entry->Name.c_str());
						ImGui::Text("Entity Flat Path: %s", entity.Flat->Entry->RelativePath.string().c_str());
					}

					ImGui::Text("Entity Model Name: %s", entity.Model->Entry->Name.c_str());
					ImGui::Text("Entity Model Path: %s", entity.Model->Entry->RelativePath.string().c_str());
					ImGui::Text("Entity Id: %s", entity.Id.c_str());
					ImGui::Text("Spawned Entity Position: %.3f, %.3f, %.3f", entity.WorldPosition.X, entity.WorldPosition.Y, entity.WorldPosition.Z);
					ImGui::Text("Entity Coordinates: %.3f, %.3f, %.3f", entity.Position.X, entity.Position.Y, entity.Position.Z);
					ImGui::Text("NiMesh Index: %d", spawnedModelId);

					ImGui::Text("Shader: %s", entity.Model->Shaders[spawnedModelId].c_str());
					ImGui::Text("Material: %s", entity.Model->MaterialNames[spawnedModelId].c_str());

					ImGui::ColorEdit3("Diffuse", &entity.Model->Materials[spawnedModelId].diffuse[0], ImGuiColorEditFlags_NoPicker);
					ImGui::ColorEdit3("Specular", &entity.Model->Materials[spawnedModelId].specular[0], ImGuiColorEditFlags_NoPicker);
					ImGui::ColorEdit3("Ambient", &entity.Model->Materials[spawnedModelId].ambient[0], ImGuiColorEditFlags_NoPicker);
					ImGui::ColorEdit3("Emission", &entity.Model->Materials[spawnedModelId].emission[0], ImGuiColorEditFlags_NoPicker);
					ImGui::Text("Alpha: %.2f", entity.Model->Materials[spawnedModelId].dissolve);
					ImGui::Text("Shininess: %.2f", entity.Model->Materials[spawnedModelId].shininess);

					if (ImGui::IsKeyPressed(ImGuiKey_Insert) && fs::exists(ms2RootExtracted))
					{
						std::cout << modifiers << std::endl;
						fs::path path = ms2RootExtracted / "Resource/";
						std::string editor = "cmd.exe /q /c start /b code --goto ";
						int line = -1;
						DWORD flags = 0;

						if (modifiers == (ModifierKeys::Shift | ModifierKeys::Ctrl) && entity.Flat != nullptr)
						{
							flags = CREATE_NO_WINDOW;

							path = path / entity.Flat->Entry->RelativePath;
						}
						else if (modifiers == ModifierKeys::Alt)
						{
							editor = "\"B:/Files/NifSkope_2_0_2020-07-09-x64/NifSkope.exe\"";
							path = path / entity.Model->Entry->RelativePath;
						}
						else if (modifiers == ModifierKeys::Ctrl)
						{
							flags = CREATE_NO_WINDOW;

							path = loadedMaps[entity.MapIndex].XBlockPath;

							line = entity.LineNumber;
						}
						else
						{
							path = "err";
						}

						if (fs::exists(path))
						{
							std::stringstream openNotepad;

							openNotepad << "\"" << path.string();

							if (line != -1)
							{
								openNotepad << ":" << line;
							}

							openNotepad << "\"";


							//std::system((openNotepad.str()).c_str());
							//WinExec(openNotepad.str().c_str(), SW_HIDE);
							if (true)
							{
								STARTUPINFOA startInfo;
								startInfo.cb = sizeof(startInfo);
								PROCESS_INFORMATION processInfo;

								ZeroMemory(&startInfo, sizeof(startInfo));
								ZeroMemory(&processInfo, sizeof(processInfo));

								//if (flags == CREATE_NO_WINDOW)
								//{
								startInfo.wShowWindow = SW_HIDE;
								startInfo.dwFlags = STARTF_USESHOWWINDOW;
								//}

								std::string args = editor + openNotepad.str();

								if (CreateProcessA(NULL, const_cast<LPSTR>(args.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startInfo, &processInfo))
								{
									CloseHandle(processInfo.hThread);
									CloseHandle(processInfo.hProcess);
								}
							}
						}
					}

					if (entity.PortalIndex != -1)
					{
						const SpawnedPortal& portal = spawnedPortals[entity.PortalIndex];

						ImGui::Text("Portal Id: %d", portal.PortalId);

						if (portal.TargetField != "")
							ImGui::Text("Target Map: [%s] %s", portal.TargetField.c_str(), mapNames[portal.TargetField].c_str());

						if (portal.TargetPortal != -1)
						{
							ImGui::Text("Target Portal Id: %d", portal.TargetPortal);

							int mapIndex = portal.TargetField != "" && mapIndices.contains(portal.TargetField) ? mapIndices[portal.TargetField] : (portal.TargetField != "" ? -1 : entity.MapIndex);

							if (mapIndex != -1)
							{
								LoadedMap& map = loadedMaps[mapIndex];

								const auto& targetPortalIndex = map.Portals.find(portal.TargetPortal);

								if (targetPortalIndex != map.Portals.end())
								{
									const SpawnedEntity& targetPortal = spawnedEntities[targetPortalIndex->second];

									ImGui::Text("Target Portal Entity Name: %s", targetPortal.Name.c_str());

									if (targetPortal.Flat != nullptr)
									{
										ImGui::Text("Target Portal Entity Flat Name: %s", targetPortal.Flat->Entry->Name.c_str());
										ImGui::Text("Target Portal Entity Flat Path: %s", targetPortal.Flat->Entry->RelativePath.string().c_str());
									}

									ImGui::Text("Target Portal Entity Model Name: %s", targetPortal.Model->Entry->Name.c_str());
									ImGui::Text("Target Portal Entity Model Path: %s", targetPortal.Model->Entry->RelativePath.string().c_str());
									ImGui::Text("Target Portal Entity Id: %s", targetPortal.Id.c_str());
									ImGui::Text("Target Portal Spawned Entity Position: %.3f, %.3f, %.3f", targetPortal.WorldPosition.X, targetPortal.WorldPosition.Y, targetPortal.WorldPosition.Z);
									ImGui::Text("Target Portal Entity Coordinates: %.3f, %.3f, %.3f", targetPortal.Position.X, targetPortal.Position.Y, targetPortal.Position.Z);

									if (ImGui::IsKeyPressed(ImGuiKey_Enter) && modifiers == ModifierKeys::Shift)
									{
										std::stringstream str;
										str << targetPortal.WorldPosition;
										std::string positionString = str.str();

										glfwSetClipboardString(helloVk.getWindow(), positionString.c_str());
									}

									if (ImGui::IsKeyPressed(ImGuiKey_Enter) && modifiers == ModifierKeys::Ctrl)
									{
										std::stringstream str;

										Vector3SF position = entity.WorldPosition;

										if (entity.MapIndex != -1)
										{
											position = loadedMaps[entity.MapIndex].MapTransform * Vector3F(entity.Position, 1) - loadedMaps[entity.MapIndex].MapTransform.Translation();
										}

										str << targetPortal.WorldPosition - position;
										std::string positionString = str.str();

										glfwSetClipboardString(helloVk.getWindow(), positionString.c_str());
									}

									if (ImGui::IsKeyPressed(ImGuiKey_Home))
									{
										nvh::CameraManipulator::Camera camera = CameraManip.getCamera();

										vec3 ctr = camera.ctr;
										vec3 ey = camera.eye;

										Vector3SF center(ctr[0], ctr[1], ctr[2]);
										Vector3SF eye(ey[0], ey[1], ey[2]);

										Vector3SF offset = targetPortal.WorldPosition - entity.WorldPosition;

										center += offset;
										eye += offset;

										camera.ctr = vec3(center.X, center.Y, center.Z);
										camera.eye = vec3(eye.X, eye.Y, eye.Z);

										CameraManip.setCamera(camera);
									}
								}
							}
						}
					}

					if (ImGui::IsKeyPressed(ImGuiKey_Enter) && modifiers == ModifierKeys::None)
					{
						std::stringstream str;
						str << entity.WorldPosition;
						std::string positionString = str.str();

						glfwSetClipboardString(helloVk.getWindow(), positionString.c_str());
					}
				}

				if (ImGui::CollapsingHeader("Unmapped Materials Found:"))
				{
					for (const std::string& name : unmappedMaterials)
					{
						ImGui::Text(("\t" + name).c_str());
					}
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Settings"))
			{
				ImGui::Text("Lighting Model:");
				ImGui::RadioButton("Phong", &helloVk.hostUBO.lightingModel, 0);
				ImGui::RadioButton("MS2 Phong", &helloVk.hostUBO.lightingModel, 1);

				ImGui::Text("Sky Light:");
				ImGui::RadioButton("Map Lights", &helloVk.hostUBO.skyLightMode, 0);
				ImGui::RadioButton("Dynamic Sky", &helloVk.hostUBO.skyLightMode, 1);

				if (helloVk.hostUBO.skyLightMode == 1)
				{

				}

				bool drawInvisible = (helloVk.hostUBO.drawMode & 1) != 0;
				bool drawDebug = (helloVk.hostUBO.drawMode & 2) != 0;

				ImGui::Checkbox("Draw Invisible Objects", &drawInvisible);
				ImGui::Checkbox("Draw Debug Objects", &drawDebug);

				helloVk.hostUBO.drawMode &= -1 ^ 3;
				helloVk.hostUBO.drawMode |= (drawDebug ? 2 : 0) | (drawInvisible ? 1 : 0);

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGuiH::Control::Info("", "", "(F10) Toggle Pane", ImGuiH::Control::Flags::Disabled);
		ImGuiH::Panel::End();
	}

	// Start rendering the scene
	helloVk.prepareFrame();

	// Start command buffer of this frame
	auto                   curFrame = helloVk.getCurFrame();
	const VkCommandBuffer& cmdBuf   = helloVk.getCommandBuffers()[curFrame];

	VkCommandBufferBeginInfo beginInfo{VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(cmdBuf, &beginInfo);

	// Updating camera buffer
	helloVk.updateUniformBuffer(cmdBuf);

	// Clearing screen
	std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color        = {{clearColor[0], clearColor[1], clearColor[2], clearColor[3]}};
	clearValues[1].depthStencil = {1.0f, 0};

	// Offscreen render pass
	{
		VkRenderPassBeginInfo offscreenRenderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
		offscreenRenderPassBeginInfo.clearValueCount = 2;
		offscreenRenderPassBeginInfo.pClearValues    = clearValues.data();
		offscreenRenderPassBeginInfo.renderPass      = helloVk.m_offscreenRenderPass;
		offscreenRenderPassBeginInfo.framebuffer     = helloVk.m_offscreenFramebuffer;
		offscreenRenderPassBeginInfo.renderArea      = {{0, 0}, helloVk.getSize()};

		// Rendering Scene
		if(useRaytracer)
		{
		helloVk.raytrace(cmdBuf, clearColor);
		}
		else
		{
		vkCmdBeginRenderPass(cmdBuf, &offscreenRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
		helloVk.rasterize(cmdBuf);
		vkCmdEndRenderPass(cmdBuf);
		}
	}

	// 2nd rendering pass: tone mapper, UI
	{
		VkRenderPassBeginInfo postRenderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
		postRenderPassBeginInfo.clearValueCount = 2;
		postRenderPassBeginInfo.pClearValues    = clearValues.data();
		postRenderPassBeginInfo.renderPass      = helloVk.getRenderPass();
		postRenderPassBeginInfo.framebuffer     = helloVk.getFramebuffers()[curFrame];
		postRenderPassBeginInfo.renderArea      = {{0, 0}, helloVk.getSize()};

		// Rendering tonemapper
		vkCmdBeginRenderPass(cmdBuf, &postRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
		helloVk.drawPost(cmdBuf);
		// Rendering UI
		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmdBuf);
		vkCmdEndRenderPass(cmdBuf);
	}

	// Submit for display
	vkEndCommandBuffer(cmdBuf);
	helloVk.submitFrame();
	}

	// Cleanup
	vkDeviceWaitIdle(helloVk.getDevice());

	helloVk.destroyResources();
	helloVk.destroy();
	vkctx.deinit();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
