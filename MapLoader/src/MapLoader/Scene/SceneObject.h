#pragma once

#include <Engine/Objects/Object.h>
#include <Engine/Objects/Transform.h>

namespace MapLoader
{
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
		void AddToScene(RTScene* scene, size_t index);
		void RemoveFromScene(RTScene* scene);

		ObjectVisibilityType GetVisibilityType() const;
		uint32_t GetVisibilityTypeBit() const;
		bool HasChanged() const;
		bool IsStatic() const;
		Engine::Transform* GetTransform() const;
		uint32_t GetModelId() const;
		bool HasModel() const;
		size_t GetSceneIndex(RTScene* scene) const;

		void SetStatic(bool isStatic);
		void SetVisibilityType(ObjectVisibilityType visibilityType);
		void SetTransform(Engine::Transform* transform);
		void SetModel(ModelData* model, size_t index);

	private:
		struct SceneEntry
		{
			RTScene* Scene = nullptr;
			size_t Index = (size_t)-1;
		};

		bool IsStale = false;
		bool IsStaticObject = false;
		ModelData* Model = nullptr;
		size_t ModelIndex = 0;
		Engine::Transform* Transform = nullptr;
		ObjectVisibilityType VisibilityType = ObjectVisibilityType::Normal;
		SceneEntry Scene;
		std::vector<SceneEntry> Scenes;
	};
}