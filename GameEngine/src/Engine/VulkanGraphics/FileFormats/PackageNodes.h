#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <Engine/Math/Color3.h>
#include <Engine/Math/Vector2S.h>
#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Quaternion.h>

namespace Engine
{
	class Transform;

	namespace Graphics
	{
		class MeshFormat;
		class MeshData;
		class ShaderGroup;
		class Texture;
		class Material;

		struct ModelPackageNode
		{
			std::string Name;
			size_t AttachedTo = (size_t)-1;
			size_t MaterialIndex = (size_t)-1;
			size_t DataIndex = (size_t)-1;
			bool HasPhysXData = false;
			bool IsBone = false;
			bool IsInBoneList = false;
			bool IsVisible = true;
			std::shared_ptr<Engine::Graphics::MeshFormat> Format;
			std::shared_ptr<Engine::Graphics::MeshData> Mesh;
			std::shared_ptr<Engine::Transform> Transform;
			std::vector<size_t> Bones;
		};

		struct ModelPackageTextureTransform
		{
			bool Active = false;
			Vector2SF Translation;
			Vector2SF Scale;
			Vector2SF Pivot;
			float Rotation;
			int Mode;
			// 0: center * rotation * -center * translate * scale
			// 1: center * scale * rotation * translate * -center
			// 2: center * rotation * -center * flipV * translate * scale
		};

		struct ModelPackageMaterial
		{
			std::string Name;
			std::string ShaderName;
			std::string Diffuse;
			std::string Normal;
			std::string Specular;
			std::string OverrideColor;
			std::string Glow;
			std::string Decal;
			std::string Anisotropic;

			std::shared_ptr<Texture> DiffuseTexture;
			std::shared_ptr<Texture> NormalTexture;
			std::shared_ptr<Texture> SpecularTexture;
			std::shared_ptr<Texture> OverrideColorTexture;
			std::shared_ptr<Texture> GlowTexture;
			std::shared_ptr<Texture> DecalTexture;
			std::shared_ptr<Texture> AnisotropicTexture;

			ModelPackageTextureTransform DiffuseTransform;
			ModelPackageTextureTransform NormalTransform;
			ModelPackageTextureTransform SpecularTransform;
			ModelPackageTextureTransform OverrideColorTransform;
			ModelPackageTextureTransform GlowTransform;
			ModelPackageTextureTransform DecalTransform;
			ModelPackageTextureTransform AnisotropicTransform;

			std::shared_ptr<Material> Material;

			Color3 DiffuseColor = Color3(0.5f, 0.5f, 0.5f);
			Color3 SpecularColor = Color3(0.5f, 0.5f, 0.5f);
			Color3 AmbientColor = Color3(0.5f, 0.5f, 0.5f);
			Color3 OverrideColor0 = Color3(1.f, 0.f, 0.f);
			Color3 OverrideColor1 = Color3(0.f, 1.f, 0.f);
			Color3 OverrideColor2 = Color3(0.f, 0.f, 1.f);
			Color3 EmissiveColor;
			float Shininess = 10;
			float Alpha = 1;
			float FresnelBoost = 0;
			float FresnelExponent = 5;
			float ColorBoost = 1;
			// NiAlphaProperty
			unsigned char SourceBlendMode = 6;
			unsigned char DestBlendMode = 7;
			/*
			* 0000 |  0 | GL_ONE
			* 0001 |  1	| GL_ZERO
			* 0010 |  2	| GL_SRC_COLOR
			* 0011 |  3	| GL_ONE_MINUS_SRC_COLOR
			* 0100 |  4	| GL_DST_COLOR
			* 0101 |  5	| GL_ONE_MINUS_DST_COLOR
			* 0110 |  6	| GL_SRC_ALPHA
			* 0111 |  7	| GL_ONE_MINUS_SRC_ALPHA
			* 1000 |  8	| GL_DST_ALPHA
			* 1001 |  9	| GL_ONE_MINUS_DST_ALPHA
			* 1010 | 10 | GL_SRC_ALPHA_SATURATE
			*/
			unsigned char AlphaTestMode = 9;
			/*
			* 0 bit: enable
			* 0001 |  0 | GL_ALWAYS
			* 0011 |  3 | GL_LESS
			* 0101 |  5 | GL_EQUAL
			* 0111 |  7 | GL_LEQUAL
			* 1001 |  9 | GL_GREATER
			* 1011 | 11 | GL_NOTEQUAL
			* 1101 | 13 | GL_GEQUAL
			* 1111 | 15 | GL_NEVER
			*/
			unsigned char TestThreshold = 0;
			// NiTexturingProperty
			unsigned char TextureApplyMode = 0;
			/* (bits 1-2)
			* 0 | APPLY_REPLACE - Color = Texture; Alpha = TextureAlpha
			* 1 | APPLY_DECAL - Color = Texture * TextureAlpha + Vertex * (1 - TextureAlpha); Alpha = VertexAlpha
			* 2 | APPLY_MODULATE - Color = Texture * Vertex; Alpha = TextureAlpha * VertexAlpha
			*/
			// NiVertexColorProperty
			unsigned char LightingMode = 1;
			/* (bits 3)
			* 0 | LIGHTING_E - emissive
			* 1 | LIGHTING_E_A_D - emissive, diffuse, ambient
			*/
			unsigned char SourceVertexMode = 0;
			/* (bits 4-5)
			* 0 | SOURCE_IGNORE - ignore vertex, use material
			* 1 | SOURCE_EMISSIVE - use vertex color for emissive, others use material
			* 2 | SOURCE_AMB_DIFF - use vertex color for ambient & diffuse, emissive uses material
			*/

