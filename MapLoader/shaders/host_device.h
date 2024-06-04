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
 #define START_BINDING_64(a) enum a : uint64_t {
 #define END_BINDING() }
#define WITH_DEFAULT(x) = x
#else
#extension GL_EXT_shader_explicit_arithmetic_types_int8 : require
#extension GL_EXT_shader_explicit_arithmetic_types_int32 : require
#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
 #define START_BINDING(a)  const uint
 #define START_BINDING_64(a)  const uint64_t
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
	eTextureOverrides = 7,
	eMaterials = 8
END_BINDING();

START_BINDING(RtxBindings)
	eTlas     = 0,  // Top-level acceleration structure
	eOutImage = 1   // Ray tracer output image
END_BINDING();

START_BINDING(LightingModels)
	ePhong  = 0,
	eMS2Phong = 1,

	eLightingModelCount = 2
END_BINDING();

START_BINDING(MaterialTypes)
	eDefaultMaterial = -1,
	eMS2StandardMaterial  = 0,
	eMS2ShimmerMaterial = 1,
	eMS2GlowMaterial = 2,
	eMS2CharacterSkinMaterial = 3,
	eMS2CharacterMaterial = 4,
	eMS2CharacterHairMaterial = 5,
	eMS2GlassMaterial = 6,
	eLightMapMaterial = 7,
	eEffectDissolve_HO = 8,
	eEffectUVDistortionMask_HO = 9,
	eEffectUVDistortionMaskGlow_HO = 10,
	eEffectUVDistortionMaskWrap_HO = 11,
	eEffectUVDistortionMaskGlowWrap_HO = 12,
	eNiStandardMaterial = 13
END_BINDING();

START_BINDING(VisibilityFlags)
	eDisabledObject = 0x0,
	eStandardVisibility = 0x1,
	eCollider = 0x2,
	eHasInvisibility = 0x4,
	eDebugObject = 0x8,
	eHiddenObject = 0x10,
	eHasShadow = 0x20,
	eHasPhysXMesh = 0x40,
	eHasFluid = 0x80,
	eHasVibrate = 0x100,
	eHasBreakable = 0x200,
	eCubeTypeNone = 0x400,
	eCubeTypeGround = 0x800,
	eCubeTypeFluid = 0x1000,
	eCubeTypeWall = 0x2000,
	eCubeTypeObject = 0x4000,
	eCubeTypeBuilding = 0x8000,
	eCollisionGroup0 = 0x10000,
	eCollisionGroup7 = 0x20000,
	eCollisionGroup8 = 0x40000,
	eCollisionGroup9 = 0x80000,
	eCollisionGroupMisc = 0x100000,
	eHasTransparency = 0x200000
END_BINDING();

START_BINDING(SpecializationTypes)
	eLightingModel = 0,
	eMaterial = 1,
	eMaterialTextureFlags = 2
END_BINDING();

START_BINDING(MaterialTextureBits)
	eCanHaveDiffuse = 0x1,
	eAlwaysHasDiffuse = 0x2,
	eCanHaveSpecular = 0x4,
	eAlwaysHasSpecular = 0x8,
	eCanHaveNormal = 0x10,
	eAlwaysHasNormal = 0x20,
	eCanHaveColorOverride = 0x40,
	eAlwaysHasColorOverride = 0x80,
	eCanHaveEmissive = 0x100,
	eAlwaysHasEmissive = 0x200,
	eCanHaveDecal = 0x400,
	eAlwaysHasDecal = 0x800,
	eCanHaveAnisotropic = 0x1000,
	eAlwaysHasAnisotropic = 0x2000
END_BINDING();

// clang-format on

