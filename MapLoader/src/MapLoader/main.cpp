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
#include "nvvk/images_vk.hpp"
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
#include "Assets/ModelLibrary.h"
#include "Assets/TextureLibrary.h"
#include "Assets/GameAssetLibrary.h"
#include "Assets/TextureAsset.h"
#include "Map/FlatLibrary.h"
#include "Vulkan/VulkanContext.h"
#include "Items/Dyes.h"
#include "Items/EmotionLibrary.h"
#include "Character/Character.h"
#include "Scene/RTScene.h"
#include "Assets/SkinnedModel.h"

using DyeColor = MapLoader::DyeColor;
using EmotionTexture = MapLoader::EmotionTexture;
using Emotion = MapLoader::Emotion;
using Gender = MapLoader::Gender;
using Character = MapLoader::Character;

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

struct EntityData;

struct SpawnedEntity
{
	MapLoader::ModelData* Model = nullptr;
	const Archive::Metadata::Entry* FlatEntry = nullptr;
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

HelloVulkan* helloVkPtr = nullptr;
std::shared_ptr<Archive::ArchiveReader> Reader = std::make_shared<Archive::ArchiveReader>();
std::shared_ptr<Graphics::VulkanContext> VulkanContext;
std::shared_ptr<MapLoader::GameAssetLibrary> AssetLibrary;
MapLoader::DyeColors dyeColors;
std::string documentBuffer;
std::string flatDocumentBuffer;
std::string nifDocumentBuffer;

const char* localeName = "NA";
const char* environmentName = "Live";
fs::path ms2Root = "B:/Files/Maplstory 2 Client/appdata";
fs::path ms2RootExtracted = "B:/Files/ms2export/export/";
fs::path tableroot = fs::path("Xml/table/");
bool loadLights = true;
std::vector<SpawnedModel> spawnedModels;
std::vector<SpawnedEntity> spawnedEntities;
std::vector<LoadedMap> loadedMaps;
std::vector<SpawnedPortal> spawnedPortals;
std::unordered_map<std::string, std::string> mapNames;
std::unordered_map<std::string, int> mapIndices;
std::unordered_map<int, std::string> mapFileNames;
std::shared_ptr<MapLoader::RTScene> Scene;
std::shared_ptr<Engine::Transform> mapTransform;

const float PI = 3.14159265359f;

Matrix4F ms2ToWorld = Matrix4F::NewScale(0.02f / 3.f, 0.02f / 3.f, 0.02f / 3.f) * Matrix4F::PitchRotation(-PI / 2);

struct Bounds
{
	Vector3SF Min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() , std::numeric_limits<float>::max() };
	Vector3SF Max = { -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max() , -std::numeric_limits<float>::max() };
};