			std::shared_ptr<ShaderGroup> ShaderGroup;
		};

		enum class AnimationInterpolationType
		{
			None = 0,
			Linear = 1,
			Quadratic = 2,
			TensionBiasContinuity = 3,
			XyzRotation = 4,
			Const = 5,

			Count
		};

		enum class AnimationCycleType
		{
			Loop = 0,
			Reverse = 1,
			Clamp = 2
		};

		struct ModelPackageAnimationVectorKeyframe
		{
			static const bool HasQuadraticParams = true;

			Vector3SF Value;
			float Time = 0;
			bool NoChange = false;
			Vector3SF Params;
			Vector3SF Backward;
		};

		struct ModelPackageAnimationQuaternionKeyframe
		{
			static const bool HasQuadraticParams = false;

			Quaternion Value;
			float Time = 0;
			bool NoChange = false;
			Vector3SF Params;
		};

		struct ModelPackageAnimationFloatKeyframe
		{
			static const bool HasQuadraticParams = true;

			float Value = 0;
			float Time = 0;
			bool NoChange = false;
			Vector3SF Params;
		};

		struct ModelPackageAnimationFloatNode
		{
			AnimationInterpolationType Type = AnimationInterpolationType::None;
			std::vector<ModelPackageAnimationFloatKeyframe> Keyframes;
		};

		struct ModelPackageAnimationEulerAxisNode
		{
			AnimationInterpolationType Type = AnimationInterpolationType::None;
			std::vector<ModelPackageAnimationFloatKeyframe> Keyframes;
		};

		struct ModelPackageAnimationEulerNode
		{
			ModelPackageAnimationEulerAxisNode X;
			ModelPackageAnimationEulerAxisNode Y;
			ModelPackageAnimationEulerAxisNode Z;
		};

		struct ModelPackageAnimationVectorNode
		{
			AnimationInterpolationType Type = AnimationInterpolationType::None;
			std::vector<ModelPackageAnimationVectorKeyframe> Keyframes;
		};

		struct ModelPackageAnimationQuaternionNode
		{
			AnimationInterpolationType Type = AnimationInterpolationType::None;
			std::vector<ModelPackageAnimationQuaternionKeyframe> Keyframes;
		};

		template <typename SplinePointType>
		struct ModelPackageSpline
		{
			typedef SplinePointType PointType;
			static const size_t Dimension = sizeof(PointType) / sizeof(float);
			std::vector<PointType> ControlPoints;
			float Start = 0;
			float End = 0;
		};

		struct ModelPackageAnimationNode
		{
			std::string NodeName;
			bool IsSpline = false;
			ModelPackageAnimationQuaternionNode Rotation;
			ModelPackageAnimationVectorNode Translation;
			ModelPackageAnimationFloatNode Scale;
			ModelPackageAnimationEulerNode EulerRotation;
			ModelPackageSpline<Vector3SF> TranslationSpline;
			ModelPackageSpline<Quaternion> RotationSpline;
			ModelPackageSpline<float> ScaleSpline;
		};

		struct ModelPackageAnimationEvent
		{
			float Time = 0;
			std::string Name;
		};

		struct ModelPackageAnimation
		{
			std::string Name;
			std::string RootName;
			float Duration = 0;
			float PlaybackSpeed = 1;
			AnimationCycleType CycleType = AnimationCycleType::Clamp;
			std::vector<ModelPackageAnimationNode> Nodes;
			std::unordered_map<std::string, ModelPackageAnimationNode*> NodeMap;
			std::vector<ModelPackageAnimationEvent> Events;
		};

		struct ModelPhysXMesh
		{
			size_t DataIndex = (size_t)-1;
			size_t MaterialIndex = (size_t)-1;
			std::shared_ptr<Engine::Graphics::MeshFormat> Format;
			std::shared_ptr<Engine::Graphics::MeshData> Mesh;
			std::shared_ptr<Engine::Transform> Transform;
		};

		struct ModelPhysXActor
		{
			std::vector<ModelPhysXMesh> Meshes;
		};

		struct ModelPhysXProp
		{
			std::vector<ModelPhysXActor> Actors;
		};

		struct ModelPackage
		{
			std::vector<size_t> Bones;
			std::vector<ModelPackageNode> Nodes;
			std::vector<ModelPackageMaterial> Materials;
			std::vector<ModelPackageAnimation> Animations;
			std::vector<ModelPhysXProp> PhysXProps;
			bool HasEnabledPhysXMeshes = false;
		};
	}
}

namespace Enum
{
	typedef Engine::Graphics::AnimationInterpolationType AnimationInterpolationType;
	typedef Engine::Graphics::AnimationCycleType AnimationCycleType;
}