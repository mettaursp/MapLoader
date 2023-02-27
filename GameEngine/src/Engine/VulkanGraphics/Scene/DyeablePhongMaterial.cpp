#include "DyeablePhongMaterial.h"

#include <Engine/VulkanGraphics/Core/Texture.h>

namespace Engine
{
	namespace Graphics
	{
		void DyeablePhongMaterial::RegisterTextures(std::vector<Texture*>& textures) const
		{
			const auto add = [&textures](Texture* texture)
			{
				if (texture == nullptr) return;

				textures[texture->GetTextureId()] = texture;
			};

			add(Albedo.get());
			add(Specular.get());
			add(Normal.get());
			add(ColorParams.get());
		}
	}
}