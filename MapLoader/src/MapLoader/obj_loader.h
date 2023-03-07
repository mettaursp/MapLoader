/*
 * Copyright (c) 2021, NVIDIA CORPORATION.  All rights reserved.
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

#pragma once
#include <nvmath.h>
#include <tinyobjloader/tiny_obj_loader.h>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <vulkan/vulkan_core.h>
#include <host_device.h>
#include "Assets/TextureLibrary.h"

using MaterialObjTextures = MaterialTextures;
using MaterialObj = WaveFrontMaterial;

//struct MaterialObjTextures
//{
//	int textureID = -1;
//	int diffuseTransformId = -1;
//	int specularID = -1;
//	int specularTransformId = -1;
//	int normalID = -1;
//	int normalTransformId = -1;
//	int colorOverrideID = -1;
//	int colorOverrideTransformId = -1;
//	int emissiveID = -1;
//	int emissiveTransformId = -1;
//	int decalId = -1;
//	int decalTransformId = -1;
//};

// Structure holding the material
//struct MaterialObj
//{
//	nvmath::vec3f ambient       = nvmath::vec3f(0.1f, 0.1f, 0.1f);
//	nvmath::vec3f diffuse       = nvmath::vec3f(0.7f, 0.7f, 0.7f);
//	nvmath::vec3f specular      = nvmath::vec3f(1.0f, 1.0f, 1.0f);
//	nvmath::vec3f transmittance = nvmath::vec3f(0.0f, 0.0f, 0.0f);
//	nvmath::vec3f emission      = nvmath::vec3f(0.0f, 0.0f, 0.10);
//	float         shininess     = 0.f;
//	float         ior           = 1.0f;  // index of refraction
//	float         dissolve      = 1.f;   // 1 == opaque; 0 == fully transparent
//																			 // illumination model (see http://www.fileformat.info/format/material/)
//	int shaderType     = -1;
//	MaterialObjTextures textures;
//	//int textureID = -1;
//	//int diffuseTransformId = -1;
//	//int specularID = -1;
//	//int specularTransformId = -1;
//	//int normalID = -1;
//	//int normalTransformId = -1;
//	//int colorOverrideID = -1;
//	//int colorOverrideTransformId = -1;
//	//int emissiveID = -1;
//	//int emissiveTransformId = -1;
//	//int decalId = -1;
//	//int decalTransformId = -1;
//	int textureModes = 0;
//};
// OBJ representation of a vertex
// NOTE: BLAS builder depends on pos being the first member
struct VertexObj
{
	vec3 pos;
	vec3 nrm;
	vec4 color;
	vec2 texCoord;
	vec3 binormal;
	vec3 tangent;
};


struct shapeObj
{
	uint32_t offset;
	uint32_t nbIndex;
	uint32_t matIndex;
};

class ObjLoader
{
public:
		ObjLoader() {}
	void loadModel(const std::string& filename);
	void loadModel(const tinyobj::attrib_t& attribs, const std::vector<tinyobj::material_t>& materials, const std::vector<tinyobj::shape_t>& shapes);

	std::vector<VertexObj>   m_vertices;
	std::vector<uint32_t>    m_indices;
	std::vector<MaterialObj> m_materials;
	std::vector<std::string> m_textures;
	std::shared_ptr<MapLoader::TextureLibrary> TextureLibrary;
	std::vector<std::string> m_textures2;
	std::vector<int32_t>     m_matIndx;
};
