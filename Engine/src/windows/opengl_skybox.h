#pragma once
#include "texture2d.h"
#include "image2d.h"
#include "renderer.h"
#include "vertexarray.h"
#include "opengl_shader.h"
#include "colorrgba.h"

namespace renderer {
	enum CubemapSlots : uint8_t
	{
		Right = 0,
		Left,
		Top,
		Bottom,
		Front,
		Back
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

		void SetRight(std::shared_ptr<renderer::Image2D> image);
		void SetLeft(std::shared_ptr<renderer::Image2D> image);
		void SetTop(std::shared_ptr<renderer::Image2D> image);
		void SetBottom(std::shared_ptr<renderer::Image2D> image);
		void SetFront(std::shared_ptr<renderer::Image2D> image);
		void SetBack(std::shared_ptr<renderer::Image2D> image);			

		void SetAmbientColor(const renderer::ColorRGBA& color);
		
		void Render(renderer::Renderer& renderer);
	private:
		void CreateCubemapTexture(std::shared_ptr<renderer::Image2D> image, CubemapSlots cubemapSlot);
		std::shared_ptr<renderer::VertexArray> mVertexArray;
		std::shared_ptr<renderer::IndexBuffer> mIndexBuffer;
		std::shared_ptr<renderer::Shader> mShader;
		renderer::ColorRGBA mAmbientColor = { 255, 255, 255, 255 };
		uint32_t mTextureID;
	};	
}



