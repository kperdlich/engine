#pragma once
#include <array>
#include "texture2d.h"
#include "image2d.h"
#include "renderer.h"
#include "vertexarray.h"
#include "opengl_shader.h"

namespace renderer {
	enum CubemapSlots : uint8_t
	{
		POSITIVE_X = 0,
		NEGATIVE_X,
		POSITIVE_Y,
		NEGATIVE_Y,
		POSITIVE_Z,
		NEGATIVE_Z,
	};

	class Skybox 
	{
	public:
		explicit Skybox(uint32_t textureSlot = 0);
		~Skybox() = default;
		Skybox(const Skybox&) = delete;
		Skybox(Skybox&&) = delete;
		void operator=(const Skybox&) = delete;
		void operator=(Skybox&&) = delete;

		void SetPositiveX(std::shared_ptr<renderer::Image2D> image);
		void SetNegativeX(std::shared_ptr<renderer::Image2D> image);
		void SetPositiveY(std::shared_ptr<renderer::Image2D> image);
		void SetNegativeY(std::shared_ptr<renderer::Image2D> image);
		void SetPositiveZ(std::shared_ptr<renderer::Image2D> image);
		void SetNegativeZ(std::shared_ptr<renderer::Image2D> image);			
		
		void Render(renderer::Renderer& renderer);
	private:
		void CreateCubemapTexture(std::shared_ptr<renderer::Image2D> image, CubemapSlots cubemapSlot);
		std::shared_ptr<renderer::VertexArray> mVertexArray;
		std::shared_ptr<renderer::IndexBuffer> mIndexBuffer;
		std::shared_ptr<renderer::Shader> mShader;
		uint32_t mTextureID;
	};
}