struct MeshDesc
{
	uint32_t displayFlags WITH_DEFAULT(0);
	uint64_t vertexPosAddress WITH_DEFAULT(0);      // Address of the Vertex buffer
	uint64_t vertexBinormalAddress WITH_DEFAULT(0); // Address of the Vertex buffer
	uint64_t vertexMorphAddress WITH_DEFAULT(0);    // Address of the Vertex buffer
	uint64_t vertexBlendAddress WITH_DEFAULT(0); // Address of the Vertex buffer
	uint64_t indexAddress WITH_DEFAULT(0);          // Address of the index buffer
	uint32_t materialId WITH_DEFAULT(0);       // Address of the material buffer
};

struct WireframeDesc
{
	uint64_t vertexAddress WITH_DEFAULT(0);      // Address of the Vertex buffer
	uint64_t indexAddress WITH_DEFAULT(0);          // Address of the index buffer
};

struct InstDesc
{
	vec3 color;
	uint32_t drawFlags WITH_DEFAULT(eStandardVisibility | eHasShadow);
	vec3 primaryColor;
	int textures WITH_DEFAULT(-1);
	vec3 secondaryColor;
	uint64_t vertexPosAddress WITH_DEFAULT(0);
	uint64_t vertexBinormalAddress WITH_DEFAULT(0);
	uint64_t indexAddress WITH_DEFAULT(0);          // Address of the index buffer
	uint32_t materialId WITH_DEFAULT(0);          // Address of the index buffer
	vec3 mapCoords;
	float morphWeight WITH_DEFAULT(0);
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
	uint32_t drawMask WITH_DEFAULT(eStandardVisibility);
	uint32_t highlightMask WITH_DEFAULT(eDisabledObject);
	uint32_t drawMaskHighlightPos WITH_DEFAULT(8);
	uint32_t lightingModelOffset WITH_DEFAULT(0);
	uint32_t highlightMaterialFlags WITH_DEFAULT(0);
	int8_t sliceAxisIndex WITH_DEFAULT(-1);
	float sliceAxis WITH_DEFAULT(0);
	float sliceAxisEpsilon WITH_DEFAULT(20);
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

