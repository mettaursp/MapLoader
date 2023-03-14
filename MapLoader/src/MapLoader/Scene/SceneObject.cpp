#include "SceneObject.h"

#include "RTScene.h"
#include <MapLoader/Assets/ModelData.h>

namespace MapLoader
{
	void SceneObject::AddToScene(RTScene* scene, size_t index)
	{
		if (scene == nullptr) return;

		if (Scene.Scene == nullptr)
		{
			Scene = { scene, index };
			
			return;
		}

		Scenes.push_back({ scene, index });
	}

	void SceneObject::RemoveFromScene(RTScene* scene)
	{
		if (scene == nullptr) return;

		if (Scene.Scene == scene)
		{
			if (Scenes.size() > 0)
			{
				Scene = Scenes.back();
				Scenes.pop_back();
			}
			else
				Scene = {};

			return;
		}

		for (SceneEntry& entry : Scenes)
		{
			if (entry.Scene == scene)
			{
				std::swap(entry, Scenes.back());
				Scenes.pop_back();

				return;
			}
		}
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

	void SceneObject::SetStatic(bool isStatic)
	{
		IsStaticObject = isStatic;
	}

	void SceneObject::SetVisibilityType(ObjectVisibilityType visibilityType)
	{
		VisibilityType = visibilityType;
	}

	void SceneObject::SetTransform(Engine::Transform* transform)
	{
		Transform = transform;
	}

	void SceneObject::SetModel(ModelData* model, size_t index)
	{
		Model = model;
		ModelIndex = index;
	}
}