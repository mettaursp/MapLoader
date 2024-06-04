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
#include <ArchiveParser/XmlReader.h>
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
#include "Scene/AnimationPlayer.h"

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
			mapFile.Read(documentBuffer);

			SupportSettings feature;
			SupportSettings locale;

			XmlLite::XmlReader document;

			document.OpenDocument(documentBuffer);

			document.GetFirstChild();

			XmlLite::XmlReader::StackMarker envMarker = document.GetStackMarker();

			for (const XmlLite::XmlNode* envNode = document.GetFirstChild(); envNode; envNode = document.GetNextSibling(envMarker))
			{
				if (!isNodeEnabled(document, &feature, &locale)) continue;

				const XmlLite::XmlNode* xblock = document.GetFirstChild("xblock");

				if (xblock == nullptr) continue;

				xblockName = document.ReadAttributeValue<std::string_view>("name", "");
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

	xblockFile.Read(flatDocumentBuffer);

	XmlLite::XmlReader document;

	document.OpenDocument(flatDocumentBuffer);

	document.GetFirstChild();

	if (document.GetFirstChild("entitySet") == nullptr) return;

	mapIndices[mapId] = (int)loadedMaps.size();
	loadedMaps.push_back(LoadedMap{ mapId, mapNames[mapId], {}, ms2ToWorld, xblockFile.GetPath().string() });

	size_t directionalLight = -1;

	MapLoader::FlatLight ambient;
	bool hasAmbient = false;

	XmlLite::XmlReader::StackMarker entityMarker = document.GetStackMarker();

	for (const XmlLite::XmlNode* entityNode = document.GetFirstChild(); entityNode; entityNode = document.GetNextSibling(entityMarker))
	{
		size_t lineNumber = document.GetLineNumber();

		std::string_view id = document.ReadAttributeValue<std::string_view>("id", "");
		std::string_view modelName = document.ReadAttributeValue<std::string_view>("modelName", "");
		std::string_view entityName = document.ReadAttributeValue<std::string_view>("name", "");

		MapLoader::FlatEntry flatentry = AssetLibrary->GetFlats().FetchFlat(modelName);
		MapLoader::FlatEntity flatEntity = AssetLibrary->GetFlats().GetEntity(flatentry.Entity);

		if (flatentry.Entity == (size_t)-1)
			continue;

		MapLoader::FlatLibrary& mapData = AssetLibrary->GetMapData();

		MapLoader::FlatEntry entityEntry = mapData.LoadEntityFromFlat(flatentry, document);
		MapLoader::FlatEntity entity = mapData.GetEntity(entityEntry.Entity);

		entity.Id = id;

		if (entity.Light != (size_t)-1 && loadLights)
		{
			MapLoader::FlatLight& light = mapData.GetLight(entity.Light);

			if (light.Type == MapLoader::EntityLightType::Ambient)
			{
				hasAmbient = true;
				ambient = light;
			}
			else
			{
				MapLoader::FlatPlaceable& placeable = mapData.GetPlaceable(entity.Placeable);

				Vector3F direction = -(/*ms2ToWorld */ placeable.Transformation.FrontVector()).Unit();
				Vector3F position = /*ms2ToWorld */ Vector3F(placeable.Position, 1);

				helloVkPtr->lights.push_back(LightDesc{});

				LightDesc& newLight = helloVkPtr->lights.back();

				if (light.Type == MapLoader::EntityLightType::Directional && directionalLight == -1)
					directionalLight = helloVkPtr->lights.size() - 1;

				newLight.position = vec3(position.X, position.Y, position.Z);
				newLight.direction = vec3(direction.X, direction.Y, direction.Z);
				newLight.brightness = light.Dimmer;
				newLight.type = (int)light.Type;
				newLight.range = light.Range;
				newLight.diffuse = (Vector3)light.DiffuseColor;
				newLight.specular = (Vector3)light.SpecularColor;
				newLight.ambient = (Vector3)light.AmbientColor;
				newLight.castsShadows = light.CastsShadows;
			}
		}


		bool spawningCube = false;
		bool spawningProxy = false;
		bool spawnCube = false;
		Vector3SF physXBoxSize = { 1, 1, 1 };
		Matrix4F transformation;
		Vector3SF pos;

		if (entity.Placeable != (size_t)-1)
		{
			transformation = mapData.GetPlaceable(entity.Placeable).Transformation;
			pos = transformation.Translation();
		}

		if (entity.PhysXWhitebox != (size_t)-1)
		{
			spawnCube = true;
			physXBoxSize = (1 / 150.f) * mapData.GetPhysXWhitebox(entity.PhysXWhitebox).ShapeDimensions;
			transformation = transformation * Matrix4F(0, 0, -75 * physXBoxSize.Z);
		}

		bool canSpawnColliders = entity.PhysXShape != (size_t)-1 || entity.PhysXMesh != (size_t)-1;

		if (entity.Breakable != (size_t)-1)
		{
			spawnCube |= mapData.GetBreakable(entity.Breakable).NxCollision;
		}

		if (entity.MapProperties != (size_t)-1)
		{
			spawnCube |= mapData.GetMapProperties(entity.MapProperties).GeneratePhysX;

			if (mapData.GetMapProperties(entity.MapProperties).DisableCollision)
			{
				canSpawnColliders = false;
				spawnCube = false;
			}
		}
		
		const auto spawnNewModel = [&mapData, &entityEntry, &entity, &entityName, &flatentry, &flatEntity, lineNumber, &spawningProxy, &transformation, &spawnCube, &spawningCube, canSpawnColliders, &physXBoxSize](MapLoader::ModelData* model)
		{
			MapLoader::FlatPlaceable& placeable = mapData.GetPlaceable(entity.Placeable);

			SpawnedEntity* newModel = AssetLibrary->GetModels().SpawnModel(Scene.get(), model, transformation, placeable.Position, spawningCube, physXBoxSize,
				[&mapData, &placeable, &entityEntry, &entity, &spawningProxy, &spawnCube, &spawningCube, canSpawnColliders](ModelSpawnParameters& spawnParameters)
				{
					if (entity.Mesh != (size_t)-1)
						spawnParameters.NewInstance.color = (Vector3)mapData.GetMesh(entity.Mesh).MaterialColor;

					uint32_t overrideFlags = 0;

					if ((spawnParameters.NewInstance.drawFlags & VisibilityFlags::eCollider) != 0)
					{
						if (spawnCube && !spawningCube)
						{
							overrideFlags += 0;
						}

						if (spawningProxy || (!canSpawnColliders && !spawningCube)) return false;

						overrideFlags = VisibilityFlags::eCollider;
					}

					if (!placeable.IsVisible || (spawnParameters.NewInstance.drawFlags & VisibilityFlags::eHiddenObject) != 0)
						overrideFlags |= VisibilityFlags::eHiddenObject;

					if (spawningProxy)
						overrideFlags |= VisibilityFlags::eDebugObject;

					if (spawnParameters.NewInstance.drawFlags & VisibilityFlags::eHiddenObject)
						overrideFlags |= VisibilityFlags::eHiddenObject;

					if (overrideFlags != 0)
						spawnParameters.NewInstance.drawFlags = overrideFlags;

					//if (entityEntry.PhysXShape != nullptr)
					//	spawnParameters.NewInstance.drawFlags |= VisibilityFlags::eHasPhysXShape;

					bool physXMeshFlagSet = (spawnParameters.NewInstance.drawFlags & VisibilityFlags::eHasPhysXMesh) != 0;
					bool shouldGeneratePhysX = false;
					Vector3SF physXBoxSize = { 1, 1, 1 };

					if (entity.MapProperties != (size_t)-1)
						shouldGeneratePhysX = (unsigned int)mapData.GetMapProperties(entity.MapProperties).GeneratePhysX;

					if (entity.PhysXWhitebox != (size_t)-1)
					{
						shouldGeneratePhysX = true;
						physXBoxSize = (1 / 150.f) * mapData.GetPhysXWhitebox(entity.PhysXWhitebox).ShapeDimensions;
					}

					if (entity.Breakable != (size_t)-1)
					{
						shouldGeneratePhysX |= mapData.GetBreakable(entity.Breakable).NxCollision;
					}

					bool hasPhysXMesh = physXMeshFlagSet || shouldGeneratePhysX;

					if (hasPhysXMesh)
						spawnParameters.NewInstance.drawFlags |= VisibilityFlags::eHasPhysXMesh;
					else if (physXMeshFlagSet)
						spawnParameters.NewInstance.drawFlags ^= VisibilityFlags::eHasPhysXMesh;

					if (entity.Fluid != (size_t)-1)
						spawnParameters.NewInstance.drawFlags |= VisibilityFlags::eHasFluid;

					if (entity.Vibrate != (size_t)-1 && mapData.GetVibrateObject(entity.Vibrate).Enabled)
						spawnParameters.NewInstance.drawFlags |= VisibilityFlags::eHasVibrate;

					if (entity.Breakable != (size_t)-1)
					{
						spawnParameters.NewInstance.drawFlags |= VisibilityFlags::eHasBreakable;
						spawnParameters.NewInstance.drawFlags |= (unsigned int)mapData.GetBreakable(entity.Breakable).CollisionGroup;
					}

					if (entity.MapProperties != (size_t)-1)
						spawnParameters.NewInstance.drawFlags |= (unsigned int)mapData.GetMapProperties(entity.MapProperties).CubeType;

					if (entity.PhysXMesh != (size_t)-1)
						spawnParameters.NewInstance.drawFlags |= (unsigned int)mapData.GetPhysXMesh(entity.PhysXMesh).CollisionGroup;

					return true;
				}
			);// *flat->Transformation);
			newModel->Id = entity.Id;
			newModel->Name = entityName;
			newModel->FlatEntry = flatEntity.Entry;
			newModel->Position = placeable.Position;
			newModel->WorldPosition = ms2ToWorld * Vector3F(placeable.Position, 1);
			newModel->MapIndex = (int)loadedMaps.size() - 1;
			newModel->LineNumber = (int)lineNumber;

			if (entity.Portal != (size_t)-1)
			{
				MapLoader::FlatPortal& portal = mapData.GetPortal(entity.Portal);

				newModel->PortalIndex = (int)spawnedPortals.size();
				loadedMaps.back().Portals[portal.PortalId] = (int)AssetLibrary->GetModels().GetSpawnedEntities().size() - 1;

				spawnedPortals.push_back(SpawnedPortal{ portal.TargetField, portal.TargetPortal, portal.PortalId });
			}
		};

		if (entity.Mesh != (size_t)-1)
		{
			MapLoader::FlatMesh& mesh = mapData.GetMesh(entity.Mesh);

			if (mesh.Model != nullptr)
				spawnNewModel(mesh.Model);
		}

		if (spawnCube)
		{
			spawningCube = true;
			spawnNewModel(nullptr);
			spawningCube = false;
		}

		spawningProxy = true;

		if (entityEntry.Entity != (size_t)-1)
		{
			MapLoader::FlatEntity& entity = mapData.GetEntity(entityEntry.Entity);

			if (entity.ProxyModel != nullptr)
				spawnNewModel(entity.ProxyModel);
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

	file.Read(documentBuffer);

	XmlLite::XmlReader document;

	document.OpenDocument(documentBuffer);

	document.GetFirstChild();

	XmlLite::XmlReader::StackMarker keyMarker = document.GetStackMarker();

	for (const XmlLite::XmlNode* keyNode = document.GetFirstChild(); keyNode; keyNode = document.GetNextSibling(keyMarker))
	{
		std::string id = document.ReadAttributeValue<std::string>("id", "");

		mapNames[id] = document.ReadAttributeValue<std::string_view>("name", "");
	}
}

void loadMapFileNames(const Archive::ArchivePath& file)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load fielddata.xml " << file.GetPath().string() << std::endl;
		return;
	}

	file.Read(documentBuffer);

	XmlLite::XmlReader document;

	document.OpenDocument(documentBuffer);

	document.GetFirstChild();

	XmlLite::XmlReader::StackMarker fieldDataMarker = document.GetStackMarker();

	for (const XmlLite::XmlNode* fieldDataNode = document.GetFirstChild(); fieldDataNode; fieldDataNode = document.GetNextSibling(fieldDataMarker))
	{
		int id = document.ReadAttributeValue("id", 0);

		const XmlLite::XmlNode* envElement = document.GetFirstChild();

		if (envElement == nullptr) continue;

		if (envElement->Name != "environment")
		{
			continue;
		}

		XmlLite::XmlReader::StackMarker componentMarker = document.GetStackMarker();

		for (const XmlLite::XmlNode* componentElement = document.GetFirstChild(); componentElement; componentElement = document.GetNextSibling(componentMarker))
		{
			if (componentElement->Name != "xblock") continue;

			mapFileNames[id] = document.ReadAttributeValue<std::string_view>("name", "");
		}
	}
}

