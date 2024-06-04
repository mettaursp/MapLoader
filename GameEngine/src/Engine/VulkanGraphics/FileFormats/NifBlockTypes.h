#pragma once

#include <vector>
#include <string>
#include <memory>
#include <limits>

#include <Engine/Assets/ParserUtils.h>
#include <Engine/Math/Vector2S.h>
#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Color4.h>
#include <Engine/Math/Color3.h>
#include <Engine/Math/Quaternion.h>
#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include "NifComponentInfo.h"

struct BlockData;
struct NifDocument;

struct NiDataBlock
{
	unsigned int BlockIndex = 0;
	NifDocument* Document = nullptr;

	virtual ~NiDataBlock() {}

	BlockData* Get();

	template <typename T>
	T* Cast()
	{
		return reinterpret_cast<T*>(this);
	}

	template <typename T>
	T* Cast() const
	{
		return reinterpret_cast<const T*>(this);
	}
};

struct BlockData
{
	std::string BlockType;
	std::string BlockName;
	NifDocument* Document = nullptr;
	unsigned int BlockIndex = 0;
	unsigned int BlockSize = 0;
	std::unique_ptr<NiDataBlock> Data = nullptr;
	unsigned int BlockStart = 0;

	template <typename T, typename... Arguments>
	T* AddData(const Arguments&... arguments)
	{
		std::unique_ptr<T> data = std::make_unique<T>(arguments...);
	
		data->BlockIndex = BlockIndex;
		data->Document = Document;
	
		T* pointer = data.get();
	
		Data = std::move(data);
		
		return pointer;
	}

	template <typename T, typename... Arguments>
	T* MakeType(const Arguments&... arguments)
	{
		T* data = AddData<T>(arguments...);

		BlockType = T::BlockTypeName;

		return data;
	}

	template <typename T>
	T* GetData()
	{
		return reinterpret_cast<T*>(Data.get());
	}

	template <typename T>
	const T* GetData() const
	{
		return reinterpret_cast<const T*>(Data.get());
	}
};

template <typename T>
struct NiRef
{
	const BlockData* Block = nullptr;

	NiRef(const BlockData* block = nullptr)
	{
		*this = block;
	}

	NiRef(const NiRef<T>& ref)
	{
		Block = ref.Block;
	}

	NiRef(NiRef<T>&& ref)
	{
		Block = ref.Block;

		ref.Block = nullptr;
	}

	T* operator->() {
		return reinterpret_cast<T*>(Block->Data.get());
	}

	const T* operator->() const {
		return reinterpret_cast<const T*>(Block->Data.get());
	}

	T& operator*() {
		return *reinterpret_cast<T*>(Block->Data.get());
	}

	const T& operator*() const {
		return *reinterpret_cast<const T*>(Block->Data.get());
	}

	// throws std::bad_cast
	NiRef<T>& operator=(const BlockData* block)
	{
		if (Block == nullptr || dynamic_cast<T*>(block->Data.get()) != nullptr)
		{
			Block = block;
		}

		return *this;
	}

	NiRef<T>& operator=(std::nullptr_t)
	{
		Block = nullptr;

		return *this;
	}

	NiRef<T>& operator=(const NiRef<T>& ref)
	{
		Block = ref.Block;

		return *this;
	}

	template <typename T2>
	NiRef<T>& operator=(const NiRef<T2>& ref)
	{
		static_assert(std::is_base_of<T, T2>::value, "NiRef: Derived not derived from BaseClass");

		Block = ref.Block;

		return *this;
	}

	NiRef<T>& operator=(NiRef<T>&& ref)
	{
		Block = ref.Block;

		ref.Block = nullptr;

		return *this;
	}

	bool operator==(const BlockData* block) const
	{
		return Block == block;
	}

	bool operator==(std::nullptr_t) const
	{
		return Block == nullptr;
	}

	bool operator==(const NiRef<T>& ref) const
	{
		return Block == ref.Block;
	}

	bool operator==(const T* data) const
	{
		if (Block == nullptr)
		{
			return data == nullptr;
		}

		return Block->Data.get() == data;
	}

	operator T* ()
	{
		return &**this;
	}

	operator T* () const
	{
		return &**this;
	}
};

struct MeshPrimitiveTypeEnum
{
	enum MeshPrimitiveType
	{
		Triangles,
		TriStrips,
		Lines,
		LineStrips,
		Quads,
		Points
	};
};

typedef MeshPrimitiveTypeEnum::MeshPrimitiveType MeshPrimitiveType;

struct CloningBehaviorEnum
{
	enum CloningBehavior
	{
		Share,
		Copy,
		BlankCopy
	};
};

