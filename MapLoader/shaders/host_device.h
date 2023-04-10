/*
 * Copyright (c) 2019-2021, NVIDIA CORPORATION.  All rights reserved.
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
 * SPDX-FileCopyrightText: Copyright (c) 2019-2021 NVIDIA CORPORATION
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef COMMON_HOST_DEVICE
#define COMMON_HOST_DEVICE

#ifdef __cplusplus
#include <nvmath.h>
// GLSL Type
using uint = unsigned int;
using uint64_t = unsigned long long;
#endif

// clang-format off
#ifdef __cplusplus // Descriptor binding helper for C++ and GLSL
 #define START_BINDING(a) enum a {
 #define END_BINDING() }
#define WITH_DEFAULT(x) = x
#else
#extension GL_EXT_shader_explicit_arithmetic_types_int8 : require
 #define START_BINDING(a)  const uint
 #define END_BINDING() 
#define WITH_DEFAULT(x)
#endif

START_BINDING(SceneBindings)
	eGlobals  = 0,  // Global uniform containing camera matrices
	eObjDescs = 1,  // Access to the object descriptions
	eTextures = 2,   // Access to textures
	eLights = 3,
	eTextureTransforms = 4,
	eMouseIO = 5,
	eInstDescs = 6,
	eTextureOverrides = 7
END_BINDING();

START_BINDING(RtxBindings)
	eTlas     = 0,  // Top-level acceleration structure
	eOutImage = 1   // Ray tracer output image
END_BINDING();

START_BINDING(LightingModels)
	ePhong  = 0,
	eMS2Phong = 1
END_BINDING();

START_BINDING(MaterialTypes)
	eNone = -1,
	eMS2StandardMaterial  = 0,
	eMS2ShimmerMaterial = 1,
	eMS2GlowMaterial = 2,
	eMS2CharacterSkinMaterial = 3,
	eMS2CharacterMaterial = 4,
	eMS2CharacterHairMaterial = 5,
	eMS2GlassMaterial = 6
END_BINDING();
// clang-format on

struct MeshDesc
{
	int displayFlags WITH_DEFAULT(0);
	uint64_t vertexPosAddress WITH_DEFAULT(0);      // Address of the Vertex buffer
	uint64_t vertexBinormalAddress WITH_DEFAULT(0); // Address of the Vertex buffer
	uint64_t vertexMorphAddress WITH_DEFAULT(0);    // Address of the Vertex buffer
	uint64_t vertexBlendAddress WITH_DEFAULT(0); // Address of the Vertex buffer
	uint64_t indexAddress WITH_DEFAULT(0);          // Address of the index buffer
	uint64_t materialAddress WITH_DEFAULT(0);       // Address of the material buffer
	uint64_t materialIndexAddress WITH_DEFAULT(0);  // Address of the triangle material index buffer
};

struct WireframeDesc
{
	uint64_t vertexAddress WITH_DEFAULT(0);      // Address of the Vertex buffer
	uint64_t indexAddress WITH_DEFAULT(0);          // Address of the index buffer
};

struct InstDesc
{
	vec3 color;
	int flags WITH_DEFAULT(0);
	vec3 primaryColor;
	int textureOverride WITH_DEFAULT(-1);
	vec3 secondaryColor;
	uint64_t vertexPosAddressOverride WITH_DEFAULT(0);
	uint64_t vertexBinormalAddressOverride WITH_DEFAULT(0);
};

struct LightDesc
{
	vec3 position;
	int type;
	vec3 direction;
	float brightness WITH_DEFAULT(1);
	vec3 diffuse;
	float range;
	vec3 specular;
	int padding;
	vec3 ambient;
	bool castsShadows;
};

// Uniform buffer set at each frame
struct GlobalUniforms
{
	mat4 viewProj;     // Camera view * projection
	mat4 viewInverse;  // Camera inverse view matrix
	mat4 projInverse;  // Camera inverse projection matrix
	float nearPlane WITH_DEFAULT(1);
	float fov WITH_DEFAULT(60);
	int lightCount WITH_DEFAULT(0);
	int mouseX WITH_DEFAULT(0);
	int mouseY WITH_DEFAULT(0);
	int hitIndex WITH_DEFAULT(0);
	int lightingModel WITH_DEFAULT(1);
	int skyLightMode WITH_DEFAULT(0);
	int drawMode WITH_DEFAULT(0);
};

struct AnimationTask
{
	mat4 modelMatrix;

	uint64_t vertices WITH_DEFAULT(0);

	uint64_t vertexPosAddress WITH_DEFAULT(0);      // Address of the Vertex buffer
	uint64_t vertexBinormalAddress WITH_DEFAULT(0); // Address of the Vertex buffer
	uint64_t vertexMorphAddress WITH_DEFAULT(0);    // Address of the Vertex buffer
	uint64_t vertexBlendAddress WITH_DEFAULT(0); // Address of the Vertex buffer
	uint64_t indexAddress WITH_DEFAULT(0);          // Address of the index buffer

	uint64_t skeletonAddress WITH_DEFAULT(0);
	uint64_t skeletonIndicesAddress WITH_DEFAULT(0);
	
	uint64_t vertexPosAddressOverride WITH_DEFAULT(0);
	uint64_t vertexBinormalAddressOverride WITH_DEFAULT(0);
};

// Push constant structure for the raster
struct PushConstantRaster
{
	mat4  modelMatrix;  // matrix of the instance
	vec3  lightPosition;
	uint  objIndex;
	float lightIntensity;
	int   lightType;
};


// Push constant structure for the ray tracer
struct PushConstantRay
{
	vec4  clearColor;
	int mouseX;
	int mouseY;
	int hitIndex;
	int width;
	int height;
	int offsetX;
	int offsetY;
};

struct TextureTransform
{
	vec2 translation WITH_DEFAULT(vec2(0, 0));
	vec2 scale WITH_DEFAULT(vec2(1, 1));
	vec2 pivot WITH_DEFAULT(vec2(0, 0));
	float rotation WITH_DEFAULT(0);
	int mode WITH_DEFAULT(0);
};

struct VertexPosBinding
{
	vec3 position;
	vec2 texcoord;
	vec3 normal;
	u8vec4 color WITH_DEFAULT(0xFFFFFFFF);
};

struct VertexBinormalBinding
{
	vec3 binormal;
	vec3 tangent;
};

struct VertexMorphBinding
{
	vec3 morphpos;
};

struct VertexBlendBinding
{
	u8vec4 blendindices WITH_DEFAULT(0);
	vec4 blendweight;
};

struct MaterialTexture
{
	int   id WITH_DEFAULT(-1);
	int   transformId WITH_DEFAULT(-1);
};

struct MaterialTextures
{
	MaterialTexture diffuse;
	MaterialTexture specular;
	MaterialTexture normal;
	MaterialTexture colorOverride;
	MaterialTexture emissive;
	MaterialTexture decal;
	MaterialTexture anisotropic;
};

struct WaveFrontMaterial  // See ObjLoader, copy of MaterialObj, could be compressed for device
{
	vec3  ambient WITH_DEFAULT(vec3(0.1f, 0.1f, 0.1f));
	float colorBoost WITH_DEFAULT(1);
	vec3  diffuse WITH_DEFAULT(vec3(0.7f, 0.7f, 0.7f));
	float dissolve WITH_DEFAULT(1);  // 1 == opaque; 0 == fully transparent
	vec3  specular WITH_DEFAULT(vec3(1.0f, 1.0f, 1.0f));
	float shininess WITH_DEFAULT(1);
	vec3  transmittance WITH_DEFAULT(vec3(0.0f, 0.0f, 0.0f));
	float ior WITH_DEFAULT(1);       // index of refraction
	vec3  emission WITH_DEFAULT(vec3(0.0f, 0.0f, 0.10));
	int   shaderType WITH_DEFAULT(-1);     // illumination model (see http://www.fileformat.info/format/material/)
	int textures WITH_DEFAULT(0);
	int   textureModes WITH_DEFAULT(0);
	float fresnelBoost WITH_DEFAULT(0);
	float fresnelExponent WITH_DEFAULT(1);
	/* bits:
	*  0- 1: texture apply mode
	*  2- 3: source vertex mode
	*     4: lighting mode
	*  5- 8: sourceBlend
	*  9-12: destBlend
	*    13: alpha test enabled
	* 14-16: alpha test
	* 17-20: alpha threshold
	*/
};

struct MouseRayOut
{
	vec3 hitPosition;
	int objectIndex;
};


#endif
