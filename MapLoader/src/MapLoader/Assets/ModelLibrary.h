#pragma once

#include <unordered_set>

#include <Engine/VulkanGraphics/Scene/MeshData.h>
#include <ArchiveParser/MetadataMapper.h>
#include <MapLoader/Assets/ModelData.h>
#include "TextureLibrary.h"
#include <host_device.h>
#include <MapLoader/obj_loader.h>
#include <host_device.h>
#include <Engine/Math/Matrix4.h>

namespace Engine
{
	namespace Graphics
	{
		struct ModelPackageNode;
		struct ModelPackageMaterial;
	}

	class Transform;
}

namespace MapLoader
{
	class SceneObject;
}

struct SpawnedMesh
{
	std::shared_ptr<Engine::Transform> Transform;
	std::shared_ptr<MapLoader::SceneObject> SceneObject;
};

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
	std::vector<SpawnedMesh> Meshes;
};

struct ModelSpawnParameters
{
	MapLoader::ModelData* Model;
	size_t MeshIndex = (size_t)-1; // Mesh index in model
	InstDesc& NewInstance;
	size_t MeshId = (size_t)-1; // Spawned model instance index
	size_t VertexCount = 0;
	size_t IndexCount = 0;
};

typedef std::function<bool(ModelSpawnParameters&)> ModelSpawnCallback;

namespace MapLoader
{
	class GameAssetLibrary;
	class RTScene;

	class ModelLibrary
	{
	public:
		struct SpawnedModel
		{
			int EntityId = -1;
			int ModelId = -1;
			int MaterialId = -1;
			size_t BlasInstanceId = (size_t)-1;
			std::shared_ptr<MapLoader::SceneObject> SceneObject;
		};

		ModelLibrary(GameAssetLibrary& assetLibrary);
		~ModelLibrary();

		ModelData* FetchModel(const Archive::Metadata::Entry* entry, bool keepRawData = false, ModelData* parentRig = nullptr);
		ModelData* FindModel(const Archive::Metadata::Entry* entry);
		void SetCurrentMapTransform(const Matrix4F& mapTransform);
		void SetMeshBlasId(size_t meshId, size_t blasId);
		void SetBlasInstanceId(size_t blasInstanceId, size_t blasId);

		const Matrix4F& GetCurrentMapTransform() const { return CurrentMapTransform; }
		const auto& GetUnmappedMaterials() const { return UnmappedMaterials; }
		const auto& GetModels() const { return Models; }
		const auto& GetMeshDescriptions() const { return MeshDescriptions; }
		const auto& GetWireframeDescriptions() const { return WireframeDescriptions; }
		const auto& GetGpuData() const { return GpuMeshData; }
		const auto& GetGpuWireframeData() const { return GpuWireframeData; }
		const auto& GetGpuMaterialData() const { return GpuMaterialData; }
		const auto& GetTextureTransforms() const { return TextureTransforms; }
		auto& GetMaterialTextures() { return MaterialTextures; }
		const auto& GetMaterialTextures() const { return MaterialTextures; }
		auto& GetTextureTransforms() { return TextureTransforms; }
		uint32_t LoadWireframeMesh(const std::vector<VertexPosBinding>& vertices, const std::vector<int>& indices);
		void UpdateWireframeMesh(uint32_t index, const std::vector<VertexPosBinding>& vertices, const std::vector<int>& indices);
		const auto& GetMeshFormat() const { return MeshFormat; }
		const auto& GetSpawnedInstances() const { return SpawnedInstances; }
		const auto& GetSpawnedWireframeInstances() const { return SpawnedWireframeInstances; }
		const auto& GetSpawnedModels() const { return SpawnedModels; }
		const auto& GetSpawnedEntities() const { return SpawnedEntities; }
		const auto& GetGpuEntityData() const { return GpuEntityData; }
		const auto& GetBlasInstances() const { return BlasInstances; }