typedef CloningBehaviorEnum::CloningBehavior CloningBehavior;

struct NiTransform
{
	Vector3SF Translation;
	Matrix4F Rotation;
	float Scale = 1;
};

struct NiNodeType : public NiDataBlock
{
	std::vector<const BlockData*> ExtraData;
	const BlockData* Controller = nullptr;
	unsigned short Flags = 0;
	NiTransform Transformation;
	std::vector<const BlockData*> Properties;
	const BlockData* CollisionObject = nullptr;
};

struct NiNode : public NiNodeType
{
	static inline const std::string BlockTypeName = "NiNode";

	std::vector<const BlockData*> Children;
	std::vector<const BlockData*> Effects;
};

struct NiBounds
{
	Vector3SF Center;
	float Radius = 1;
};

struct NiMesh : public NiNodeType
{
	static inline const std::string BlockTypeName = "NiMesh";

	struct Semantics
	{
		std::string Name;
		unsigned int Index = 0;
	};

	struct DataStreams
	{
		const BlockData* Stream = nullptr;
		bool IsPerInstance = false;
		std::vector<unsigned short> SubmeshToRegionMap;
		std::vector<Semantics> ComponentSemantics;
	};

	std::vector<std::string> Materials;
	std::vector<const BlockData*> MaterialExtraData;
	unsigned int ActiveMaterial = 0;
	bool MaterialNeedsUpdate = false;
	MeshPrimitiveType PrimitiveType;
	unsigned short NumSubmeshes = 0;
	bool InstancingEnabled = false;
	NiBounds Bounds;
	std::vector<DataStreams> Streams;
	std::vector<const BlockData*> Modifiers;
};

struct NiMorphMeshModifier : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiMorphMeshModifier";

	struct ElementData
	{
		NiMesh::Semantics Semantic;
		unsigned int NormalizeFlag = 0;
	};

	std::vector<unsigned short> SubmitPoints;
	std::vector<unsigned short> CompletePoints;
	unsigned char Flags = 0;
	unsigned short NumTargets = 0;
	std::vector<ElementData> Elements;
};

struct NiMorphWeightsController : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiMorphWeightsController";

	const BlockData* NextController = nullptr;
	unsigned short Flags = 0;
	float Frequency = 1;
	float Phase = 0;
	float StartTime = 0;
	float StopTime = 1e-5f;
	const BlockData* Target = nullptr;
	unsigned int Count = 0;
	std::vector<const BlockData*> Interpolators;
	std::vector<std::string> TargetNames;
};

struct NiSkinningMeshModifier : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiSkinningMeshModifier";

	struct ElementData
	{
		NiMesh::Semantics Semantic;
		unsigned int NormalizeFlag = 0;
	};

	std::vector<unsigned short> SubmitPoints;
	std::vector<unsigned short> CompletePoints;
	unsigned short Flags = 0;
	const BlockData* SkeletonRoot = nullptr;
	NiTransform SkeletonTransformation;
	std::vector<const BlockData*> Bones;
	std::vector<NiTransform> BoneTransforms;
	std::vector<NiBounds> BoneBounds;
};

struct NiFloatInterpolator : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiFloatInterpolator";

	float Value = std::numeric_limits<float>::min();
	const BlockData* Data = nullptr;
};

struct NiFloatData : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiFloatData";

	struct Key
	{
		float Time = 0;
		float Value = 0;
	};

	unsigned int Interpolation = 0;

	std::vector<Key> Keys;
};

struct NiMaterialProperty : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiMaterialProperty";

	std::vector<const BlockData*> ExtraData;
	const BlockData* Controller = nullptr;
	Color3 AmbientColor = Color3(0.7f, 0.7f, 0.7f);
	Color3 DiffuseColor = Color3(0.7f, 0.7f, 0.7f);
	Color3 SpecularColor = Color3(1.f, 1.f, 1.f);
	Color3 EmissiveColor = Color3(0.f, 0.f, 0.f);
	float Glossiness = 10;
	float Alpha = 1;
	float FresnelBoost = 1;
	float FresnelExponent = 1;
};

