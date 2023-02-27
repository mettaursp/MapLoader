#pragma once

#include "Material.h"

namespace Engine
{
	namespace Graphics
	{
		class Texture;

		class DyeablePhongMaterial : public Material
		{
		public:
			std::shared_ptr<Texture> Albedo;
			std::shared_ptr<Texture> Specular;
			std::shared_ptr<Texture> Normal;
			std::shared_ptr<Texture> ColorParams;

			virtual void RegisterTextures(std::vector<Texture*>& textures) const override;

		private:

		};
	}
}