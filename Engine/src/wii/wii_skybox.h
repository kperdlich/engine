#pragma once
#include "texture2d.h"
#include "image2d.h"
#include "renderer.h"
#include "vertexarray.h"
//#include "wii/wii_displaylist.h"

namespace renderer {
	enum CubemapSlots : uint8_t
	{
		Front = 0,
		Bottom,
		Back,
		Top,
		Right,
		Left,
	};

	class Skybox
	{
	public:
		Skybox();
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
		void RenderSkyBox(renderer::Renderer& renderer);

		//renderer::DisplayList mDisplayList;
		std::shared_ptr<renderer::VertexArray> mVertexArray;
		std::shared_ptr<renderer::IndexBuffer> mIndexBuffer;
		std::unique_ptr<renderer::Texture2D> mSkyBoxTextures[6];
		std::shared_ptr<renderer::Image2D> mImages[6];		
		renderer::ColorRGBA mAmbientColor = { 255, 255, 255, 255 };
	};
}