struct NiTexturingProperty : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiTexturingProperty";

	struct TextureData
	{
		bool HasThisTexture = false;
		const BlockData* Source = nullptr;
		unsigned short Flags = 0;
		unsigned short MaxAnisotropy = 1;
		bool HasTextureTransform = false;
		Vector2SF Translation;
		Vector2SF Scale = Vector2SF(1, 1);
		float Rotation = 0;
		unsigned int TransformMethod = 0;
		Vector2SF Center = Vector2SF(0.5f, 0.5f);
	};

	struct ShaderTextureData
	{
		TextureData Map;
		unsigned int MapId = 0;
	};

	std::vector<const BlockData*> ExtraData;
	const BlockData* Controller = nullptr;
	unsigned short Flags = 0;
	unsigned int TextureCount = 0;
	TextureData BaseTexture;
	TextureData DarkTexture;
	TextureData DetailTexture;
	TextureData GlossTexture;
	TextureData GlowTexture;
	TextureData BumpTexture;
	float BumpMapLumaScale = 1;
	float BumpMapLumaOffset = 0;
	Vector2SF BumpMapRight;
	Vector2SF BumpMapUp;
	TextureData NormalTexture;
	TextureData ParallaxTexture;
	TextureData Decal0Texture;
	std::vector<ShaderTextureData> ShaderTextures;
};

struct NiSourceTexture : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiSourceTexture";

	std::vector<const BlockData*> ExtraData;
	const BlockData* Controller = nullptr;
	unsigned char UseExternal = 1;
	std::string FileName;
	const BlockData* PixelData = nullptr;
	unsigned int PixelLayout = 0;
	unsigned int UseMipmaps = 0;
	unsigned int AlphaFormat = 0;
	unsigned char IsStatic = 1;
	bool DirectRender = false;
	bool PersistRenderData = false;
};

struct NiExtraData : public NiDataBlock
{

};

template <typename T>
struct NiExtraDataImpl : public NiExtraData
{
	T Value;
};

struct NiFloatExtraData : public NiExtraDataImpl<float>
{
	typedef float ValueType;

	static inline const std::string BlockTypeName = "NiFloatExtraData";
};

struct NiColorExtraData : public NiExtraDataImpl<Color4>
{
	typedef Color4 ValueType;

	static inline const std::string BlockTypeName = "NiColorExtraData";
};

struct NiIntegerExtraData : public NiExtraDataImpl<unsigned int>
{
	typedef unsigned int ValueType;

	static inline const std::string BlockTypeName = "NiIntegerExtraData";
};

struct NiProperty : public NiDataBlock
{
	std::vector<const BlockData*> ExtraData;
	const BlockData* Controller = nullptr;
	unsigned short Flags = 0;
};

struct NiVertexColorProperty : public NiProperty
{
	static inline const std::string BlockTypeName = "NiVertexColorProperty";
};

struct NiZBufferProperty : public NiProperty
{
	static inline const std::string BlockTypeName = "NiZBufferProperty";
};

struct NiSpecularProperty : public NiProperty
{
	static inline const std::string BlockTypeName = "NiSpecularProperty";
};

struct NiAlphaProperty : public NiProperty
{
	static inline const std::string BlockTypeName = "NiAlphaProperty";

	unsigned char Threshold = 0;
};

struct StreamUsageEnum
{
	enum StreamUsage
	{
		IndexBuffer,
		VertexBuffer,
		ShaderConstant,
		User
	};
};

typedef StreamUsageEnum::StreamUsage StreamUsage;

struct NiDataStream : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiDataStream";

	struct Region
	{
		unsigned int StartIndex = 0;
		unsigned int NumIndices = 0;
	};

	unsigned int StreamSize = 0;
	CloningBehavior CloningBehavior;
	std::vector<Region> Regions;
	std::vector<ComponentFormat> ComponentFormats;
	std::vector<char> StreamData;
	StreamUsage Usage;
	bool Streamable = false;
	std::vector<Engine::Graphics::VertexAttributeFormat> Attributes;
};

struct NiPhysXPropDesc;

struct NiPhysXProp : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiPhysXProp";

	std::vector<NiRef<NiExtraData>> ExtraData; // NiExtraData
	const BlockData* Controller = nullptr; // NiTimeController
	float PhysXToWorldScale = 1;
	std::vector<const BlockData*> Sources; // NiPhysXSrc
	std::vector<const BlockData*> Dests; // NiPhysXDest
	std::vector<NiRef<NiMesh>> ModifiedMeshes; // NiMesh
	bool KeepMeshes = false;
	NiRef<NiPhysXPropDesc> Snapshot; // NiPhysXPropDesc
};

struct NiPhysXActorDesc;

struct NiPhysXPropDesc : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiPhysXPropDesc";

	struct StateString
	{
		std::string String;
		unsigned int Value;
	};

	struct State
	{
		std::vector<StateString> Strings;
	};

	std::vector<NiRef<NiPhysXActorDesc>> Actors; // NiPhysXActorDesc
	std::vector<const BlockData*> Joints; // NiPhysXJointDesc
	std::vector<const BlockData*> Clothes; // NiPhysXClothDesc
	std::unordered_map<unsigned short, const BlockData*> Materials;
	std::vector<State> StateNames;
	unsigned char Flags = 0;
};

