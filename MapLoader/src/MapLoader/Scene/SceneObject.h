#pragma once

#include <Engine/Objects/Object.h>
#include <Engine/Objects/Transform.h>

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

	enum class ObjectVisibilityType
	{
		Disabled = 0,
		Normal = 1,
		Debug = 2,
		Invisible = 3,

		NormalBit = 1 << Normal,
		DebugBit = 1 << Debug,
		InvisibleBit = 1 << Invisible
	};

	class RTScene;
	struct ModelData;

	class SceneObject : public Engine::Object
	{
	public:
		~SceneObject();

		void AddToScene(RTScene* scene, size_t id, size_t index, SceneObjectType type);
		size_t RemoveFromScene(RTScene* scene);

		ObjectVisibilityType GetVisibilityType() const;
		uint32_t GetVisibilityTypeBit() const;
		virtual bool HasChanged() const;
		bool IsStatic() const;
		Engine::Transform* GetTransform() const;
		uint32_t GetModelId() const;
		size_t GetInstanceId() const;
		bool HasModel() const;
		size_t GetSceneIndex(RTScene* scene) const;
		size_t GetSceneId(RTScene* scene) const;

		virtual void MarkStale(bool isStale);
		void SetStatic(bool isStatic);
		void SetVisibilityType(ObjectVisibilityType visibilityType);
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

		bool IsStale = false;
		bool IsStaticObject = false;
		ModelData* Model = nullptr;
		size_t ModelIndex = 0;
		size_t InstanceId = 0;
		Engine::Transform* Transform = nullptr;
		ObjectVisibilityType VisibilityType = ObjectVisibilityType::Normal;
		SceneEntry Scene;
		std::vector<SceneEntry> Scenes;
	};
}