void LoadAniKeyText(const Archive::ArchivePath& file)
{
	if (!file.Loaded())
	{
		std::cout << "failed to load fielddata.xml " << file.GetPath().string() << std::endl;
		return;
	}

	file.Read(documentBuffer);

	XmlLite::XmlReader document;

	document.OpenDocument(documentBuffer);
	document.GetFirstChild();
	XmlLite::XmlReader::StackMarker kfmMarker = document.GetStackMarker();

	for (const XmlLite::XmlNode* kfmNode = document.GetFirstChild(); kfmNode; kfmNode = document.GetNextSibling(kfmMarker))
	{
		std::string name = std::string(document.ReadAttributeValue<std::string_view>("name", ""));

		if (name == "")
			continue;

		MapLoader::AnimationList& rig = MapLoader::RigAnimations[name];

		rig.RigName = name;

		XmlLite::XmlReader::StackMarker seqMarker = document.GetStackMarker();

		for (const XmlLite::XmlNode* sequenceElement = document.GetFirstChild(); sequenceElement; sequenceElement = document.GetNextSibling(seqMarker))
		{
			unsigned int id = document.ReadAttributeValue<unsigned int>("id", -1);
			std::string sequenceName = std::string(document.ReadAttributeValue<std::string_view>("name", ""));

			if (sequenceName == "")
				continue;

			MapLoader::Sequence& sequence = rig.Animations[sequenceName];

			sequence.Id = id;
			sequence.Name = sequenceName;

			rig.IdNames[id] = sequenceName;

			XmlLite::XmlReader::StackMarker keyMarker = document.GetStackMarker();

			for (const XmlLite::XmlNode* keyElement = document.GetFirstChild(); keyElement; keyElement = document.GetNextSibling(keyMarker))
			{
				std::string keyName = std::string(document.ReadAttributeValue<std::string_view>("name", ""));
				float time = document.ReadAttributeValue<float>("time", 0);

				if (keyName == "")
					continue;

				sequence.Keyframes.push_back({ keyName, time });
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

	if (mapId != nullptr)
		std::cout << "opening map: " << mapId << std::endl;

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
	Scene = std::make_shared<MapLoader::RTScene>(AssetLibrary);
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
	AssetLibrary->GetModels().GenerateDefaultCube();
	AssetLibrary->GetEmotions().LoadEmotions(Reader);

	loadMapNames(Reader->GetPath("Xml/string/en/mapname.xml"));
	loadMapFileNames(Reader->GetPath("Xml/table/fielddata.xml"));
	LoadAniKeyText(Reader->GetPath("Xml/anikeytext.xml"));

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

		AssetLibrary->GetModels().SetCurrentMapTransform(ms2ToWorld);

		std::cout << "loading map " << maps[i].id << std::endl;

		loadMap(maps[i].id);

		loadLights = false;
	}

	ms2ToWorld = ms2toworld;
	AssetLibrary->GetModels().SetCurrentMapTransform(ms2ToWorld);
	loadLights = true;

	if (mapId != nullptr)
		loadMap(mapId);

	MapLoader::CharacterData baadf00d;

	baadf00d.Gender = Gender::Female;
	baadf00d.Face = { .Id = 10300097, .Color = dyeColors.GetDyeColor("Light Green", true) };
	baadf00d.FaceDecor = { { .Id = 10400010 } };
	baadf00d.SkinColor = dyeColors.GetDyeColor(3);
	baadf00d.Hair = { { .Id = 10200250, .Color = dyeColors.GetDyeColor("Pink") }, 1 };
	baadf00d.Cosmetics.Hat = { { .Id = 11300743, .Color = dyeColors.GetDyeColor("Red") }, Vector3SF(30, 0, 0), Vector3SF(10, 25, 20), Vector3SF(-5, 0, 0) };
	baadf00d.Cosmetics.Shirt = { .Id = 11401065, .Color = dyeColors.GetDyeColor("Light Pink") };
	baadf00d.Cosmetics.Pants = { .Id = 11500163, .Color = dyeColors.GetDyeColor("Pink") };
	baadf00d.Cosmetics.Gloves = { .Id = 11620024, .Color = dyeColors.GetDyeColor("Red") };
	baadf00d.Cosmetics.Shoes = { .Id = 11700313, .Color = dyeColors.GetDyeColor("Light Pink") };

	Character f00dCharacter(AssetLibrary, Scene);

	f00dCharacter.Load(&baadf00d, Matrix4F(-2250, -1200, 1785) * Matrix4F::RollRotation(-0.5f * PI));

	MapLoader::CharacterData hornetsp;

	hornetsp.Gender = Gender::Male;
	hornetsp.Face = { .Id = 10300014, .Color = dyeColors.GetDyeColor("Blue") };
	hornetsp.FaceDecor = { { .Id = 10400006, .Color = dyeColors.GetDyeColor("Blue"), .Preset = 0 } };
	hornetsp.SkinColor = dyeColors.GetDyeColor(12);
	hornetsp.Hair = { { .Id = 10200001, .Color = dyeColors.GetDyeColor("Green") } };
	hornetsp.Cosmetics.Hat = { { .Id = 11380431, .Color = dyeColors.GetDyeColor("Green") } };
	hornetsp.Cosmetics.Shirt = { .Id = 11480386, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Pants = { .Id = 11500660, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Gloves = { .Id = 11600864, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Shoes = { .Id = 11790671, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Cosmetics.Cape = { .Id = 11890080, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Earring = { .Id = 11200064, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Pendant = { .Id = 11900122, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Belt = { .Id = 12100112, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Ring = { .Id = 12060106, .Color = dyeColors.GetDyeColor("Green") };
	hornetsp.Gear.Weapon = { .Id = 15460178, .Color = dyeColors.GetDyeColor("Green") };

	Character hornetCharacter(AssetLibrary, Scene);

	hornetCharacter.Load(&hornetsp, Matrix4F(-2250, -1050, 1785) * Matrix4F::RollRotation(-0.5f * PI));

	MapLoader::CharacterData blazemodz;

	blazemodz.Gender = Gender::Female;
	blazemodz.Face = { .Id = 10300097, .Color = dyeColors.GetDyeColor("Light Green", true) };
	blazemodz.SkinColor = dyeColors.GetDyeColor(3);
	blazemodz.Hair = { { .Slot = MapLoader::ItemSlotType::Hair, .Id = 10200056, .Color = dyeColors.GetDyeColor("Orange") }, 1 };
	blazemodz.Cosmetics.Hat = { { .Id = 11150053, .Color = dyeColors.GetDyeColor("Black") } };
	blazemodz.Cosmetics.Shirt = { .Id = 11400031, .Color = dyeColors.GetDyeColor("Black") };
	blazemodz.Cosmetics.Pants = { .Id = 11500541, .Color = dyeColors.GetDyeColor("Black") };
	blazemodz.Cosmetics.Shoes = { .Id = 11700230, .Color = dyeColors.GetDyeColor("Black") };
	blazemodz.EmotionFrame = 1;

	Character blazemodzCharacter(AssetLibrary, Scene);

	blazemodzCharacter.Load(&blazemodz, Matrix4F(-2900, -2700, 3000)* Matrix4F::RollRotation(-0.25f * PI));

	const Archive::Metadata::Entry* derpPandaAnimationEntry = Archive::Metadata::Entry::FindFirstEntryByTags("60000053_LesserPanda", "gamebryo-animation");

	MapLoader::RigAnimationData* derpPandaAnimData = AssetLibrary->GetAnimations().FetchRigAnimations(derpPandaAnimationEntry);

	MapLoader::ModelData* derpPandaModel = nullptr;
	std::shared_ptr<MapLoader::SkinnedModel> derpPandaRig = Engine::Create<MapLoader::SkinnedModel>(AssetLibrary, Scene);

	std::shared_ptr<Engine::Transform> derpPandaTransform = Engine::Create<Engine::Transform>();
	derpPandaTransform->SetTransformation(Matrix4F(-2270, -1125, 1785) * Matrix4F::RollRotation(-0.5f * PI));
	derpPandaTransform->Update(0);

	derpPandaRig->SetParent(derpPandaTransform);
	derpPandaRig->SetTransform(derpPandaTransform.get());

	derpPandaModel = AssetLibrary->GetAnimations().FetchRig(derpPandaAnimData);
	derpPandaRig->AddModel(derpPandaModel, {}, [](auto&)
		{
			return true;
		}
	);
	derpPandaRig->CreateRigDebugMesh();
	derpPandaRig->SetRigAnimations("60000053_LesserPanda");

	Scene->AddSkinnedModel(derpPandaRig);

	//const char* npcModelName = "23000011_B_LizardDragonFire";
	const char* npcModelName = "23000007_B_DevilHugeBlue";

	const Archive::Metadata::Entry* npcAnimationEntry = Archive::Metadata::Entry::FindFirstEntryByTags(npcModelName, "gamebryo-animation");

	MapLoader::RigAnimationData* npcAnimData = AssetLibrary->GetAnimations().FetchRigAnimations(npcAnimationEntry);

	MapLoader::ModelData* npcModel = nullptr;
	std::shared_ptr<MapLoader::SkinnedModel> npcRig = Engine::Create<MapLoader::SkinnedModel>(AssetLibrary, Scene);

	std::shared_ptr<Engine::Transform> npcTransform = Engine::Create<Engine::Transform>();
	npcTransform->SetTransformation(Matrix4F(-2250, -2500, 1800) * Matrix4F::RollRotation(-0.5f * PI));
	npcTransform->Update(0);

	npcRig->SetParent(npcTransform);
	npcRig->SetTransform(npcTransform.get());

	npcModel = AssetLibrary->GetAnimations().FetchRig(npcAnimData);
	npcRig->AddModel(npcModel, {}, [](auto&)
		{
			return true;
		}
	);
	npcRig->CreateRigDebugMesh();
	npcRig->SetRigAnimations(npcModelName);

	Scene->AddSkinnedModel(npcRig);

	MapLoader::ModelData* derpPandaBoreA = AssetLibrary->GetAnimations().FetchAnimation(derpPandaAnimData->FetchAnimation("Bore_A"));

	const auto& f00dModel = f00dCharacter.GetModel();

	MapLoader::RigAnimationData* femaleAnimationData = f00dModel->GetRigAnimations();
	MapLoader::RigAnimationData* maleAnimationData = hornetCharacter.GetModel()->GetRigAnimations();

	MapLoader::ModelData* emotionDanceQ = AssetLibrary->GetAnimations().FetchAnimation(femaleAnimationData->FetchAnimation("Emotion_Dance_Q"));

	struct RigReference
	{
		std::string Name;
		std::string RigName;
		MapLoader::RigAnimationData* AnimationData = nullptr;
		MapLoader::AnimationPlayer* AnimationPlayer = nullptr;
		MapLoader::RigAnimation* CurrentlyPlaying = nullptr;
		MapLoader::Sequence* PlayingSequenceData = nullptr;
		size_t AnimationIndex = (size_t)-1;
		bool Looping = false;
		float PlaybackSpeed = 1;
	};

	std::vector<RigReference> rigs = {
		{ "HornetSp", "Male", maleAnimationData, hornetCharacter.GetModel()->GetAnimationPlayer()},
		{ "BAADF00D", "Female", femaleAnimationData, f00dModel->GetAnimationPlayer()},
		{ "BlazeModz", "Female", femaleAnimationData, blazemodzCharacter.GetModel()->GetAnimationPlayer() },
		{ "Derp Panda", "60000053_LesserPanda", derpPandaAnimData, derpPandaRig->GetAnimationPlayer()},
		{ "Npc", npcModelName, npcAnimData, npcRig->GetAnimationPlayer()}
	};

	int currentRig = 3;

	const size_t searchSize = 20;
	char searchText[searchSize + 1] = { 0 };
	
	//size_t kr = Archive::Metadata::Entry::GetTag("kr");
	//size_t cn = Archive::Metadata::Entry::GetTag("cn");
	//size_t jp = Archive::Metadata::Entry::GetTag("jp");
	//
	//auto& entries = Archive::Metadata::Entry::GetTagData("gamebryo-scenegraph")->Ids;
	//size_t loaded = 0;
	//
	//for (auto index : entries)
	//{
	//	bool skip = false;
	//	for (size_t i = 0; i < index.second->Tags.size() && !skip; ++i)
	//	{
	//		skip |= index.second->Tags[i] == kr;
	//		skip |= index.second->Tags[i] == cn;
	//		skip |= index.second->Tags[i] == jp;
	//	}
	//	++loaded;
	//
	//	size_t percent = (loaded * 100) / entries.size();
	//	size_t lastPercent = (std::max(0ull, loaded - 1) * 100) / entries.size();
	//
	//	if (percent != lastPercent)
	//		std::cout << percent << "%" << std::endl;
	//
	//	if (skip) continue;
	//	AssetLibrary->GetModels().FetchModel(index.second);
	//}
	//
	//AssetLibrary->GetModels().PrintLoggedTextures();

	//loadMap("02000376"); //sb map
	//loadMap("02010011"); // ludari promenade
	//loadMap("02000415"); // lions gate
	//loadMap("99999887"); // test
	//loadMap("02000422"); // sky fort
	//loadMap("02000496"); // storms eye
	//loadMap("02020130"); // 
	//loadMap("02000083"); 
	// 
	//loadMap("02020110"); // floating worlds
	//loadMap("02020112"); // winding halls
	//loadMap("02020145"); // azure flux
	// 
	//loadMap("02020100"); // forest of sorrow
	//loadMap("02020101"); // emerald prison
	// 
	//loadMap("02020120"); // terminus of time
	// 
	//loadMap("02020130"); // blackshard nexus

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
	helloVk.createRtDescriptorSet();
	helloVk.createRtPipeline();

	helloVk.createPostPipeline();
	helloVk.updatePostDescriptorSet();

	Scene->UpdateAnimations(0);
	helloVk.updateAnimations();
	helloVk.animate();
	helloVk.updateStaleBlas();
	Scene->Update(0);

	vec4 clearColor   = vec4(1, 1, 1, 1.00f);
	bool          useRaytracer = true;


	helloVk.setupGlfwCallbacks(window);
	ImGui_ImplGlfw_InitForVulkan(window, true);

	bool takingLargeScreenshot = false;
	bool debugDisplaySkeletons = false;

	size_t totalBytesRead = AssetLibrary->GetReader()->GetTotalBytesRead();
	size_t totalDiskBytesRead = AssetLibrary->GetReader()->GetTotalDiskBytesRead();
	
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

					if (modelId >= 0 && modelId < (int)AssetLibrary->GetModels().GetSpawnedModels().size())
					{
						int entityId = AssetLibrary->GetModels().GetSpawnedModels()[modelId].EntityId;

						const SpawnedEntity& entity = AssetLibrary->GetModels().GetSpawnedEntities()[entityId];


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

						int spawnedModelId = AssetLibrary->GetModels().GetSpawnedModels()[modelId].ModelId;
						uint32_t drawFlags = AssetLibrary->GetModels().GetGpuEntityData()[modelId].drawFlags;

						ImGui::Text("Entity Name: %s", entity.Name.c_str());

						if (entity.FlatEntry != nullptr)
						{
							ImGui::Text("Entity Flat Name: %s", entity.FlatEntry->Name.c_str());
							ImGui::Text("Entity Flat Path: %s", entity.FlatEntry->RelativePath.string().c_str());
						}

						if (entity.Model != nullptr)
						{
							ImGui::Text("Entity Model Name: %s", entity.Model->Entry->Name.c_str());
							ImGui::Text("Entity Model Path: %s", entity.Model->Entry->RelativePath.string().c_str());
						}

						ImGui::Text("Entity Id: %s", entity.Id.c_str());
						ImGui::Text("Spawned Entity Position: %.3f, %.3f, %.3f", entity.WorldPosition.X, entity.WorldPosition.Y, entity.WorldPosition.Z);
						ImGui::Text("Entity Coordinates: %.3f, %.3f, %.3f", entity.Position.X, entity.Position.Y, entity.Position.Z);

						if (entity.Model != nullptr && spawnedModelId < entity.Model->Nodes.size())
						{
							MapLoader::ModelNode& node = entity.Model->Nodes[spawnedModelId];

							ImGui::Text("NiMesh Index: %d", node.NifBlockIndex);

							ImGui::Text("Shader: %s", node.Shader.c_str());
							ImGui::Text("Material: %s", node.MaterialName.c_str());
							ImGui::Text("Draw Flags: %d", drawFlags);

							ImGui::ColorEdit3("Diffuse", &node.Material.diffuse[0], ImGuiColorEditFlags_NoPicker);
							ImGui::ColorEdit3("Specular", &node.Material.specular[0], ImGuiColorEditFlags_NoPicker);
							ImGui::ColorEdit3("Ambient", &node.Material.ambient[0], ImGuiColorEditFlags_NoPicker);
							ImGui::ColorEdit3("Emission", &node.Material.emission[0], ImGuiColorEditFlags_NoPicker);
							ImGui::Text("Alpha: %.2f", node.Material.dissolve);
							ImGui::Text("Shininess: %.2f", node.Material.shininess);
						}
						else
						{
							ImGui::Text("NiMesh Index: -1");
							ImGui::Text("Generated PhysX Cube");
						}
						
						if (ImGui::IsKeyPressed(ImGuiKey_Insert) && fs::exists(ms2RootExtracted))
						{
							std::cout << modifiers << std::endl;
							fs::path path = ms2RootExtracted / "Resource";
							std::string editor = "cmd.exe /q /c start /b code --goto ";
							int line = -1;
							DWORD flags = 0;

							if (modifiers == (ModifierKeys::Shift | ModifierKeys::Ctrl) && entity.FlatEntry != nullptr)
							{
								flags = CREATE_NO_WINDOW;

								std::string flatPath = entity.FlatEntry->RelativePath.string();

								if (flatPath.size() >= 9 && flatPath.substr(0, 9) == "resource/")
									path = path.parent_path();

								path += flatPath;
								std::cout << "using vs code" << std::endl;
							}
							else if (modifiers == ModifierKeys::Alt)
							{
								editor = "\"B:/Files/NifSkope_2_0_2020-07-09-x64/NifSkope.exe\"";
								path += entity.Model->Entry->RelativePath;
								std::cout << "using nifskope" << std::endl;
							}
							else if (modifiers == ModifierKeys::Ctrl)
							{
								flags = CREATE_NO_WINDOW;

								const std::string& xblockPath = loadedMaps[entity.MapIndex].XBlockPath;

								if (xblockPath.size() >= 9 && xblockPath.substr(0, 9) == "resource/")
									path = path.parent_path();
								
								path = path / xblockPath;

								line = entity.LineNumber;
								std::cout << "using vs code" << std::endl;
							}
							else
							{
								path = "err";
							}

							std::cout << "opening " << path.string() << std::endl;

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
										const SpawnedEntity& targetPortal = AssetLibrary->GetModels().GetSpawnedEntities()[targetPortalIndex->second];

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

					helloVk.hostUBO.lightingModelOffset = 2 * helloVk.hostUBO.lightingModel * helloVk.RTShaderCount;

					ImGui::Text("Sky Light:");
					ImGui::RadioButton("Map Lights", &helloVk.hostUBO.skyLightMode, 0);
					ImGui::RadioButton("Dynamic Sky", &helloVk.hostUBO.skyLightMode, 1);

					if (helloVk.hostUBO.skyLightMode == 1)
					{

					}

					ImGui::Checkbox("Limit Frame Rate", &helloVk.desiredVSync);
					takeScreenshot = ImGui::Button("Screenshot");
					takingLargeScreenshot |= ImGui::Button("Large Screenshot");

					if (!helloVk.takingScreenshot)
					{
						ImGui::Checkbox("Combine Large Screenshot", &helloVk.combineScreenshot);
					}

					if (ImGui::CollapsingHeader("Animations"))
					{
						ImGui::Text("Selected Rig:");

						for (size_t i = 0; i < rigs.size(); ++i)
						{
							ImGui::RadioButton(rigs[i].Name.c_str(), &currentRig, (int)i);
						}

						auto& rig = rigs[currentRig];

						if (rig.AnimationIndex == (size_t)-1)
							rig.CurrentlyPlaying = nullptr;
						else if (!rig.AnimationPlayer->IsPlaying(rig.AnimationIndex))
						{
							rig.AnimationIndex = (size_t)-1;
							rig.CurrentlyPlaying = nullptr;
						}

						if (rig.CurrentlyPlaying != nullptr)
						{
							std::string currentlyPlaying = "Currently Playing: " + rig.CurrentlyPlaying->Name;

							ImGui::Text(currentlyPlaying.c_str());
						}
						else
							ImGui::Text("Currently Playing: [None]");

						MapLoader::RigAnimation* playingNext = rig.CurrentlyPlaying;

						if (ImGui::CollapsingHeader("Rig Animations:"))
						{
							ImGui::InputText("##AnimationSearch", searchText, searchSize);
							ImGui::BeginChild("AnimationsPanel", ImVec2(0, 300), true);

							for (size_t i = 0; i < rig.AnimationData->Animations.size(); ++i)
							{
								const std::string& name = rig.AnimationData->Animations[i].Name;
								if (searchText[0] != 0)
								{
									if (!containsCaseInsensitive(name, searchText))
										continue;
								}
								std::stringstream buttonText;
								buttonText << name << " (" << rig.AnimationData->Animations[i].Id << ")##" << rig.RigName << ";" << i;
								std::string text = buttonText.str();

								if (ImGui::Button(text.c_str()))
								{
									playingNext = &rig.AnimationData->Animations[i];
								}
							}

							ImGui::EndChild();
						}
						
						if (playingNext != rig.CurrentlyPlaying)
						{
							if (rig.CurrentlyPlaying != nullptr)
								rig.AnimationPlayer->Stop(rig.AnimationIndex);

							AssetLibrary->GetAnimations().FetchAnimation(playingNext);

							rig.CurrentlyPlaying = playingNext;
							rig.AnimationIndex = rig.AnimationPlayer->PlayAnimation(playingNext);
						}

						ImGui::Checkbox("Looping", &rig.Looping);
						ImGui::InputFloat("Playback Speed", &rig.PlaybackSpeed);

						float time = 0;
						float playbackSpeed = rig.PlaybackSpeed;
						float duration = 0;

						if (rig.CurrentlyPlaying != nullptr)
						{
							time = rig.AnimationPlayer->GetTime(rig.AnimationIndex);
							duration = rig.CurrentlyPlaying->Duration;
						}

						if (ImGui::SliderFloat("Time", &time, 0, duration) && rig.CurrentlyPlaying != nullptr)
						{
							playbackSpeed = 0;
							rig.AnimationPlayer->SetTime(rig.AnimationIndex, time);
						}

						rig.PlayingSequenceData = nullptr;

						if (rig.CurrentlyPlaying != nullptr)
						{
							rig.AnimationPlayer->SetLooping(rig.AnimationIndex, rig.Looping);
							rig.AnimationPlayer->SetPlaybackSpeed(rig.AnimationIndex, rig.PlaybackSpeed);

							if (rig.AnimationData && rig.AnimationData->AnimationList)
							{
								auto entry = rig.AnimationData->AnimationList->Animations.find(rig.CurrentlyPlaying->Name);

								if (entry != rig.AnimationData->AnimationList->Animations.end())
								{
									rig.PlayingSequenceData = &entry->second;
								}
							}
						}

						if (ImGui::BeginTable("Keyframes Panel", 2))
						{
							ImGui::TableNextRow();

							ImGui::TableSetColumnIndex(0);
							ImGui::Text("Key Frame");

							ImGui::TableSetColumnIndex(1);
							ImGui::Text("Time");

							if (rig.PlayingSequenceData)
							{
								size_t index = 0;

								for (MapLoader::SequenceKeyframe& keyframe : rig.PlayingSequenceData->Keyframes)
								{
									ImGui::TableNextRow();

									std::stringstream keyframeName;
									keyframeName << keyframe.Name + "##KeyframesPanel" << index;
									ImGui::TableSetColumnIndex(0);
									
									if (ImGui::Button(keyframeName.str().c_str()))
									{
										time = keyframe.Time;

										rig.AnimationPlayer->SetTime(rig.AnimationIndex, time);
									}

									std::stringstream keyframeValue;
									keyframeValue << keyframe.Time;
									ImGui::TableSetColumnIndex(1);
									ImGui::Text(keyframeValue.str().c_str());

									++index;
								}
							}

							ImGui::EndTable();
						}
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Debug Settings"))
				{
					ImGui::Checkbox("Draw Rig Skeletons", &debugDisplaySkeletons);
					ImGui::Text("Show World Slice:");

					int sliceIndex = helloVk.hostUBO.sliceAxisIndex;

					ImGui::RadioButton("None", &sliceIndex, -1);
					ImGui::RadioButton("X", &sliceIndex, 0);
					ImGui::RadioButton("Y", &sliceIndex, 1);
					ImGui::RadioButton("Z", &sliceIndex, 2);

					helloVk.hostUBO.sliceAxisIndex = sliceIndex;

					if (sliceIndex != -1)
					{
						ImGui::InputFloat("Axis", &helloVk.hostUBO.sliceAxis);
						ImGui::InputFloat("Epsilon", &helloVk.hostUBO.sliceAxisEpsilon);
					}

					const char* const drawFlagLabels[] = {
						"Standard Objects",
						"Colliders",
						"Objects With Invisibility",
						"Debug/Proxy Objects",
						"Hidden Objects",
						"Objects With Shadows",
						"Has PhysX Meshes",
						"Has Fluid",
						"Has Vibrate",
						"Has Breakable",
						"CubeType.None",
						"CubeType.Ground",
						"CubeType.Fluid",
						"CubeType.Wall",
						"CubeType.Object",
						"CubeType.Building",
						"Collision Group 0",
						"Collision Group 7",
						"Collision Group 8",
						"Collision Group 9",
						"Collision Group Misc",
						"Objects With Transparency",
						nullptr
					};
					const size_t count = sizeof(drawFlagLabels) / sizeof(drawFlagLabels[0]) - 1;

					bool drawFlags[count] = { false };
					bool highlightFlags[count] = { false };

					for (size_t i = 0; i < count; ++i)
					{
						drawFlags[i] = (helloVk.hostUBO.drawMask & ((size_t)1 << i)) != 0;
						highlightFlags[i] = (helloVk.hostUBO.highlightMask & ((size_t)1 << i)) != 0;
					}


					if (ImGui::CollapsingHeader("Draw Object Types"))
					{
						for (size_t i = 0; i < count && drawFlagLabels[i]; ++i)
						{
							ImGui::Checkbox(drawFlagLabels[i], &drawFlags[i]);
						}
					}

					if (ImGui::CollapsingHeader("Highlight Object Types"))
					{
						for (size_t i = 0; i < count && drawFlagLabels[i]; ++i)
						{
							std::string label = drawFlagLabels[i];
							label += "##highlight";

							ImGui::Checkbox(label.c_str(), &highlightFlags[i]);
						}
					}

					uint32_t drawMask = 0;
					uint32_t highlightMask = 0;

					for (size_t i = 0; i < count; ++i)
					{
						drawMask |= (uint64_t)drawFlags[i] << i;
						highlightMask |= (uint64_t)highlightFlags[i] << i;
					}

					helloVk.hostUBO.drawMask = drawMask;
					helloVk.hostUBO.highlightMask = highlightMask;
					helloVk.hostUBO.drawMaskHighlightPos = count;

					if (ImGui::CollapsingHeader("Highlight Materials"))
					{
						bool highlightMaterialFlags[32] = { false };
						const char* materialNames[16] = { nullptr };

						const auto& models = AssetLibrary->GetModels();

						for (const auto& index : models.MaterialTypeMap)
						{
							size_t i = index.second + 1;

							materialNames[i] = index.first.c_str();

							if (materialNames[i][0] == 0)
								materialNames[i] = "Default";

							highlightMaterialFlags[i] = (helloVk.hostUBO.highlightMaterialFlags & (1 << i)) != 0;
						}

						for (size_t i = 0; i < 16; ++i)
						{
							if (materialNames[i] == nullptr) continue;

							ImGui::Checkbox(materialNames[i], &highlightMaterialFlags[i]);
						}

						uint32_t materialMask = 0;

						for (size_t i = 0; i < 16; ++i)
						{
							materialMask |= highlightMaterialFlags[i] << i;
						}

						helloVk.hostUBO.highlightMaterialFlags = materialMask;
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
		float delta = 1 / ImGui::GetIO().Framerate;
		Scene->UpdateAnimations(delta);
		helloVk.updateAnimations();
		helloVk.animate();
		helloVk.updateStaleBlas();
		Scene->Update(delta);
		helloVk.updateRtDescriptorSet();

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

	hornetCharacter.ReleaseResources();
	f00dCharacter.ReleaseResources();
	blazemodzCharacter.ReleaseResources();
	derpPandaRig->ReleaseResources();
	npcRig->ReleaseResources();
	helloVk.destroyResources();
	helloVk.destroy();
	vkctx.deinit();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
