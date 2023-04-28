#include "SceneObject.h"

#include "RTScene.h"
#include <MapLoader/Assets/ModelData.h>

namespace MapLoader
{
	Enum::SceneObjectChanges operator|(Enum::SceneObjectChanges left, Enum::SceneObjectChanges right)
	{
		return (Enum::SceneObjectChanges)((uint32_t)left | (uint32_t)right);
	}

	Enum::SceneObjectChanges operator&(Enum::SceneObjectChanges left, Enum::SceneObjectChanges right)
	{
		return (Enum::SceneObjectChanges)((uint32_t)left & (uint32_t)right);
	}

	Enum::SceneObjectChanges& operator|=(Enum::SceneObjectChanges& left, Enum::SceneObjectChanges right)
	{
		return left = left | right;
	}

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

	VisibilityFlags SceneObject::GetVisibilityFlags() const
	{
		return ObjectVisibilityType;
	}

	void SceneObject::SetVisibilityFlags(VisibilityFlags visibilityFlags)
	{
		if (ObjectVisibilityType != visibilityFlags)
			Changes |= SceneObjectChanges::Visibility;

		ObjectVisibilityType = visibilityFlags;
	}

	void SceneObject::AddVisibilityFlags(VisibilityFlags visibilityFlags)
	{
		SetVisibilityFlags((VisibilityFlags)(ObjectVisibilityType | visibilityFlags));
	}

	void SceneObject::RemoveVisibilityFlags(VisibilityFlags visibilityFlags)
	{
		SetVisibilityFlags((VisibilityFlags)(ObjectVisibilityType & (0xFFFFFFFF ^ visibilityFlags)));
	}

	bool SceneObject::HasVisibilityFlags(VisibilityFlags visibilityFlags) const
	{
		return (ObjectVisibilityType & visibilityFlags) == visibilityFlags;
	}

	void SceneObject::SetShaderType(uint32_t shaderType)
	{
		if (ShaderType != shaderType)
			Changes |= SceneObjectChanges::ShaderType;

		ShaderType = shaderType;
	}

	bool SceneObject::HasChanged() const
	{
		if (Transform == nullptr) return false;

		if (Changes) return true;

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
		if (isStale)
			Changes |= SceneObjectChanges::Misc;
		else
			Changes = SceneObjectChanges::None;
	}

	void SceneObject::SetStatic(bool isStatic)
	{
		Changes |= SceneObjectChanges::Static;

		IsStaticObject = isStatic;
	}

	void SceneObject::SetTransform(Engine::Transform* transform)
	{
		Changes |= SceneObjectChanges::Transform;

		Transform = transform;
	}

	void SceneObject::SetModel(ModelData* model, size_t index)
	{
		Changes |= SceneObjectChanges::Model;

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