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

#version 460
#extension GL_EXT_ray_tracing : require
#extension GL_EXT_nonuniform_qualifier : enable
#extension GL_EXT_scalar_block_layout : enable
#extension GL_GOOGLE_include_directive : enable

#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
#extension GL_EXT_shader_16bit_storage : require
#extension GL_EXT_buffer_reference2 : require

#include "raycommon.glsl"
#include "wavefront.glsl"

hitAttributeEXT vec2 attributes;

// clang-format off
layout(location = 0) rayPayloadInEXT hitPayload prd;
layout(location = 1) rayPayloadEXT shadowHitPayload shadowPayload;

layout(buffer_reference, scalar) buffer VertexPos {VertexPosBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexBinormal {VertexBinormalBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexMorph {VertexMorphBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexBlend {VertexBlendBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer Indices {ivec3 i[]; }; // Triangle indices
layout(buffer_reference, scalar) buffer Materials {WaveFrontMaterial m[]; }; // Array of all materials on an object
layout(buffer_reference, scalar) buffer MatIndices {int i[]; }; // Material ID for each triangle
layout(set = 0, binding = eTlas) uniform accelerationStructureEXT topLevelAS;
layout(set = 1, binding = eGlobals) uniform _GlobalUniforms { GlobalUniforms uni; };
layout(set = 1, binding = eObjDescs, scalar) buffer ObjDesc_ { MeshDesc i[]; } objDesc;
layout(set = 1, binding = eTextures) uniform sampler2D textureSamplers[];
layout(set = 1, binding = eLights, scalar) buffer LightDesc_ { LightDesc i[]; } lightDesc;
layout(set = 1, binding = eTextureTransforms, scalar) buffer TextureTransform_ { TextureTransform i[]; } textureTransform;
layout(set = 1, binding = eInstDescs, scalar) buffer InstanceDescription_ { InstDesc i[]; } instDesc;
layout(set = 1, binding = eTextureOverrides, scalar) buffer MaterialTextures_ { MaterialTextures i[]; } texOverride;

layout(push_constant) uniform _PushConstantRay { PushConstantRay pcRay; };

layout(shaderRecordEXT) buffer SBTData {
    float material_id;
};
// clang-format on

vec3 reflectVector(vec3 vector, vec3 normal)
{
	return vector - 2 * dot(vector, normal) * normal;
}

vec2 getTextCoords(vec2 textureCoords, int transformId)
{
	if (transformId == -1)
		return textureCoords;

	TextureTransform transform = textureTransform.i[transformId];

    float sine = sin(transform.rotation);
	float cosine = cos(transform.rotation);
	mat2 rotation = mat2(2 * vec2(cosine, sine), vec2(-sine, cosine));

	if (transform.mode == 0)
	{
		return rotation * (transform.scale * textureCoords + transform.translation - transform.pivot) + transform.pivot;
	}

	if (transform.mode == 1)
	{
		return (rotation * (textureCoords - transform.pivot + transform.translation)) * transform.scale + transform.pivot;
	}

	// mode 2

	return rotation * (flipV(textureCoords * transform.scale + transform.translation) - transform.pivot) + transform.pivot;
}

vec4 sampleTexture(MaterialTexture inputTexture, vec2 texCoord)
{
	return textureLod(textureSamplers[nonuniformEXT(inputTexture.id)], getTextCoords(texCoord, inputTexture.transformId), 0);
}

int getId(int baseId, int overrideId)
{
	if (overrideId != -1) return overrideId;

	return baseId;
}

void main()
{
	// Object data
	InstDesc    instanceDesc = instDesc.i[gl_InstanceID];
	MeshDesc    objResource = objDesc.i[gl_InstanceCustomIndexEXT];
	MatIndices matIndices  = MatIndices(objResource.materialIndexAddress);
	Materials  materials   = Materials(objResource.materialAddress);
	Indices    indices     = Indices(objResource.indexAddress);


	prd.hitObject = gl_InstanceID;

	// Indices of the triangle
	ivec3 ind = indices.i[gl_PrimitiveID];

	VertexPos vertices = VertexPos(objResource.vertexPosAddress);

	// Vertex of the triangle
	VertexPosBinding v0 = vertices.v[ind.x];
	VertexPosBinding v1 = vertices.v[ind.y];
	VertexPosBinding v2 = vertices.v[ind.z];

	const vec3 barycentrics = vec3(1.0 - attributes.x - attributes.y, attributes.x, attributes.y);

	// Computing the coordinates of the hit position
	const vec3 pos      = v0.position * barycentrics.x + v1.position * barycentrics.y + v2.position * barycentrics.z;
	const vec3 worldPos = vec3(gl_ObjectToWorldEXT * vec4(pos, 1.0));  // Transforming the position to world space

	vec3 nrm = v0.normal * barycentrics.x + v1.normal * barycentrics.y + v2.normal * barycentrics.z;
	vec2 texCoord = v0.texcoord * barycentrics.x + v1.texcoord * barycentrics.y + v2.texcoord * barycentrics.z;

	// Computing the normal at hit position
	vec3 worldNrm = normalize(vec3(nrm * gl_WorldToObjectEXT));  // Transforming the normal to world space

	// Computing the normal at hit position
	vec4 vertexColor      = v0.color * barycentrics.x + v1.color * barycentrics.y + v2.color * barycentrics.z;
	vertexColor /= 255;

	// Material of the object
	int               matIdx = matIndices.i[gl_PrimitiveID];
	WaveFrontMaterial mat    = materials.m[matIdx];
	int texturesIndex = instanceDesc.textureOverride != -1 ? instanceDesc.textureOverride : mat.textures;
	MaterialTextures textures = texOverride.i[texturesIndex];

	int shaderType = mat.shaderType & 0xFFFF0000;
	shaderType = shaderType < 0 ? -1 : shaderType >> 16;

	bool debugDrawObject = (mat.shaderType & 0x1) != 0;
	bool invisibleObject = (instanceDesc.flags & 1) != 0;
	//if (mat.shaderType == eNone)
	//{ prd.hitValue = vec3(1, 0, 0); prd.rayLength = 0; return; }
	//if (shaderType == eMS2GlowMaterial)
	//{ prd.hitValue = vec3(1, 0, 1); prd.rayLength = 0; return; }

	bool drawInvisible = (uni.drawMode & 1) != 0;
	bool drawDebug = (uni.drawMode & 2) != 0;
	bool highlightDebug = (uni.drawMode & 4) != 0;
	
	if ((invisibleObject && !drawInvisible) || (debugDrawObject && !drawDebug))
	{
		prd.nextDirection = gl_WorldRayDirectionEXT;
		prd.nextOrigin = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
		prd.rayLength -= gl_HitTEXT;
	
		return;
	}

	if (debugDrawObject && highlightDebug)
	{
		 prd.hitValue = vec3(1, 0, 1);
		 prd.rayLength = 0;
		 return;
	}

	// Diffuse
	vec3 diffuseColor = mat.diffuse;
	vec3 specularColor = mat.specular;
	vec3 emissiveColor = mat.emission;
	float alpha = mat.dissolve * vertexColor.w;
	vec2 anisotropicColor = vec2(0, 0);

	int textureApply = getFlags(mat.textureModes, 3, 0);
	int sourceColorMode = getFlags(mat.textureModes, 3, 2);
	int lightingMode = getFlags(mat.textureModes, 1, 4);

	switch (sourceColorMode)
	{
	case 0: // SOURCE_IGNORE
		break;
	case 1: // SOURCE_EMISSIVE
		emissiveColor = vertexColor.xyz;
		break;
	case 2: // SOURCE_AMB_DIFF
		diffuseColor = vertexColor.xyz;
		specularColor = vertexColor.xyz;
	}

	diffuseColor = vertexColor.xyz;

	if (textures.emissive.id >= 0)
	{
		vec4 emissiveTextureColor = sampleTexture(textures.emissive, texCoord);
		emissiveColor = textureApplyColor(textureApply, emissiveTextureColor.xyz, emissiveColor, emissiveTextureColor.w);
	}

	if (lightingMode == 0)
	{
		prd.hitValue = prd.transmission * emissiveColor;
		prd.transmission *= (1 - alpha);
		prd.nextDirection = gl_WorldRayDirectionEXT;
		prd.nextOrigin = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
		prd.rayLength -= gl_HitTEXT;

		if (alpha == 1)
		{
			prd.rayLength = 0;
		}

		return;
	}

	float diffuseAlpha = 1;
	vec3 baseColor = diffuseColor;

	if(textures.diffuse.id >= 0)
	{
		vec4 diffuseTextureColor = sampleTexture(textures.diffuse, texCoord);

		diffuseColor = textureApplyColor(textureApply, diffuseTextureColor.xyz, diffuseColor, diffuseTextureColor.w);
		alpha *= textureApplyAlpha(textureApply, diffuseTextureColor.w, alpha);
	}

	if (textures.colorOverride.id >= 0)
	{
		vec4 controlColor = sampleTexture(textures.colorOverride, texCoord);

		vec3 dyeColor = (1 - controlColor.r) * instanceDesc.secondaryColor + controlColor.r * instanceDesc.primaryColor;
		diffuseColor = (1 - controlColor.w) * diffuseColor + controlColor.w * dyeColor * baseColor;
	}

	if(textures.decal.id >= 0)
	{
		vec4 decalTextureColor = sampleTexture(textures.decal, texCoord);
		
		diffuseColor = (1 - decalTextureColor.w) * diffuseColor + decalTextureColor.w * decalTextureColor.xyz;
		alpha *= textureApplyAlpha(textureApply, max(diffuseAlpha, decalTextureColor.w), alpha);
	}

	if (textures.specular.id >= 0)
	{
		vec4 specularTextureColor = sampleTexture(textures.specular, texCoord);
		specularColor = textureApplyColor(textureApply, specularTextureColor.xyz, specularColor, specularTextureColor.w);
	}

	vec3 binormal = vec3(0, 0, 0);
	vec3 tangent = vec3(0, 0, 0);
	vec3 worldBinormal = vec3(0, 0, 0);
	vec3 worldTangent = vec3(0, 0, 0);

	if (objResource.vertexBinormalAddress != 0 && (textures.anisotropic.id >= 0 || textures.normal.id >= 0))
	{
		VertexBinormal tbn = VertexBinormal(objResource.vertexBinormalAddress);

		VertexBinormalBinding v0tbn = tbn.v[ind.x];
		VertexBinormalBinding v1tbn = tbn.v[ind.y];
		VertexBinormalBinding v2tbn = tbn.v[ind.z];

		binormal = normalize(v0tbn.binormal * barycentrics.x + v1tbn.binormal * barycentrics.y + v2tbn.binormal * barycentrics.z);
		tangent = normalize(v0tbn.tangent * barycentrics.x + v1tbn.tangent * barycentrics.y + v2tbn.tangent * barycentrics.z);

		worldBinormal = normalize(vec3(binormal * gl_WorldToObjectEXT));
		worldTangent = normalize(vec3(tangent * gl_WorldToObjectEXT));
	}

	if (textures.anisotropic.id >= 0)
	{
		anisotropicColor = sampleTexture(textures.anisotropic, texCoord).xy * 2 - vec2(1, 1);
	}

	if (textures.normal.id >= 0)
	{
		vec4 normalTextureColor = sampleTexture(textures.normal, texCoord);

		if (false)
		{
			normalTextureColor.x = 2 * normalTextureColor.z - 1;
			normalTextureColor.y = 2 * normalTextureColor.y - 1;
			normalTextureColor.z = sqrt(1 - (normalTextureColor.x * normalTextureColor.x + normalTextureColor.y * normalTextureColor.y));
		}
		else
			normalTextureColor = vec4(2 * normalTextureColor.xyz - vec3(1, 1, 1), 0);
		
		nrm = normalize(mat3(tangent, binormal, nrm) * normalTextureColor.xyz);
		worldNrm = normalize(vec3(nrm * gl_WorldToObjectEXT));

		//{ prd.hitValue = worldNrm; prd.rayLength = 0; return; }
	}

	vec3 minTransmission = vec3(0, 0, 0);

	if (shaderType >= eMS2CharacterSkinMaterial && shaderType <= eMS2CharacterHairMaterial)
		minTransmission = vec3(0.5, 0.5, 0.5);

	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);
	vec3 ambient = vec3(0, 0, 0);

	bool hasSpecular = uni.lightingModel != eMS2Phong || textures.specular.id >= 0 || shaderType == eMS2GlassMaterial || shaderType == eMS2CharacterSkinMaterial || shaderType == eMS2CharacterMaterial;

	for (int i = 0; i < uni.lightCount; ++i)
	{
		LightDesc light = lightDesc.i[i];
		
		ambient += light.brightness * light.ambient;

		if (light.type == 2)
		{
			continue;
		}
		
		// Vector toward the light
		vec3  L;
		float lightIntensity = light.brightness;
		float lightDistance  = 100000.0;
		// Point light
		if(light.type == 0)
		{
			vec3 lDir      = light.position - worldPos;
			lightDistance  = length(lDir);
			lightIntensity *= 1 / (lightDistance * lightDistance);
			L              = normalize(lDir);
		}
		else  // Directional light
		{
			L = normalize(light.direction.xyz);
		}

		shadowPayload.isShadowed   = false;
		shadowPayload.transmission = vec3(1, 1, 1);

		// Tracing shadow ray only if the light is visible from the surface
		if(light.castsShadows && dot(worldNrm, L) > 0)
		{
			vec3  origin = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;// + worldNrm * 0.002;
			float tMin   = 0.005;
			float tMax   = lightDistance;
			vec3  rayDir = L;
			//uint  flags  = gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsOpaqueEXT | gl_RayFlagsSkipClosestHitShaderEXT;
			uint  flags  = gl_RayFlagsNoneEXT ;

			shadowPayload.rayLength = tMax;
			shadowPayload.nextOrigin = origin;
			shadowPayload.nextDirection = rayDir;
			const int maxShadowTransmissions = 10;

			for (int i = 0; i < maxShadowTransmissions; ++i)
			{
				traceRayEXT(topLevelAS,  // acceleration structure
									flags,       // rayFlags
									0xFF,        // cullMask
									1,           // sbtRecordOffset
									1,           // sbtRecordStride
									1,           // missIndex
									shadowPayload.nextOrigin,      // ray origin
									tMin,        // ray min range
									shadowPayload.nextDirection,      // ray direction
									shadowPayload.rayLength,        // ray max range
									1            // payload (location = 1)
				);

				shadowPayload.transmission = max(minTransmission, shadowPayload.transmission);

				if (shadowPayload.transmission.x <= minTransmission.x && shadowPayload.transmission.y <= minTransmission.y && shadowPayload.transmission.z <= minTransmission.z)
				{
					shadowPayload.isShadowed = true;

					break;
				}

				if (shadowPayload.rayLength <= tMin || shadowPayload.isShadowed)
					break;
			}

		}
		else
		{
			shadowPayload.isShadowed = light.castsShadows;
		}

		vec3 halfVector = normalize(L + -gl_WorldRayDirectionEXT);
		float lightDot = max(0, dot(halfVector, worldNrm));

		vec3 lightBoost = vec3(1, 1, 1);

		if (uni.lightingModel == eMS2Phong && shaderType == eMS2CharacterSkinMaterial)
		{
			vec3 sssColor = vec3(1, 0.2, 0.2);
			float sssPower = 1;
			float lightDotSaturated = max(0, min(1, lightDot));
			float subsurfaceScatter = max(0, min(1, (lightDot + sssPower) / (1 + sssPower)));
			subsurfaceScatter = (3 - 2 * subsurfaceScatter) * subsurfaceScatter * subsurfaceScatter;
			subsurfaceScatter -= (3 - 2 * lightDotSaturated) * lightDotSaturated * lightDotSaturated;
			subsurfaceScatter = max(0, subsurfaceScatter);

			lightBoost = subsurfaceScatter * sssColor + (1 - subsurfaceScatter) * vec3(1, 1, 1);
		}

		if(shadowPayload.isShadowed)
		{
			shadowPayload.transmission = minTransmission;

			if (uni.lightingModel != eMS2Phong)
				continue;
		}

		if (uni.lightingModel != eMS2Phong)
		{
			specular += shadowPayload.transmission * lightIntensity * pow(lightDot, mat.shininess) * light.specular;
		}
		else if (uni.lightingModel == eMS2Phong)
		{
			if (textures.specular.id >= 0 || shaderType == eMS2GlassMaterial)
			{
				float specularExponent = lightDot > 0 ? log2(lightDot) : -16.6096401;
				float specularPower = pow(2, specularExponent * mat.shininess);

				if (textures.anisotropic.id >= 0)
				{
					vec3 directionBias = normalize(anisotropicColor.x * worldTangent + anisotropicColor.y * worldBinormal);

					float biasDot = dot(halfVector, directionBias);
					biasDot = 1 - biasDot * biasDot;
					float binormalDot = dot(halfVector, worldBinormal);

					float biasExponent = lightDot > 0 ? log2(biasDot) : -16.6096401;
					float binormalExponent = binormalDot > 0 ? log2(binormalDot) : -16.6096401;

					specularPower = 0.5 * (pow(2, biasExponent * mat.shininess)) + pow(2, binormalExponent * mat.shininess);
				}
				
				specular += shadowPayload.transmission * specularPower * lightIntensity * light.specular;
			}
		}

		if (uni.lightingModel == eMS2Phong && mat.fresnelBoost > 0)
		{
			float fresnelDot = dot(worldNrm, -gl_WorldRayDirectionEXT);
			float fresnel = fresnelDot * lightDot * lightDot * mat.fresnelBoost * pow(1 - abs(fresnelDot), mat.fresnelExponent);
			vec3 lightColor = (1 - fresnel) * vec3(0, 0, 0) + fresnel * light.diffuse;
			
			diffuse += shadowPayload.transmission * lightBoost * lightIntensity * lightColor;
		}
		
		diffuse += shadowPayload.transmission * lightBoost * lightIntensity * max(0, dot(L, worldNrm)) * light.diffuse;
	}

	int srcMode = getFlags(mat.textureModes, 15, 5);
	int dstMode = getFlags(mat.textureModes, 15, 9);

	vec3 src = blendValue(srcMode, diffuse, vec3(1, 1, 1), alpha, 1);
	vec3 dst = blendValue(dstMode, diffuse, vec3(1, 1, 1), alpha, 1);

	vec3 contribution = vec3(0, 0, 0);

	switch (uni.lightingModel)
	{
		case ePhong:
			ambient *= mat.ambient;
			contribution = src * diffuseColor * (diffuse + ambient) + emissiveColor + specularColor * specular;

			break;
		case eMS2Phong:
			ambient *= mat.ambient;
			contribution = src * mat.colorBoost * diffuseColor * (diffuse + ambient + emissiveColor) + specularColor * specular;

			break;
	}

	prd.hitValue = prd.transmission * contribution;
	prd.transmission *= dst;
	prd.nextDirection = gl_WorldRayDirectionEXT;
	prd.nextOrigin = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
	prd.rayLength -= gl_HitTEXT;

	if (prd.transmission.x <= 0.01 && prd.transmission.y <= 0.01 && prd.transmission.z <= 0.01)
	{
		prd.rayLength = 0;
	}
}
