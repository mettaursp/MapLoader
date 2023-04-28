#pragma once

#include <Engine/Objects/Object.h>
#include <Engine/Objects/Transform.h>
#include <host_device.h>

struct SceneObjectChangesEnum
{
	enum SceneObjectChanges : unsigned char
	{
		None = 0,
		Transform = 0x1,
		Visibility = 0x2,
		Static = 0x4,
		Model = 0x8,
		ShaderType = 0x10,
		Misc = 0x20
	};
};

namespace Enum
{
	typedef SceneObjectChangesEnum::SceneObjectChanges SceneObjectChanges;
}

namespace MapLoader
{
	enum class SceneObjectType
	{
		Static,
		Dynamic,
		Skinned,
		Wireframe,

		Count,

		None
	};

	Enum::SceneObjectChanges operator|(Enum::SceneObjectChanges left, Enum::SceneObjectChanges right);
	Enum::SceneObjectChanges operator&(Enum::SceneObjectChanges left, Enum::SceneObjectChanges right);
	Enum::SceneObjectChanges& operator|=(Enum::SceneObjectChanges& left, Enum::SceneObjectChanges right);

	class RTScene;
	struct ModelData;

	class SceneObject : public Engine::Object
	{
	public:
		typedef Enum::SceneObjectChanges SceneObjectChanges;

		~SceneObject();

		void AddToScene(RTScene* scene, size_t id, size_t index, SceneObjectType type);
		size_t RemoveFromScene(RTScene* scene);

		VisibilityFlags GetVisibilityFlags() const;
		virtual bool HasChanged() const;
		SceneObjectChanges GetChanges() const { return Changes; }
		bool IsStatic() const;
		Engine::Transform* GetTransform() const;
		uint32_t GetModelId() const;
		size_t GetInstanceId() const;
		bool HasModel() const;
		ModelData* GetModel() const { return Model; }
		size_t GetModelIndex() const { return ModelIndex; }
		size_t GetSceneIndex(RTScene* scene) const;
		size_t GetSceneId(RTScene* scene) const;
		uint32_t GetShaderType() const { return ShaderType; }

		virtual void MarkStale(bool isStale);
		void SetStatic(bool isStatic);
		void SetVisibilityFlags(VisibilityFlags visibilityFlags);
		void AddVisibilityFlags(VisibilityFlags visibilityFlags);
		void RemoveVisibilityFlags(VisibilityFlags visibilityFlags);
		bool HasVisibilityFlags(VisibilityFlags visibilityFlags) const;
		void SetShaderType(uint32_t shaderType);
		void SetTransform(Engine::Transform* transform);
		void SetModel(ModelData* model, size_t index);
		void SetInstanceId(size_t instanceId);

		SceneObjectType GetObjectType(RTScene* scene) const;
		void SetObjectType(RTScene* scene, SceneObjectType type, size_t index);

	private:
		struct SceneEntry
		{
			RTScene* Scene = nullptr;
			size_t Id = (size_t)-1;
			size_t Index = (size_t)-1;
			SceneObjectType Type = SceneObjectType::None;
		};

		SceneObjectChanges Changes = SceneObjectChanges::None;
		bool IsStaticObject = false;
		ModelData* Model = nullptr;
		size_t ModelIndex = 0;
		size_t InstanceId = 0;
		uint32_t ShaderType = 0;
		Engine::Transform* Transform = nullptr;
		VisibilityFlags ObjectVisibilityType = VisibilityFlags::eStandardVisibility;
		SceneEntry Scene;
		std::vector<SceneEntry> Scenes;
	};
}