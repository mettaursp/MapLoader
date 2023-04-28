#extension GL_EXT_ray_tracing : require
#extension GL_EXT_scalar_block_layout : enable
#extension GL_EXT_nonuniform_qualifier : enable
#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require

#extension GL_EXT_buffer_reference2 : require

#include "raycommon.glsl"
#include "wavefront.glsl"

hitAttributeEXT vec2 attributes;

#ifdef PAYLOAD_0
layout(location = 0) rayPayloadInEXT hitPayload prd;
#elif defined(PAYLOAD_1)
layout(location = 1) rayPayloadEXT shadowHitPayload shadowPayload;
#endif

//layout(location = 0) rayPayloadEXT hitPayload prd;

layout(buffer_reference, scalar) buffer VertexPos {VertexPosBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexBinormal {VertexBinormalBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexMorph {VertexMorphBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer VertexBlend { VertexBlendBinding v[]; }; // Positions of an object
layout(buffer_reference, scalar) buffer Indices {ivec3 i[]; }; // Triangle indices
layout(set = 1, binding = eObjDescs, scalar) buffer ObjDesc_ { MeshDesc i[]; } objDesc;
layout(set = 1, binding = eInstDescs, scalar) buffer InstanceDescription_ { InstDesc i[]; } instDesc;
layout(set = 1, binding = eTextures) uniform sampler2D textureSamplers[];
layout(set = 1, binding = eTextureTransforms, scalar) buffer TextureTransform_ { TextureTransform i[]; } textureTransform;
layout(set = 1, binding = eGlobals) uniform _GlobalUniforms { GlobalUniforms uni; };
layout(set = 1, binding = eTextureOverrides, scalar) buffer MaterialTextures_ { MaterialTextures i[]; } texOverride;
layout(set = 1, binding = eMaterials, scalar) buffer Materials_ { WaveFrontMaterial m[]; } materials;

//layout(push_constant) uniform _PushConstantRay
//{
//	PushConstantRay pcRay;
//};

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

void main()
{
	// Object data
	InstDesc		instanceDesc = instDesc.i[gl_InstanceID];
	Indices		indices		 = Indices(instanceDesc.indexAddress);

	// Material of the object
	WaveFrontMaterial mat    = materials.m[instanceDesc.materialId];

//#ifdef IS_SHADOW_RAY
//	bool noShadows = (instanceDesc.drawFlags & 2) != 0;
//
//	if (noShadows)
//	{
//		ignoreIntersectionEXT;
//
//		return;
//	}
//#endif

	// Indices of the triangle
	ivec3 ind = indices.i[gl_PrimitiveID];

	const vec3 barycentrics = vec3(1.0 - attributes.x - attributes.y, attributes.x, attributes.y);

	VertexPos vertices = VertexPos(instanceDesc.vertexPosAddress);

	VertexPosBinding v0 = vertices.v[ind.x];
	VertexPosBinding v1 = vertices.v[ind.y];
	VertexPosBinding v2 = vertices.v[ind.z];

	float vertexAlpha      = v0.color.w * barycentrics.x + v1.color.w * barycentrics.y + v2.color.w * barycentrics.z;
	vertexAlpha /= 255;

	float alpha = mat.dissolve * vertexAlpha;
	int textureApply = getFlags(mat.textureModes, 3, 0);

	if (alpha < 1e-3f && textureApply != 0)
	{
		ignoreIntersectionEXT;

		return;
	}

	MaterialTextures textures = texOverride.i[instanceDesc.textures];

	//if (textures.diffuse.id < 0 && textures.decal.id < 0)
	//{
	//	if (!debugDrawObject)
	//		ignoreIntersectionEXT;
//
	//	return;
	//}

	vec2 texCoord = v0.texcoord * barycentrics.x + v1.texcoord * barycentrics.y + v2.texcoord * barycentrics.z;
//	vec3 nrm = cross(v1.position - v0.position, v2.position - v0.position);
//
//	const vec3 worldNrm = normalize(vec3(nrm * gl_WorldToObjectEXT));	// Transforming the normal to world space
//	
//	float normalDot = dot(worldNrm, gl_WorldRayDirectionEXT);
//
//#ifdef IS_SHADOW_RAY
//	if (normalDot < 0)
//	{
//		ignoreIntersectionEXT;
//
//		return;
//	}
//#else
//	if (normalDot > 0)
//	{
//		ignoreIntersectionEXT;
//
//		return;
//	}
//#endif

	return;

	float diffuseAlpha = 1;

	if (textures.diffuse.id >= 0)
	{
		diffuseAlpha = sampleTexture(textures.diffuse, texCoord).w;
	}

	float decalAlpha = 0;
	if (textures.decal.id >= 0)
	{
		decalAlpha = sampleTexture(textures.decal, texCoord).w;
	}

	if (max(diffuseAlpha, decalAlpha) == 0)
	{
		ignoreIntersectionEXT;

		return;
	}
}