struct NxActorFlagEnum
{
	enum NxActorFlag : unsigned int
	{
		None,
		DisableCollision = 1 << 0,
		DisableResponse = 1 << 1,
		LockCenterOfMass = 1 << 2,
		FluidDisableCollision = 1 << 3,
		ContactModification = 1 << 4,
		ForceConeFriction = 1 << 5,
		UserActorPairFiltering = 1 << 6
	};
};

typedef NxActorFlagEnum::NxActorFlag NxActorFlag;

struct NiPhysXShapeDesc;

struct NiPhysXActorDesc : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiPhysXActorDesc";

	std::string ActorName;
	std::vector<Matrix4F> Poses;
	const BlockData* BodyDesc = nullptr; //NiPhysXBodyDesc
	float Density = 1;
	NxActorFlag ActorFlags = NxActorFlag::None;
	unsigned short ActorGroup = 0;
	unsigned short DominanceGroup = 0;
	unsigned int ContactReportFlags = 0;
	unsigned short ForceFieldMaterial = 0;
	std::vector<NiRef<NiPhysXShapeDesc>> ShapeDescriptions;
	NiRef<NiPhysXActorDesc> ActorParent;
	const BlockData* Source = nullptr; // NiPhysXRigidBodySrc
	const BlockData* Dest = nullptr; // NiPhysXRigidBodyDest
};

struct NxShapeTypeEnum
{
	enum NxShapeType : unsigned int
	{
		Plane,
		Sphere,
		Box,
		Capsule,
		Wheel,
		Convex,
		Mesh,
		HeightField,
		RawMesh,
		Compound
	};
};

typedef NxShapeTypeEnum::NxShapeType NxShapeType;

struct NxShapeFlagEnum
{
	enum NxShapeFlag : unsigned int
	{
		Visualization = 1 << 3,
		DisableCollision = 1 << 4,
		FeatureIndices = 1 << 5,
		DisableRaycasting = 1 << 6,
		PointContactForce = 1 << 7,
		FluidDrain = 1 << 8,
		FluidDisableCollision = 1 << 10,
		FluidTwoWay = 1 << 11,
		DisableResponse = 1 << 12,
		DynamicDynamicCCD = 1 << 13,
		DisableSceneQueries = 1 << 14,
		ClothDrain = 1 << 15,
		ClothDisableCollision = 1 << 16,
		ClothTwoWay = 1 << 17,
		SoftBodyDrain = 1 << 18,
		SoftBodyDisableCollision = 1 << 19,
		SoftBodyTwoWay = 1 << 20
	};
};

typedef NxShapeFlagEnum::NxShapeFlag NxShapeFlag;

constexpr NxShapeFlag operator|(NxShapeFlag left, NxShapeFlag right)
{
	return NxShapeFlag((unsigned int)left | (unsigned int)right);
}

struct NiPhysXMeshDesc;

struct NiPhysXShapeDesc : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiPhysXShapeDesc";

	NxShapeType ShapeType = NxShapeType::Plane;
	NxShapeFlag Flags = NxShapeFlag::Visualization | NxShapeFlag::ClothTwoWay | NxShapeFlag::SoftBodyTwoWay;
	Matrix4F LocalPose;
	unsigned short CollisionGroup = 0;
	unsigned short MaterialIndex = 0;
	float Density = 1;
	float Mass = 1;
	float SkinWidth = 0.01f;
	std::string ShapeName;
	unsigned int NonInteractingCompartment = 0;
	unsigned int CollisionBits[4] = { 0 };
	NiRef<NiPhysXMeshDesc> Mesh;
};

struct NxMeshShapeFlagsEnum
{
	enum NxMeshShapeFlags : unsigned int
	{
		None = 0,
		SmoothSphereCollisions = 1 << 0,
		DoubleSided = 1 << 1
	};
};

typedef NxMeshShapeFlagsEnum::NxMeshShapeFlags NxMeshShapeFlags;

struct NxPagingModeEnum
{
	enum NxPagingMode : unsigned int
	{
		Manual,
		Fallback,
		Auto
	};
};

typedef NxPagingModeEnum::NxPagingMode NxPagingMode;

struct PhysXMeshFlagsEnum
{
	enum PhysXMeshFlags : unsigned char
	{
		None = 0,
		IsConvex = 0x1,
		IsCloth = 0x2,
		Hardware = 0x4,
		CookedForWin32 = 0x8,
		CookedForPS3 = 0x10,
		CookedForXenon = 0x20
	};
};