void getBounds(const MapLoader::ModelData* model, Bounds& bounds)
{
	for (const MapLoader::ModelNode& node : model->Nodes)
	{
		if (node.Mesh == nullptr) continue;

		node.Mesh->ForEach<Vector3SF>(node.Mesh->GetFormat()->GetAttributeIndex("position"), [&bounds](const Vector3SF& vertex)
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

int duplicateFormatUses = 0;

SpawnedEntity* spawnModel(MapLoader::ModelData* model, const Matrix4F& transformation, const ModelSpawnCallback& callback)
{
	if (model == nullptr)
		return nullptr;

	int entityId = (int)spawnedEntities.size();
	spawnedEntities.push_back(SpawnedEntity{ model });
	duplicateFormatUses += model->DuplicateFormatUses;

	for (size_t i = 0; i < model->Nodes.size(); ++i)
	{
		if (model->IsLoaded(i))
		{
			InstDesc instance;

			if (callback != nullptr)
			{
				if (!callback(model, i, instance))
					continue;
			}

			Matrix4F modelTransform = model->Nodes[i].Transformation;

			helloVkPtr->loadModelInstance(model->GetId(i), ms2ToWorld * transformation * modelTransform);

			spawnedModels.push_back(SpawnedModel{ entityId, (int)i });

			std::shared_ptr<Engine::Transform> transform = Engine::Create<Engine::Transform>();
			std::shared_ptr<MapLoader::SceneObject> sceneObject = Engine::Create<MapLoader::SceneObject>();

			transform->SetTransformation(ms2ToWorld * transformation * modelTransform);
			transform->SetParent(mapTransform);
			sceneObject->SetTransform(transform.get());
			sceneObject->SetModel(model, i);
			sceneObject->SetStatic(true);
			sceneObject->SetParent(transform);
			Scene->AddObject(sceneObject);

			helloVkPtr->instanceDescriptions.push_back(instance);
		}
	}

	return &spawnedEntities.back();
}

void spawnWireframe(uint32_t index, const Matrix4F& transform)
{
	helloVkPtr->loadWireframeInstance(index, ms2ToWorld * transform);
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

void loadMap(const std::string& mapId)
{
	std::string xblockName;
	const auto& xblockNameIndex = mapFileNames.find(atoi(mapId.c_str()));
	
	if (xblockNameIndex != mapFileNames.end())
	{
		xblockName = xblockNameIndex->second;

		std::cout << "found map " << mapId << ": " << xblockName << std::endl;
	}
	else
	{
		Archive::ArchivePath mapFile = Reader->GetPath("Xml/map/" + padId(mapId) + ".xml");

		if (!mapFile.Loaded())
		{
			std::cout << "failed to load map: " << mapFile.GetPath().string() << std::endl;
			return;
		}

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
	}

	const Archive::Metadata::Entry* entry = Archive::Metadata::Entry::FindFirstEntryByTags(xblockName, "emergent-world");

	if (entry == nullptr)
	{
		std::cout << "no map entry found" << std::endl;

		return;
	}

	Archive::ArchivePath xblockFile = Reader->GetPath("Resource/" + entry->RelativePath.string());

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

	MapLoader::FlatLight ambient;
	bool hasAmbient = false;

	for (tinyxml2::XMLElement* entityElement = entitySet->FirstChildElement(); entityElement; entityElement = entityElement->NextSiblingElement())
	{
		std::string entityName = readAttribute<const char*>(entityElement, "name", "");
		std::string modelName = readAttribute<std::string>(entityElement, "modelName", "");

		MapLoader::FlatEntry flatentry = AssetLibrary->GetFlats().FetchFlat(modelName);

		if (flatentry.Entity == nullptr)
			continue;

		MapLoader::FlatEntry entityEntry = AssetLibrary->GetMapData().LoadEntityFromFlat(flatentry, entityElement);

		if (entityEntry.Light != nullptr && loadLights)
		{
			if (entityEntry.Light->Type == MapLoader::EntityLightType::Ambient)
			{
				hasAmbient = true;
				ambient = *entityEntry.Light;
			}
			else
			{
				Vector3F direction = -(/*ms2ToWorld */ entityEntry.Placeable->Transformation.FrontVector()).Unit();
				Vector3F position = /*ms2ToWorld */ Vector3F(entityEntry.Placeable->Position, 1);

				helloVkPtr->lights.push_back(LightDesc{});

				LightDesc& light = helloVkPtr->lights.back();

				if (entityEntry.Light->Type == MapLoader::EntityLightType::Directional && directionalLight == -1)
					directionalLight = helloVkPtr->lights.size() - 1;

				light.position = vec3(position.X, position.Y, position.Z);
				light.direction = vec3(direction.X, direction.Y, direction.Z);
				light.brightness = entityEntry.Light->Dimmer;
				light.type = (int)entityEntry.Light->Type;
				light.range = entityEntry.Light->Range;
				light.diffuse = (Vector3)entityEntry.Light->DiffuseColor;
				light.specular = (Vector3)entityEntry.Light->SpecularColor;
				light.ambient = (Vector3)entityEntry.Light->AmbientColor;
				light.castsShadows = entityEntry.Light->CastsShadows;
			}
		}
		
		if (entityEntry.Mesh == nullptr || entityEntry.Mesh->Model == nullptr)
			continue;

		SpawnedEntity* newModel = spawnModel(entityEntry.Mesh->Model, entityEntry.Placeable->Transformation, [&entityEntry](MapLoader::ModelData* model, size_t i, InstDesc& instance)
			{
				instance.color = (Vector3)entityEntry.Mesh->MaterialColor;
				instance.flags = entityEntry.Placeable->IsVisible ? 0 : 1;

				return true;
			}
		);// *flat->Transformation);
		newModel->Id = entityEntry.Entity->Id;
		newModel->Name = entityName;
		newModel->FlatEntry = flatentry.Entity->Entry;
		newModel->Position = entityEntry.Placeable->Position;
		newModel->WorldPosition = ms2ToWorld * Vector3F(entityEntry.Placeable->Position, 1);
		newModel->MapIndex = (int)loadedMaps.size() - 1;
		newModel->LineNumber = entityElement->GetLineNum();

		if (entityEntry.Portal != nullptr)
		{
			newModel->PortalIndex = (int)spawnedPortals.size();
			loadedMaps.back().Portals[entityEntry.Portal->PortalId] = (int)spawnedEntities.size() - 1;

			spawnedPortals.push_back(SpawnedPortal{ entityEntry.Portal->TargetField, entityEntry.Portal->TargetPortal, entityEntry.Portal->PortalId });
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

void loadMapFileNames(const Archive::ArchivePath& file)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load fielddata.xml " << file.GetPath().string() << std::endl;
		return;
	}

	tinyxml2::XMLDocument document;

	file.Read(documentBuffer);
	document.Parse(documentBuffer.data(), documentBuffer.size());

	tinyxml2::XMLElement* rootElement = document.RootElement();

	for (tinyxml2::XMLElement* fieldDataElement = rootElement->FirstChildElement(); fieldDataElement; fieldDataElement = fieldDataElement->NextSiblingElement())
	{
		int id = readAttribute<int>(fieldDataElement, "id", 0);

		tinyxml2::XMLElement* envElement = fieldDataElement->FirstChildElement();

		if (envElement == nullptr || strcmp(envElement->Name(), "environment") != 0) continue;

		for (tinyxml2::XMLElement* componentElement = envElement->FirstChildElement(); componentElement; componentElement = componentElement->NextSiblingElement())
		{
			const char* name = componentElement->Name();

			if (strcmp(name, "xblock") == 0)
			{
				mapFileNames[id] = readAttribute<std::string>(componentElement, "name", "");

				continue;
			}
		}
	}
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

	Reader->Load(ms2Root / "Data", true);

	std::cout << "archives loaded, indexing asset-web-metadata" << std::endl;

	fs::path webMetaCache = "./cache/asset-web-metadata-cache-";

	unsigned int hash = Archive::FNV1A32::Hash(ms2Root.string());
	char hashBuffer[9] = { 0 };

	for (size_t i = 0; i < 8; ++i)
	{
		char data = hash & 0xF;
		hash >>= 4;
		
		hashBuffer[7 - i] = (data < 0xA) ? '0' + data : 'A' + data - 0xA;
	}

	webMetaCache += hashBuffer;

	if (!Archive::Metadata::Entry::LoadCached(webMetaCache))
	{
		std::cout << "no asset-web-metadata cache found, loading" << std::endl;
		Archive::Metadata::Entry::LoadEntries(*Reader, "Resource/asset-web-metadata", documentBuffer);
		std::cout << "caching asset-web-metadata" << std::endl;
		Archive::Metadata::Entry::Cache(webMetaCache);
	}
	else
		std::cout << "asset-web-metadata cache found and loaded" << std::endl;

	if (!loadFeatures(Reader->GetPath("Xml/table"), localeName, environmentName, documentBuffer)) return -1;

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

	VulkanContext = std::make_shared<Graphics::VulkanContext>();
	AssetLibrary = std::make_shared<MapLoader::GameAssetLibrary>(Reader, VulkanContext);
	Scene = std::make_shared<MapLoader::RTScene>(VulkanContext);
	mapTransform = Engine::Create<Engine::Transform>();

	// Create example
	HelloVulkan helloVk;

	helloVkPtr = &helloVk;
	helloVk.AssetLibrary = AssetLibrary;
	helloVk.VulkanContext = VulkanContext;
	helloVk.Scene = Scene;

	// Window need to be opened to get the surface on which to draw
	const VkSurfaceKHR surface = helloVk.getVkSurface(vkctx.m_instance, window);
	vkctx.setGCTQueueWithPresent(surface);

	helloVk.setup(vkctx.m_instance, vkctx.m_device, vkctx.m_physicalDevice, vkctx.m_queueGCT.familyIndex);
	helloVk.createSwapchain(surface, SAMPLE_WIDTH, SAMPLE_HEIGHT);
	helloVk.createDepthBuffer();
	helloVk.createRenderPass();
	helloVk.createFrameBuffers();

	dyeColors.LoadDyes(Reader);
	AssetLibrary->GetEmotions().LoadEmotions(Reader);

	loadMapNames(Reader->GetPath("Xml/string/en/mapname.xml"));
	loadMapFileNames(Reader->GetPath("Xml/table/fielddata.xml"));

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

	MapLoader::CharacterData baadf00d;

	baadf00d.Gender = Gender::Female;
	baadf00d.Face = { 10300097, dyeColors.GetDyeColor("Light Green", true) };
	baadf00d.FaceDecor = { 10400010 };
	baadf00d.SkinColor = dyeColors.GetDyeColor(3);
	baadf00d.Hair = { 10200250, dyeColors.GetDyeColor("Pink") };
	baadf00d.Cosmetics.Hat = { 11300743, dyeColors.GetDyeColor("Red"), 0, Vector3SF(30, 0, 0), Vector3SF(10, 25, 20), Vector3SF(-5, 0, 0) };
	baadf00d.Cosmetics.Shirt = { 11401065, dyeColors.GetDyeColor("Light Pink") };
	baadf00d.Cosmetics.Pants = { 11500163, dyeColors.GetDyeColor("Pink") };
	baadf00d.Cosmetics.Gloves = { 11620024, dyeColors.GetDyeColor("Red") };
	baadf00d.Cosmetics.Shoes = { 11700313, dyeColors.GetDyeColor("Light Pink") };

	Character f00dCharacter(AssetLibrary);

	f00dCharacter.Load(&baadf00d, Matrix4F(0, 0, 3000) * Matrix4F::RollRotation(PI));

	MapLoader::CharacterData hornetsp;

	hornetsp.Gender = Gender::Male;
	hornetsp.Face = { 10300014, dyeColors.GetDyeColor("Blue") };
	hornetsp.FaceDecor = { 10400006, dyeColors.GetDyeColor("Blue"), 0 };
	hornetsp.SkinColor = dyeColors.GetDyeColor(12);
	hornetsp.Hair = { 10200001, dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Hat = { 11380431, dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Shirt = { 11480386, dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Pants = { 11500660, dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Gloves = { 11600864, dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Shoes = { 11790671, dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Cape = { 11890080, dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Earring = { 11200064, dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Pendant = { 11900122, dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Belt = { 12100112, dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Ring = { 12060106, dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Weapon = { 15460178, dyeColors.GetDyeColor("Green") };

	Character hornetCharacter(AssetLibrary);

	hornetCharacter.Load(&hornetsp, Matrix4F(120, 0, 3000) * Matrix4F::RollRotation(PI));


	const Archive::Metadata::Entry* derpPandaEntry = Archive::Metadata::Entry::FindFirstEntryByTags("60000053_LesserPanda", "gamebryo-scenegraph");
	MapLoader::ModelData* derpPandaModel = nullptr;
	std::unique_ptr<MapLoader::SkinnedModel> derpPandaRig = std::make_unique<MapLoader::SkinnedModel>(VulkanContext);
	derpPandaRig->SetTransformation(Matrix4F(60, 20, 3000) * Matrix4F::RollRotation(PI));

	if (derpPandaEntry != nullptr)
	{
		derpPandaModel = AssetLibrary->GetModels().FetchModel(derpPandaEntry);
		derpPandaRig->AddModel(derpPandaModel, {}, [](MapLoader::ModelData* model, size_t i, InstDesc& instance)
			{
				return true;
			}
		);
		derpPandaRig->CreateRigDebugMesh(AssetLibrary->GetModels());
	}


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

	helloVk.createDescriptorSetLayout();
	helloVk.createOffscreenRender();
	helloVk.createGraphicsPipeline();
	helloVk.createUniformBuffer();
	helloVk.createObjDescriptionBuffer();
	helloVk.updateDescriptorSet();
	// Setup Imgui
	helloVk.initGUI(helloVk.DeviceRenderPass->GetRenderPass(), 0);  // Using sub-pass 0

	// #VKRay
	helloVk.initRayTracing();
	Scene->Initialize();
	helloVk.createBottomLevelAS();
	Scene->Update(0);
	helloVk.createRtDescriptorSet();
	helloVk.createRtPipeline();

	helloVk.createPostPipeline();
	helloVk.updatePostDescriptorSet();


	vec4 clearColor   = vec4(1, 1, 1, 1.00f);
	bool          useRaytracer = true;


	helloVk.setupGlfwCallbacks(window);
	ImGui_ImplGlfw_InitForVulkan(window, true);

	bool takingLargeScreenshot = false;
	bool debugDisplaySkeletons = false;

	// Main loop
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if(helloVk.isMinimized())
			continue;

		double frameStart = glfwGetTime();

		// Start the Dear ImGui frame
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bool takeScreenshot = false;

		// Show UI window.
		if(helloVk.showGui())
		{
			ImGuiH::Panel::Begin();
			ImGui::ColorEdit3("Clear color", reinterpret_cast<float*>(&clearColor));
			//ImGui::Checkbox("Ray Tracer mode", &useRaytracer);  // Switch between raster and ray tracing

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

						if (entity.FlatEntry != nullptr)
						{
							ImGui::Text("Entity Flat Name: %s", entity.FlatEntry->Name.c_str());
							ImGui::Text("Entity Flat Path: %s", entity.FlatEntry->RelativePath.string().c_str());
						}

						ImGui::Text("Entity Model Name: %s", entity.Model->Entry->Name.c_str());
						ImGui::Text("Entity Model Path: %s", entity.Model->Entry->RelativePath.string().c_str());
						ImGui::Text("Entity Id: %s", entity.Id.c_str());
						ImGui::Text("Spawned Entity Position: %.3f, %.3f, %.3f", entity.WorldPosition.X, entity.WorldPosition.Y, entity.WorldPosition.Z);
						ImGui::Text("Entity Coordinates: %.3f, %.3f, %.3f", entity.Position.X, entity.Position.Y, entity.Position.Z);
						ImGui::Text("NiMesh Index: %d", spawnedModelId);

						MapLoader::ModelNode& node = entity.Model->Nodes[spawnedModelId];

						ImGui::Text("Shader: %s", node.Shader.c_str());
						ImGui::Text("Material: %s", node.MaterialName.c_str());

						ImGui::ColorEdit3("Diffuse", &node.Material.diffuse[0], ImGuiColorEditFlags_NoPicker);
						ImGui::ColorEdit3("Specular", &node.Material.specular[0], ImGuiColorEditFlags_NoPicker);
						ImGui::ColorEdit3("Ambient", &node.Material.ambient[0], ImGuiColorEditFlags_NoPicker);
						ImGui::ColorEdit3("Emission", &node.Material.emission[0], ImGuiColorEditFlags_NoPicker);
						ImGui::Text("Alpha: %.2f", node.Material.dissolve);
						ImGui::Text("Shininess: %.2f", node.Material.shininess);

						if (ImGui::IsKeyPressed(ImGuiKey_Insert) && fs::exists(ms2RootExtracted))
						{
							std::cout << modifiers << std::endl;
							fs::path path = ms2RootExtracted / "Resource/";
							std::string editor = "cmd.exe /q /c start /b code --goto ";
							int line = -1;
							DWORD flags = 0;

							if (modifiers == (ModifierKeys::Shift | ModifierKeys::Ctrl) && entity.FlatEntry != nullptr)
							{
								flags = CREATE_NO_WINDOW;

								path = path / entity.FlatEntry->RelativePath;
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

										if (targetPortal.FlatEntry != nullptr)
										{
											ImGui::Text("Target Portal Entity Flat Name: %s", targetPortal.FlatEntry->Name.c_str());
											ImGui::Text("Target Portal Entity Flat Path: %s", targetPortal.FlatEntry->RelativePath.string().c_str());
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
						for (const std::string& name : AssetLibrary->GetModels().GetUnmappedMaterials())
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
					bool highlightDebug = (helloVk.hostUBO.drawMode & 4) != 0;

					ImGui::Checkbox("Draw Invisible Objects", &drawInvisible);
					ImGui::Checkbox("Draw Debug Objects", &drawDebug);
					ImGui::Checkbox("Highlight Debug Objects", &highlightDebug);
					ImGui::Checkbox("Draw Rig Skeletons", &debugDisplaySkeletons);

					helloVk.hostUBO.drawMode &= -1 ^ 7;
					helloVk.hostUBO.drawMode |= (highlightDebug ? 4 : 0) | (drawDebug ? 2 : 0) | (drawInvisible ? 1 : 0);

					ImGui::Checkbox("Limit Frame Rate", &helloVk.desiredVSync);
					takeScreenshot = ImGui::Button("Screenshot");
					takingLargeScreenshot |= ImGui::Button("Large Screenshot");

					if (!helloVk.takingScreenshot)
					{
						ImGui::Checkbox("Combine Large Screenshot", &helloVk.combineScreenshot);
					}

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

		if (helloVk.takingScreenshot || (takeScreenshot && !takingLargeScreenshot))
		{
			helloVk.screenshot();
		}

		if (takingLargeScreenshot)
		{
			helloVk.startScreenshot();

			takingLargeScreenshot = false;
		}

		//helloVk.updateTopLevelAS();

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
			offscreenRenderPassBeginInfo.renderPass      = helloVk.RasterRenderPass->GetRenderPass();
			offscreenRenderPassBeginInfo.framebuffer     = helloVk.OffscreenBuffer->GetFrameBuffer();
			offscreenRenderPassBeginInfo.renderArea      = {{0, 0}, helloVk.getSize()};

			VkRenderPassBeginInfo offscreenWireframeRenderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
			offscreenWireframeRenderPassBeginInfo.clearValueCount = 2;
			offscreenWireframeRenderPassBeginInfo.pClearValues    = clearValues.data();
			offscreenWireframeRenderPassBeginInfo.renderPass      = helloVk.WireframeRenderPass->GetRenderPass();
			offscreenWireframeRenderPassBeginInfo.framebuffer     = helloVk.OffscreenWireframeBuffer->GetFrameBuffer();
			offscreenWireframeRenderPassBeginInfo.renderArea      = {{0, 0}, helloVk.getSize()};

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

			if (debugDisplaySkeletons)
			{
				vkCmdBeginRenderPass(cmdBuf, &offscreenWireframeRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
				helloVk.drawWireframes(cmdBuf);
				vkCmdEndRenderPass(cmdBuf);
			}
		}

		// 2nd rendering pass: tone mapper, UI
		{
			VkRenderPassBeginInfo postRenderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
			postRenderPassBeginInfo.clearValueCount = 2;
			postRenderPassBeginInfo.pClearValues    = clearValues.data();
			postRenderPassBeginInfo.renderPass      = helloVk.DeviceRenderPass->GetRenderPass();
			postRenderPassBeginInfo.framebuffer     = helloVk.DeviceBuffers[curFrame]->GetFrameBuffer();
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
