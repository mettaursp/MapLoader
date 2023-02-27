#include "BatchedSceneDrawOperation.h"

#include <algorithm>

#include "Scene.h"
#include "SceneObject.h"
#include <Engine/VulkanGraphics/Scene/Material.h>
#include <Engine/VulkanGraphics/Core/ShaderGroup.h>
#include <Engine/VulkanGraphics/Core/RenderQueue.h>
#include <Engine/VulkanGraphics/Core/ShaderPipeline.h>
#include <Engine/VulkanGraphics/Core/Uniform.h>
#include <Engine/VulkanGraphics/Scene/DyeablePhongMaterial.h>
#include <Engine/VulkanGraphics/Core/Texture.h>

#ifdef min
#undef min
#endif

namespace Engine
{
	namespace Graphics
	{
		void BatchedSceneDrawOperation::Draw(RenderQueue& queue)
		{
			Texture** textureStartPointer = TextureObjectBuffer.data();
			size_t maxTextures = (size_t)Texture::GetTextureIdBufferSize();

			std::fill(textureStartPointer, textureStartPointer + std::min(maxTextures, TextureObjectBuffer.size()), (Texture*)0);

			TextureObjectBuffer.resize(maxTextures);

			ActiveQueues.clear();

			for (auto& drawQueue : DrawQueue)
			{
				drawQueue.second.clear();
			}

			if (TargetScene != nullptr && ViewCamera != nullptr)
			{
				TargetScene->CastFrustum(
					[&queue, this](const std::shared_ptr<SceneObject>& object)
					{
						Material* material = object->Material.get();
						SceneObjectVector& drawQueue = DrawQueue[material];

						if (drawQueue.size() == 0)
							ActiveQueues.push_back(std::make_pair(material, &drawQueue));//change this to be based on shader groups & register textures to compile descriptor buffer
						//Graphics::CombinedSamplerUniform* uniform = dynamic_cast<Graphics::CombinedSamplerUniform*>(shaderGroup->ForwardShading->GetUniform(0, 1).get());

						drawQueue.push_back(object.get());

						material->RegisterTextures(TextureObjectBuffer);
					}
				);
			}

			std::sort(ActiveQueues.begin(), ActiveQueues.end(), [](auto& left, auto& right)
				{
					if (left.first == nullptr) return true;
					if (right.first == nullptr) return false;

					ShaderGroup* leftGroup = left.first->ShaderGroup.get();
					ShaderGroup* rightGroup = right.first->ShaderGroup.get();

					if (leftGroup == nullptr && rightGroup == nullptr) return left.first < right.first;

					return leftGroup < rightGroup;
				}
			);

			ShaderGroup* lastGroup = nullptr;

			for (auto drawQueue : ActiveQueues)
			{
				if (drawQueue.first == nullptr) continue;

				ShaderGroup* shaderGroup = drawQueue.first->ShaderGroup.get();

				if (shaderGroup == nullptr) continue;
				if (shaderGroup->ForwardShading == nullptr) continue;

				if (shaderGroup != lastGroup)
				{
					queue.SetShaderPipeline(shaderGroup->ForwardShading);

					lastGroup = shaderGroup;
				}

				//UpdateUniforms();
				Graphics::CombinedSamplerUniform* uniform = dynamic_cast<Graphics::CombinedSamplerUniform*>(shaderGroup->ForwardShading->GetUniform(0, 1).get());
				DyeablePhongMaterial* material = dynamic_cast<DyeablePhongMaterial*>(drawQueue.first);
				
				//if (material->Albedo != nullptr && uniform != nullptr)
				//	uniform->Set(0, material->Albedo);

				shaderGroup->ForwardShading->FlushUniformChanges();

				for (SceneObject* object : *drawQueue.second)
				{
					object->Draw(queue, ViewCamera.get());
				}
			}
		}
	}
}