typedef PhysXMeshFlagsEnum::PhysXMeshFlags PhysXMeshFlags;

struct NxsMeshTypeEnum
{
	enum class NxsMeshType
	{
		None,
		Convex,
		Triangle,
		Cloth
	};
};

typedef NxsMeshTypeEnum::NxsMeshType NxsMeshType;

struct NxsFace
{
	unsigned char Vert1 = 0;
	unsigned char Vert2 = 0;
	unsigned char Vert3 = 0;
};

struct NxsMesh
{
	NxsMeshType Type = NxsMeshType::None;
	std::vector<Vector3SF> Vertices;
	std::vector<NxsFace> Faces;
};

struct NiPhysXMeshDesc : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiPhysXMeshDesc";

	std::string MeshName;
	std::vector<unsigned char> MeshData;
	NxsMesh Mesh;
	NxMeshShapeFlags MeshFlags = NxMeshShapeFlags::None;
	NxPagingMode PagingMode = NxPagingMode::Manual;
	PhysXMeshFlags Flags = PhysXMeshFlags::None;
};

struct CycleTypeEnum
{
	enum CycleType
	{
		CycleLoop,
		CycleReverse,
		CycleClamp
	};
};

typedef CycleTypeEnum::CycleType CycleType;

struct AccumFlagsEnum
{
	enum AccumFlags
	{
		AccumXTrans = 1,
		AccumYTrans = 2,
		AccumZTrans = 4,
		AccumXRot = 8,
		AccumYRot = 16,
		AccumZRot = 32,
		AccumXFront = 64,
		AccumYFront = 128,
		AccumZFront = 256,
		AccumNegFront = 512
	};
};

typedef AccumFlagsEnum::AccumFlags AccumFlags;

struct NiSequenceData : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiSequenceData";

	std::vector<const BlockData*> Evaluators;
	const BlockData* TextKeys = nullptr;
	float Duration = 0;
	CycleType CycleType;
	float Frequency = 0;
	std::string AccumRootName;
	AccumFlags AccumFlags;
};

struct ChannelTypeEnum
{
	enum ChannelType
	{
		Invalid,
		Color,
		Bool,
		Float,
		Vector3,
		Quaternion
	};
};

typedef ChannelTypeEnum::ChannelType ChannelType;

struct ChannelTypeFlagsEnum
{
	enum ChannelTypeFlags
	{
		Referenced = 1,
		Transform = 2,
		AlwaysUpdate = 4,
		Shutdown = 8
	};
};

typedef ChannelTypeFlagsEnum::ChannelTypeFlags ChannelTypeFlags;

struct NiEvaluator : public NiDataBlock
{
	std::string NodeName;
	std::string PropertyType;
	std::string ControllerType;
	std::string ControllerId;
	std::string InterpolatorId;
	bool PositionPosed;
	ChannelType PositionChannel;
	bool RotationPosed;
	ChannelType RotationChannel;
	bool ScalePosed;
	ChannelType ScaleChannel;
	ChannelTypeFlags ChannelFlags;
};

struct NiBSplineCompTransformEvaluator : public NiEvaluator
{
	static inline const std::string BlockTypeName = "NiBSplineCompTransformEvaluator";

	float StartTime = 0;
	float EndTime = 0;
	const BlockData* Data = nullptr;
	const BlockData* BasisData = nullptr;
	NiTransform Transform;
	unsigned int TranslationHandle = 0;
	unsigned int RotationHandle = 0;
	unsigned int ScaleHandle = 0;
	float TranslationOffset = 0;
	float TranslationHalfRange = 0;
	float RotationOffset = 0;
	float RotationHalfRange = 0;
	float ScaleOffset = 0;
	float ScaleHalfRange = 0;
};

struct NiBSplineData : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiBSpineData";

	std::vector<float> FloatControlPoints;
	std::vector<short> CompactControlPoints;
};

struct NiBSplineBasisData : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiBSplineBasisData";

	unsigned int NumControlPoints = 0;
};

struct NiTransformEvaluator : public NiEvaluator
{
	static inline const std::string BlockTypeName = "NiTransformEvaluator";

	NiTransform Value;
	const BlockData* Data = nullptr;
};

struct RotationTypeEnum
{
	enum RotationType
	{
		None,
		LinearKey = 1,
		QuadraticKey = 2, // quadratic interpolation, forward n back tangents stored
		TbcKey = 3, // tension bias continuity interolation
		XyzRotationKey = 4, // rotation, seperate x, y, z keys instead of quaternions
		ConstKey = 5, // step function
	};
};

