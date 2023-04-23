#include "SceneObject.h"

#include "RTScene.h"
#include <MapLoader/Assets/ModelData.h>

namespace MapLoader
{
	SceneObject::~SceneObject()
	{
		if (Scene.Scene != nullptr)
			Scene.Scene->RemoveObject(this);

		for (size_t i = 0; i < Scenes.size(); ++i)
		{
			if (Scenes[i].Scene != nullptr)
				Scenes[i].Scene->RemoveObject(this);
		}
	}

	void SceneObject::AddToScene(RTScene* scene, size_t id, size_t index, SceneObjectType type)
	{
		if (scene == nullptr) return;

		if (Scene.Scene == nullptr)
		{
			Scene = { scene, id, index, type };
			
			return;
		}

		Scenes.push_back({ scene, id, index, type });
	}

	size_t SceneObject::RemoveFromScene(RTScene* scene)
	{
		if (scene == nullptr) return (size_t)-1;

		if (Scene.Scene == scene)
		{
			size_t index = Scene.Id;

			if (Scenes.size() > 0)
			{
				Scene = Scenes.back();
				Scenes.pop_back();
			}
			else
				Scene = {};

			return index;
		}

		for (SceneEntry& entry : Scenes)
		{
			if (entry.Scene == scene)
			{
				size_t index = entry.Id;

				std::swap(entry, Scenes.back());
				Scenes.pop_back();

				return index;
			}
		}

		return (size_t)-1;
	}

	size_t SceneObject::GetSceneIndex(RTScene* scene) const
	{
		if (Scene.Scene == scene)
			return Scene.Index;

		for (const SceneEntry& entry : Scenes)
		{
			if (entry.Scene == scene)
			{
				return entry.Index;
			}
		}

		return (size_t)-1;
	}

	size_t SceneObject::GetSceneId(RTScene* scene) const
	{
		if (Scene.Scene == scene)
			return Scene.Id;

		for (const SceneEntry& entry : Scenes)
		{
			if (entry.Scene == scene)
			{
				return entry.Id;
			}
		}

		return (size_t)-1;
	}

	ObjectVisibilityType SceneObject::GetVisibilityType() const
	{
		return VisibilityType;
	}

	uint32_t SceneObject::GetVisibilityTypeBit() const
	{
		return 1 << (int)VisibilityType;
	}

	bool SceneObject::HasChanged() const
	{
		if (Transform == nullptr) return false;

		if (IsStale) return true;

		return Transform->HasMoved();
	}

	bool SceneObject::IsStatic() const
	{
		return IsStaticObject;
	}

	Engine::Transform* SceneObject::GetTransform() const
	{
		return Transform;
	}

	bool SceneObject::HasModel() const
	{
		return Model != nullptr;
	}

	uint32_t SceneObject::GetModelId() const
	{
		if (Model == nullptr) return 0;

		return Model->GetId(ModelIndex);
	}

	size_t SceneObject::GetInstanceId() const
	{
		return InstanceId;
	}

	void SceneObject::MarkStale(bool isStale)
	{
		IsStale = isStale;
	}

	void SceneObject::SetStatic(bool isStatic)
	{
		IsStale = true;

		IsStaticObject = isStatic;
	}

	void SceneObject::SetVisibilityType(ObjectVisibilityType visibilityType)
	{
		IsStale = true;

		VisibilityType = visibilityType;
	}

	void SceneObject::SetTransform(Engine::Transform* transform)
	{
		IsStale = true;

		Transform = transform;
	}

	void SceneObject::SetModel(ModelData* model, size_t index)
	{
		IsStale = true;

		Model = model;
		ModelIndex = index;
	}

	void SceneObject::SetInstanceId(size_t instanceId)
	{
		InstanceId = instanceId;
	}

	SceneObjectType SceneObject::GetObjectType(RTScene* scene) const
	{
		if (Scene.Scene == scene)
			return Scene.Type;

		for (const SceneEntry& entry : Scenes)
		{
			if (entry.Scene == scene)
			{
				return entry.Type;
			}
		}

		return SceneObjectType::None;
	}

	void SceneObject::SetObjectType(RTScene* scene, SceneObjectType type, size_t index)
	{
		if (Scene.Scene == scene)
		{
			Scene.Type = type;
			Scene.Index = index;

			return;
		}

		for (SceneEntry& entry : Scenes)
		{
			if (entry.Scene == scene)
			{
				entry.Type = type;
				entry.Index = index;

				return;
			}
		}
	}
}