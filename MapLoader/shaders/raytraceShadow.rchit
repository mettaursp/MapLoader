
#version 460
#extension GL_EXT_ray_tracing : require
#extension GL_EXT_nonuniform_qualifier : enable
#extension GL_EXT_scalar_block_layout : enable
#extension GL_GOOGLE_include_directive : enable

#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
#extension GL_EXT_buffer_reference2 : require


hitAttributeEXT vec2 attributes;

#include "raycommon.glsl"
#include "wavefront.glsl"

// clang-format off
layout(location = 1) rayPayloadInEXT shadowHitPayload shadowPayload;

layout(buffer_reference, scalar) buffer VertexPos {VertexPosBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexBinormal {VertexBinormalBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexMorph {VertexMorphBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexBlend {VertexBlendBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer Indices {ivec3 i[]; }; // Triangle indices
layout(buffer_reference, scalar) buffer Materials {WaveFrontMaterial m[]; }; // Array of all materials on an object
layout(buffer_reference, scalar) buffer MatIndices {int i[]; }; // Material ID for each triangle
layout(set = 1, binding = eObjDescs, scalar) buffer ObjDesc_ { MeshDesc i[]; } objDesc;
layout(set = 1, binding = eTextures) uniform sampler2D textureSamplers[];
layout(set = 1, binding = eInstDescs, scalar) buffer InstanceDescription_ { InstDesc i[]; } instDesc;
layout(set = 1, binding = eTextureTransforms, scalar) buffer TextureTransform_ { TextureTransform i[]; } textureTransform;
layout(set = 1, binding = eTextureOverrides, scalar) buffer MaterialTextures_ { MaterialTextures i[]; } texOverride;


layout(push_constant) uniform _PushConstantRay { PushConstantRay pcRay; };
// clang-format on


vec2 getTextCoords(vec2 textureCoords, int transformId)
{
	if (transformId == -1)
		return textureCoords;

	TextureTransform transform = textureTransform.i[transformId];

    float sine = sin(transform.rotation);
	float cosine = cos(transform.rotation);
	mat2 rotation = mat2(vec2(cosine, sine), vec2(-sine, cosine));

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

void main()
{
	// Object data
	InstDesc    instanceDesc = instDesc.i[gl_InstanceID];
	MeshDesc    objResource = objDesc.i[gl_InstanceCustomIndexEXT];
	MatIndices matIndices  = MatIndices(objResource.materialIndexAddress);
	Materials  materials   = Materials(objResource.materialAddress);
	Indices    indices     = Indices(objResource.indexAddress);

	// Material of the object
	int               matIdx = matIndices.i[gl_PrimitiveID];
	WaveFrontMaterial mat    = materials.m[matIdx];
	int texturesIndex = instanceDesc.textureOverride != -1 ? instanceDesc.textureOverride : mat.textures;
	MaterialTextures textures = texOverride.i[texturesIndex];

	// Indices of the triangle
	ivec3 ind = indices.i[gl_PrimitiveID];

	const vec3 barycentrics = vec3(1.0 - attributes.x - attributes.y, attributes.x, attributes.y);

	VertexPos vertices = VertexPos(objResource.vertexPosAddress);

	VertexPosBinding v0 = vertices.v[ind.x];
	VertexPosBinding v1 = vertices.v[ind.y];
	VertexPosBinding v2 = vertices.v[ind.z];

	vec3 nrm = v0.normal * barycentrics.x + v1.normal * barycentrics.y + v2.normal * barycentrics.z;
	vec2 texCoord = v0.texcoord * barycentrics.x + v1.texcoord * barycentrics.y + v2.texcoord * barycentrics.z;

	const vec3 worldNrm = normalize(vec3(nrm * gl_WorldToObjectEXT));  // Transforming the normal to world space

	shadowPayload.nextOrigin = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;

	//if (dot(worldNrm, gl_WorldRayDirectionEXT) > 0)
	//{
	//	shadowPayload.rayLength -= gl_HitTEXT;
//
	//	return;
	//}

	// Computing the normal at hit position
	vec4 vertexColor      = v0.color * barycentrics.x + v1.color * barycentrics.y + v2.color * barycentrics.z;
	vertexColor /= 255;
	
	int textureApply = getFlags(mat.textureModes, 3, 0);
	int sourceColorMode = getFlags(mat.textureModes, 3, 2);

	float alpha = mat.dissolve * vertexColor.w;
	vec3 diffuseColor = mat.diffuse;

	switch (sourceColorMode)
	{
	case 0: // SOURCE_IGNORE
		break;
	case 1: // SOURCE_EMISSIVE
		break;
	case 2: // SOURCE_AMB_DIFF
		diffuseColor = vertexColor.xyz;
	}

	if(textures.diffuse.id >= 0)
	{
		vec4 diffuseTextureColor = textureLod(textureSamplers[nonuniformEXT(textures.diffuse.id)], getTextCoords(texCoord, textures.diffuse.transformId), 1);

		diffuseColor = textureApplyColor(textureApply, diffuseTextureColor.xyz, diffuseColor, diffuseTextureColor.w);
		alpha = textureApplyAlpha(textureApply, diffuseTextureColor.w, alpha);
	}

	int srcMode = getFlags(mat.textureModes, 15, 5);
	int dstMode = getFlags(mat.textureModes, 15, 9);

	vec3 src = blendValue(srcMode, diffuseColor, vec3(1, 1, 1), alpha * alpha, 1);
	vec3 dst = blendValue(dstMode, diffuseColor, vec3(1, 1, 1), alpha * alpha, 1);

	//if (alpha >= 0.999)
	//if (dst.x <= 0.01 && dst.y <= 0.01 && dst.z <= 0.01)//(alpha == 1)
	//{
	//	shadowPayload.isShadowed = true;
	//	shadowPayload.rayLength = 0;
//
	//	return;
	//}

	vec3 shadowColor = vec3(1, 1, 1) - diffuseColor;
	shadowColor *= shadowColor;
	shadowColor = vec3(1, 1, 1) - shadowColor;
	shadowPayload.transmission *= dst * (dst + src * shadowColor);
	shadowPayload.rayLength -= gl_HitTEXT;

	//shadowPayload.transmission = vec3(1, 1, 1);
	//shadowPayload.rayLength = 0;
	//shadowPayload.isShadowed = false;
}