typedef RotationTypeEnum::RotationType RotationType;

struct NifDocument;

template <typename KeyType>
KeyType ParseKey(NifDocument* document, std::string_view& stream);

template <>
float ParseKey<float>(NifDocument* document, std::string_view& stream);

template <>
Quaternion ParseKey<Quaternion>(NifDocument* document, std::string_view& stream);

template <>
Vector3SF ParseKey<Vector3SF>(NifDocument* document, std::string_view& stream);

template <typename KeyType>
struct LinearKey
{
	static const RotationType Type = RotationType::LinearKey;

	float Time;
	KeyType Value;

	void Parse(NifDocument* document, std::string_view& stream);
};

template <typename KeyType>
struct QuadraticKey
{
	static const RotationType Type = RotationType::QuadraticKey;

	float Time;
	KeyType Value;
	KeyType Forward;
	KeyType Backward;

	void Parse(NifDocument* document, std::string_view& stream);
};

template <typename KeyType>
struct TbcKey
{
	static const RotationType Type = RotationType::TbcKey;

	float Time;
	KeyType Value;
	float Tension;
	float Bias;
	float Continuity;

	void Parse(NifDocument* document, std::string_view& stream);
};

template <typename KeyType>
struct Keys
{
	RotationType Interpolation;
	std::vector<KeyType> KeysValues;

	void Parse(NifDocument* document, std::string_view& stream);
};

template <typename AnyKeyType>
struct AnyKeysNoRotate
{
	typedef AnyKeyType KeyType;

	RotationType Interpolation;
	size_t KeyCount = 0;
	std::vector<LinearKey<KeyType>> LinearKeys;
	std::vector<QuadraticKey<KeyType>> QuadraticKeys;
	std::vector<TbcKey<KeyType>> TbcKeys;

	template <typename KeyContainer>
	void ParseKeyVector(NifDocument* document, std::string_view& stream, KeyContainer& container, unsigned int keys);
	void Parse(NifDocument* document, std::string_view& stream);
};

struct XyzKeys
{
	typedef float KeyType;

	static const RotationType Type = RotationType::XyzRotationKey;

	AnyKeysNoRotate<float> KeysX;
	AnyKeysNoRotate<float> KeysY;
	AnyKeysNoRotate<float> KeysZ;

	void Parse(NifDocument* document, std::string_view& stream)
	{
		KeysX.Parse(document, stream);
		KeysY.Parse(document, stream);
		KeysZ.Parse(document, stream);
	}
};

template <typename AnyKeyType>
struct AnyKeys
{
	typedef AnyKeyType KeyType;

	RotationType Interpolation = RotationType::None;
	size_t KeyCount = 0;
	std::vector<LinearKey<KeyType>> LinearKeys;
	std::vector<QuadraticKey<KeyType>> QuadraticKeys;
	std::vector<TbcKey<KeyType>> TbcKeys;
	std::vector<XyzKeys> XyzKeys;

	template <typename KeyContainer>
	void ParseKeyVector(NifDocument* document, std::string_view& stream, KeyContainer& container, unsigned int keys);
	void Parse(NifDocument* document, std::string_view& stream);
};

struct NiTransformData : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiTransformData";

	AnyKeys<Quaternion> RotationKeys;
	AnyKeys<Vector3SF> TranslationKeys;
	AnyKeys<float> ScaleKeys;
};

struct TextKey
{
	float Time = 0;
	std::string Value;
};

struct NiTextKeyExtraData : public NiDataBlock
{
	static inline const std::string BlockTypeName = "NiTextKeyExtraData";

	std::vector<TextKey> TextKeys;
};

struct NifDocument
{
	typedef void (NifDocument::* BlockParseFunction)(std::string_view& stream, BlockData& block);
	typedef void (NifDocument::* BlockWriteFunction)(std::ostream& stream, BlockData& block);

	std::vector<std::string> BlockTypes;
	std::vector<unsigned short> BlockTypeIndices;
	std::vector<unsigned int> BlockSizes;
	std::vector<std::string> Strings;
	std::vector<BlockData> Blocks;
	std::map<unsigned short, BlockData> BlockMap;
	Endian Endian;

