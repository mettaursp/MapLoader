#pragma once

#include <functional>
#include <MapLoader/Assets/ModelData.h>
#include <Engine/Math/Matrix4.h>
#include <host_device.h>

struct SpawnedEntity;
typedef std::function<bool(MapLoader::ModelData*, size_t, InstDesc&)> ModelSpawnCallback;

SpawnedEntity* spawnModel(MapLoader::ModelData* model, const Matrix4F& transform = Matrix4F(), const ModelSpawnCallback& callback = nullptr);

namespace MapLoader
{
	class RTScene
	{
	public:

	private:

	};
}