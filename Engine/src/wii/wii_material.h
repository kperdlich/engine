#pragma once
#include "texture2d.h"

namespace renderer {
	class Material 
	{
	public:	
		Material() = default;
		~Material() = default;
		Material(const Material&) = delete;
		Material(Material&&) = delete;
		Material& operator=(const Material&) = delete;
		Material& operator=(Material&&) = delete;	

		inline void SetTexture(std::shared_ptr<renderer::Texture2D> texture);

		void Bind();

	private:
		std::shared_ptr<renderer::Texture2D> mTexture;

	};

	inline void Material::SetTexture(std::shared_ptr<renderer::Texture2D> texture)
	{
		mTexture = texture;
	}
}