	void ParserNoOp(std::string_view& stream, BlockData& block);
	void ParseStream(std::string_view& stream, BlockData& block);
	void ParseSourceTexture(std::string_view& stream, BlockData& block);
	void ParseTexturingProperty(std::string_view& stream, BlockData& block);
	void ParseTransform(std::string_view& stream, NiTransform& transform, bool translationFirst = true, bool isQuaternion = false);
	void ParseMatrix(std::string_view& stream, Matrix4F& matrix);
	Vector3SF ParseVector3(std::string_view& stream);
	Color3 ParseColor3(std::string_view& stream);
	Color4 ParseColor4(std::string_view& stream);
	void ParseBounds(std::string_view& stream, NiBounds& bounds);
	void ParseMesh(std::string_view& stream, BlockData& block);
	void ParseNode(std::string_view& stream, BlockData& block);
	void ParseMaterialProperty(std::string_view& stream, BlockData& block);
	void ParseSkinningMeshModifier(std::string_view& stream, BlockData& block);
	void ParseSequenceData(std::string_view& stream, BlockData& block);
	void ParseBSplineCompTransformEvaluator(std::string_view& stream, BlockData& block);
	void ParseBSplineData(std::string_view& stream, BlockData& block);
	void ParseEvaluator(std::string_view& stream, BlockData& block, NiEvaluator* data);
	void ParseBSplineBasisData(std::string_view& stream, BlockData& block);
	void ParseTransformEvaluator(std::string_view& stream, BlockData& block);
	void ParseTransformData(std::string_view& stream, BlockData& block);
	void ParseTextKeyExtraData(std::string_view& stream, BlockData& block);
	void ParseColorExtraData(std::string_view& stream, BlockData& block);
	void ParseFloatExtraData(std::string_view& stream, BlockData& block);
	void ParseAlphaProperty(std::string_view& stream, BlockData& block);
	void ParseVertexColorProperty(std::string_view& stream, BlockData& block);
	void ParsePhysXProp(std::string_view& stream, BlockData& block);
	void ParsePhysXPropDesc(std::string_view& stream, BlockData& block);
	void ParsePhysXActorDesc(std::string_view& stream, BlockData& block);
	void ParsePhysXShapeDesc(std::string_view& stream, BlockData& block);
	void ParsePhysXMeshDesc(std::string_view& stream, BlockData& block);

	void WriteNode(std::ostream& stream, BlockData& block);
	void WriteMesh(std::ostream& stream, BlockData& block);
	void WriteVertexColorProperty(std::ostream& stream, BlockData& block);
	void WriteZBufferProperty(std::ostream& stream, BlockData& block);
	void WriteSpecularProperty(std::ostream& stream, BlockData& block);
	void WriteMaterialProperty(std::ostream& stream, BlockData& block);
	void WriteTexturingProperty(std::ostream& stream, BlockData& block);
	void WriteSourceTexture(std::ostream& stream, BlockData& block);
	void WriteFloatExtraData(std::ostream& stream, BlockData& block);
	void WriteColorExtraData(std::ostream& stream, BlockData& block);
	void WriteIntegerExtraData(std::ostream& stream, BlockData& block);
	void WriteMorphWeightsController(std::ostream& stream, BlockData& block);
	void WriteFloatInterpolator(std::ostream& stream, BlockData& block);
	void WriteFloatData(std::ostream& stream, BlockData& block);
	void WriteMorphMeshModifier(std::ostream& stream, BlockData& block);
	void WriteDataStream(std::ostream& stream, BlockData& block);

	void WriteString(std::ostream& stream, const std::string& text);
	void WriteRef(std::ostream& stream, const BlockData* block);
	void WriteMatrix(std::ostream& stream, const Matrix4F& block);

	template <typename T>
	BlockData* MakeExtraData(const std::string& name, const typename T::ValueType& value)
	{
		BlockData& block = MakeBlock(name);
		T* data = block.MakeType<T>();
		
		data->Value = value;

		return &block;
	}

	template <typename T>
	BlockData* MakeProperty(const std::string& name, unsigned int flags)
	{
		BlockData& block = MakeBlock(name);
		T* data = block.MakeType<T>();

		data->Flags = flags;

		return &block;
	}

	BlockData& MakeBlock(const std::string& name);
	BlockData& InitializeBlock(unsigned int blockIndex);
	const BlockData* FetchRef(unsigned int ref);
	const BlockData* FetchRef(std::string_view& stream);
	const std::string& FetchString(unsigned int ref);
	const std::string& FetchString(std::string_view& stream);
	void ReadBlockRefs(std::string_view& stream, BlockData& block, std::vector<const BlockData*>& refs);

	template <typename T>
	void ReadBlockRefs(std::string_view& stream, BlockData& block, std::vector<NiRef<T>>& refs)
	{
		unsigned int count = Endian.read<unsigned int>(stream);

		refs.resize(count);

		for (unsigned int i = 0; i < count; ++i)
			refs[i] = &Blocks[Endian.read<unsigned int>(stream)];
	}
};