		SpawnedEntity* SpawnModel(RTScene* scene, ModelData* model, const Matrix4F& transform, const Vector3SF& mapCoords, const ModelSpawnCallback& callback = nullptr);
		void SpawnWireframe(RTScene* scene, uint32_t index, const Matrix4F& transform = Matrix4F());

		void FreeResources();

		void PrintLoggedTextures();

		static const std::unordered_map<std::string, int> MaterialTypeMap;

	private:
		struct MeshBuffers
		{
			void* VertexBindings[4] = { 0 };
			std::vector<VertexPosBinding> VertexPositions;
			std::vector<VertexBinormalBinding> VertexBinormals;
			std::vector<VertexMorphBinding> VertexMorphPos;
			std::vector<VertexBlendBinding> VertexBlend;
			std::vector<int> IndexBuffer;
			MaterialObj Material;
			bool HasTransparency = false;
			bool HasInvisibility = false;
		};

		struct ObjInstance
		{
			mat4 transform;
			uint32_t objIndex = 0;
			size_t customBlasInstance = (size_t)-1;
		};

		struct BlasInstance
		{
			uint32_t VertexCount = 0;
			uint32_t IndexCount = 0;
			VkDeviceAddress VertexBufferAddress = (uint64_t)-1;
			VkDeviceAddress IndexBufferAddress = (uint64_t)-1;
			size_t blasId = (size_t)-1;
		};

		GameAssetLibrary& AssetLibrary;
		std::string NifDocumentBuffer;
		std::shared_ptr<Engine::Graphics::MeshFormat> MeshFormat;
		std::unordered_map<const Archive::Metadata::Entry*, size_t> ModelMap;
		std::vector<TextureTransform> TextureTransforms;
		std::vector<std::unique_ptr<ModelData>> Models;
		std::vector<MeshDesc> GpuMeshData;
		std::vector<WireframeDesc> GpuWireframeData;
		std::vector<MaterialObj> GpuMaterialData;
		std::vector<MeshDescription> MeshDescriptions;
		std::vector<WireframeDescription> WireframeDescriptions;
		std::vector<MaterialTextures> MaterialTextures;
		std::vector<SpawnedEntity> SpawnedEntities;
		std::vector<ObjInstance> SpawnedInstances;
		std::vector<ObjInstance> SpawnedWireframeInstances;
		std::vector<SpawnedModel> SpawnedModels;
		std::vector<InstDesc> GpuEntityData;
		std::vector<BlasInstance> BlasInstances;
		int DuplicateFormatUses = 0;
		Matrix4F CurrentMapTransform;

		struct MaterialTextureLog
		{
			bool CanHave = false;
			bool CanExclude = false;
			bool AlwaysHas = false;
			size_t AppearanceCount = 0;
			size_t NumberMissing = 0;
		};

		struct MaterialLog
		{
			MaterialTextureLog Diffuse;
			MaterialTextureLog Specular;
			MaterialTextureLog Normal;
			MaterialTextureLog ColorOverride;
			MaterialTextureLog Emissive;
			MaterialTextureLog Decal;
			MaterialTextureLog Anisotropic;
			size_t AppearanceCount = 0;
		};

		const bool LogMaterialTextures = true;

		std::unordered_map<std::string, MaterialLog> LoggedMaterials;

		static std::unordered_set<std::string> UnmappedMaterials;

		bool FetchModel(const Archive::ArchivePath& file, ModelData& loadedModel, bool keepRawData = false, ModelData* parentRig = nullptr);
		void LoadMaterial(MaterialObj& material, const Engine::Graphics::ModelPackageMaterial& packageMaterial);
		void LoadBuffers(MeshBuffers& buffers, Engine::Graphics::ModelPackageNode& node);
		uint32_t LoadModel(MeshBuffers& buffers, const Matrix4F& transform = Matrix4F(), bool invisible = false);
		void LoadModelInstance(uint32_t index, Matrix4F transform = Matrix4F(), size_t customBlasInstance = (size_t)-1);
		void LoadWireframeInstance(uint32_t index, Matrix4F transform = Matrix4F());
	};
}