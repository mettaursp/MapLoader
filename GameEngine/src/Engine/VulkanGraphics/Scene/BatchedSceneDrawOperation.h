#pragma once

#include <unordered_map>

#include <Engine/VulkanGraphics/Core/DrawOperation.h>

namespace Engine
{
	namespace Graphics
	{
		class Scene;
		class Camera;
		class Material;
		class SceneObject;
		class Texture;

		class BatchedSceneDrawOperation : public DrawOperation
		{
		public:
			std::shared_ptr<Scene> TargetScene;
			std::shared_ptr<Camera> ViewCamera;

			virtual void Draw(RenderQueue& queue);
		private:
			typedef std::vector<SceneObject*> SceneObjectVector;
			typedef std::unordered_map<Material*, SceneObjectVector> MaterialQueueMap;
			typedef std::vector<std::pair<Material*, SceneObjectVector*>> QueueVector;
			typedef std::vector<Texture*> TextureVector;

			MaterialQueueMap DrawQueue;
			QueueVector ActiveQueues;
			TextureVector TextureObjectBuffer;
		};
	}
}