std::shared_ptr<Engine::Graphics::MeshFormat> GetNiMeshFormat();

template <typename KeyType>
void LinearKey<KeyType>::Parse(NifDocument* document, std::string_view& stream)
{
	Time = document->Endian.read<float>(stream);
	Value = ParseKey<KeyType>(document, stream);
}

template <typename KeyType>
void QuadraticKey<KeyType>::Parse(NifDocument* document, std::string_view& stream)
{
	Time = document->Endian.read<float>(stream);
	Value = ParseKey<KeyType>(document, stream);
	Forward = ParseKey<KeyType>(document, stream);
	Backward = ParseKey<KeyType>(document, stream);
}

template <typename KeyType>
void TbcKey<KeyType>::Parse(NifDocument* document, std::string_view& stream)
{
	Time = document->Endian.read<float>(stream);
	Value = ParseKey<KeyType>(document, stream);
	Tension = document->Endian.read<float>(stream);
	Bias = document->Endian.read<float>(stream);
	Continuity = document->Endian.read<float>(stream);
}

template <typename KeyType>
void Keys<KeyType>::Parse(NifDocument* document, std::string_view& stream)
{
	unsigned int length = document->Endian.read<unsigned int>(stream);

	if (length == 0) return;

	Interpolation = (RotationType)document->Endian.read<unsigned int>(stream);

	if (Interpolation != KeyType::Type)
		throw "unsupported";

	KeysValues.resize(length);

	for (unsigned int i = 0; i < length; ++i)
		KeysValues[i].Parse(document, stream);
}

template <typename KeyType>
template <typename Vector>
void AnyKeys<KeyType>::ParseKeyVector(NifDocument* document, std::string_view& stream, Vector& vector, unsigned int keys)
{
	vector.resize(keys);

	for (unsigned int i = 0; i < keys; ++i)
		vector[i].Parse(document, stream);
}

template <typename Type>
constexpr bool IsQuaternion()
{
	return false;
}

template <>
constexpr bool IsQuaternion<Quaternion>()
{
	return true;
}

template <typename KeyType>
void AnyKeys<KeyType>::Parse(NifDocument* document, std::string_view& stream)
{
	unsigned int length = document->Endian.read<unsigned int>(stream);

	if (length == 0) return;

	KeyCount = length;

	Interpolation = (RotationType)document->Endian.read<unsigned int>(stream);

	if (Interpolation == RotationType::ConstKey)
		throw "unsupported";

	if constexpr (std::is_same_v<Quaternion, KeyType>)
	{
		if (Interpolation == RotationType::QuadraticKey)
		{
			ParseKeyVector(document, stream, LinearKeys, length);

			return;
		}
	}

	if constexpr (std::is_same_v<Vector3SF, KeyType>)
	{
		if (Interpolation == RotationType::QuadraticKey)
		{
			//std::cout << "found" << std::endl;
		}
	}

	switch (Interpolation)
	{
	case RotationType::LinearKey: ParseKeyVector(document, stream, LinearKeys, length); break;
	case RotationType::QuadraticKey: ParseKeyVector(document, stream, QuadraticKeys, length); break;
	case RotationType::TbcKey: ParseKeyVector(document, stream, TbcKeys, length); break;
	case RotationType::XyzRotationKey: ParseKeyVector(document, stream, XyzKeys, length); break;
	}
}

template <typename KeyType>
template <typename Vector>
void AnyKeysNoRotate<KeyType>::ParseKeyVector(NifDocument* document, std::string_view& stream, Vector& vector, unsigned int keys)
{
	vector.resize(keys);

	for (unsigned int i = 0; i < keys; ++i)
		vector[i].Parse(document, stream);
}

template <typename KeyType>
void AnyKeysNoRotate<KeyType>::Parse(NifDocument* document, std::string_view& stream)
{
	unsigned int length = document->Endian.read<unsigned int>(stream);

	if (length == 0) return;

	KeyCount = length;

	Interpolation = (RotationType)document->Endian.read<unsigned int>(stream);

	if (Interpolation == RotationType::ConstKey || Interpolation == RotationType::XyzRotationKey)
		throw "unsupported";

	switch (Interpolation)
	{
	case RotationType::LinearKey: ParseKeyVector(document, stream, LinearKeys, length); break;
	case RotationType::QuadraticKey: ParseKeyVector(document, stream, QuadraticKeys, length); break;
	case RotationType::TbcKey: ParseKeyVector(document, stream, TbcKeys, length); break;
	}
}