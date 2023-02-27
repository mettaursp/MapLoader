#pragma once

#include <Engine/Objects/Object.h>

namespace Engine
{
	namespace Graphics
	{
		class ShaderGroup;
		class Texture;

		struct MaterialProperties
		{

		};

		class Material : public Object
		{
		public:
			std::shared_ptr<ShaderGroup> ShaderGroup;

			virtual void RegisterTextures(std::vector<Texture*>& textures) const {}
		private:

		};
	}
}