	float morphWeight WITH_DEFAULT(0);
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

/*
 (34443):
        Diffuse       (20273, -14170): Can Have: true ; Can Exclude: true ; Always Has: false
        Specular      (   41, -34402): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        (   43, -34400): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride (    0, -34443): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      ( 6134, -28309): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         ( 2127, -32316): Can Have: true ; Can Exclude: true ; Always Has: false
        Anisotropic   (    0, -34443): Can Have: false; Can Exclude: true ; Always Has: false
MS2StandardMaterial (50325):
        Diffuse       (48823,  -1502): Can Have: true ; Can Exclude: true ; Always Has: false
        Specular      (  419, -49906): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        (  309, -50016): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride (    0, -50325): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      (19846, -30479): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         ( 5150, -45175): Can Have: true ; Can Exclude: true ; Always Has: false
        Anisotropic   (    0, -50325): Can Have: false; Can Exclude: true ; Always Has: false
MS2CharacterSkinMaterial (3191):
        Diffuse       ( 3009,   -182): Can Have: true ; Can Exclude: true ; Always Has: false
        Specular      ( 2773,   -418): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        ( 2585,   -606): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride ( 2549,   -642): Can Have: true ; Can Exclude: true ; Always Has: false
        Emissive      (   10,  -3181): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         (    0,  -3191): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,  -3191): Can Have: false; Can Exclude: true ; Always Has: false
MS2CharacterMaterial (15408):
        Diffuse       (15243,   -165): Can Have: true ; Can Exclude: true ; Always Has: false
        Specular      (12937,  -2471): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        (11307,  -4101): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride ( 6675,  -8733): Can Have: true ; Can Exclude: true ; Always Has: false
        Emissive      ( 1032, -14376): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         (   12, -15396): Can Have: true ; Can Exclude: true ; Always Has: false
        Anisotropic   (    0, -15408): Can Have: false; Can Exclude: true ; Always Has: false
MS2CharacterHairMaterial (1237):
        Diffuse       ( 1234,     -3): Can Have: true ; Can Exclude: true ; Always Has: false
        Specular      ( 1228,     -9): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        ( 1233,     -4): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride (  947,   -290): Can Have: true ; Can Exclude: true ; Always Has: false
        Emissive      (    5,  -1232): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         (    0,  -1237): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   ( 1197,    -40): Can Have: true ; Can Exclude: true ; Always Has: false
MS2GlassMaterial (348):
        Diffuse       (  348,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Specular      (  300,    -48): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        (   42,   -306): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride (    0,   -348): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      (   16,   -332): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         (    0,   -348): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,   -348): Can Have: false; Can Exclude: true ; Always Has: false
LightMapMaterial (1):
        Diffuse       (    1,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Specular      (    0,     -1): Can Have: false; Can Exclude: true ; Always Has: false
        Normal        (    0,     -1): Can Have: false; Can Exclude: true ; Always Has: false
        ColorOverride (    0,     -1): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      (    0,     -1): Can Have: false; Can Exclude: true ; Always Has: false
        Decal         (    0,     -1): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,     -1): Can Have: false; Can Exclude: true ; Always Has: false
EffectDissolve_HO (3):
        Diffuse       (    3,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Specular      (    0,     -3): Can Have: false; Can Exclude: true ; Always Has: false
        Normal        (    0,     -3): Can Have: false; Can Exclude: true ; Always Has: false
        ColorOverride (    0,     -3): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      (    0,     -3): Can Have: false; Can Exclude: true ; Always Has: false
        Decal         (    2,     -1): Can Have: true ; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,     -3): Can Have: false; Can Exclude: true ; Always Has: false
EffectUVDistortionMask_HO (400):
        Diffuse       (  400,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Specular      (    0,   -400): Can Have: false; Can Exclude: true ; Always Has: false
        Normal        (  395,     -5): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride (    0,   -400): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      (    6,   -394): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         (    0,   -400): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,   -400): Can Have: false; Can Exclude: true ; Always Has: false
EffectUVDistortionMaskGlow_HO (1907):
        Diffuse       ( 1907,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Specular      (   50,  -1857): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        ( 1907,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        ColorOverride (    0,  -1907): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      ( 1882,    -25): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         (    0,  -1907): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,  -1907): Can Have: false; Can Exclude: true ; Always Has: false
EffectUVDistortionMaskWrap_HO (1083):
        Diffuse       ( 1083,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Specular      (    0,  -1083): Can Have: false; Can Exclude: true ; Always Has: false
        Normal        ( 1080,     -3): Can Have: true ; Can Exclude: true ; Always Has: false
        ColorOverride (    0,  -1083): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      (   17,  -1066): Can Have: true ; Can Exclude: true ; Always Has: false
        Decal         (    0,  -1083): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,  -1083): Can Have: false; Can Exclude: true ; Always Has: false
EffectUVDistortionMaskGlowWrap_HO (4169):
        Diffuse       ( 4169,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Specular      (    1,  -4168): Can Have: true ; Can Exclude: true ; Always Has: false
        Normal        ( 4169,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        ColorOverride (    0,  -4169): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      ( 4169,     -0): Can Have: true ; Can Exclude: false; Always Has: true
        Decal         (    0,  -4169): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,  -4169): Can Have: false; Can Exclude: true ; Always Has: false
NiStandardMaterial (2):
        Diffuse       (    0,     -2): Can Have: false; Can Exclude: true ; Always Has: false
        Specular      (    0,     -2): Can Have: false; Can Exclude: true ; Always Has: false
        Normal        (    0,     -2): Can Have: false; Can Exclude: true ; Always Has: false
        ColorOverride (    0,     -2): Can Have: false; Can Exclude: true ; Always Has: false
        Emissive      (    0,     -2): Can Have: false; Can Exclude: true ; Always Has: false
        Decal         (    0,     -2): Can Have: false; Can Exclude: true ; Always Has: false
        Anisotropic   (    0,     -2): Can Have: false; Can Exclude: true ; Always Has: false
*/

#endif
