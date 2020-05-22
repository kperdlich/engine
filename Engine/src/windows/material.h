#pragma once
#include "texture2d.h"
#include "opengl_shader.h"

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

		//inline void SetAmbient(std::shared_ptr<renderer::Texture2D> ambient);
		//inline void SetDiffuse(std::shared_ptr<renderer::Texture2D> ambient);
		//inline void SetSpecular(std::shared_ptr<renderer::Texture2D> ambient);
		//inline void SetNormal(std::shared_ptr<renderer::Texture2D> ambient);
		
		void Bind(renderer::Shader& shader);

		inline void SetTexture(std::shared_ptr<renderer::Texture2D> texture);		
	private:
		std::shared_ptr<renderer::Texture2D> mTexture;
		//std::shared_ptr<renderer::Texture2D> mAmbientMap;
		//std::shared_ptr<renderer::Texture2D> mDiffuseMap;
		//std::shared_ptr<renderer::Texture2D> mSpecularMap;
		//std::shared_ptr<renderer::Texture2D> mNormalMap;		
	};

	inline void Material::SetTexture(std::shared_ptr<renderer::Texture2D> texture)
	{
		mTexture = texture;
	}

	//inline void Material::SetAmbient(std::shared_ptr<renderer::Texture2D> ambient)
	//{
	//	mAmbientMap = ambient;
	//}
	//
	//inline void Material::SetDiffuse(std::shared_ptr<renderer::Texture2D> diffuse)
	//{
	//	mDiffuseMap = diffuse;
	//}
	//
	//inline void Material::SetSpecular(std::shared_ptr<renderer::Texture2D> specular)
	//{	
	//	mSpecularMap = specular;
	//}
	//
	//inline void Material::SetNormal(std::shared_ptr<renderer::Texture2D> normal)
	//{
	//	mNormalMap = normal;
	//}

}