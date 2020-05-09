#include "wii_defines.h"
#include "vector3f.h"
#include "wii_skybox.h"
#include "image2d.h"
#include "texture2d.h"
#include "renderer.h"
#include "camera.h"
#include "vertexformat.h"

std::vector<float> vertices =
{
	-1.0,  1.0,  1.0,
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0, -1.0,
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
};

std::vector<float> textCoords =
{
	0.0f, 1.0f,  // lower-left corner  
	0.0f, 0.0f,  // top-left corner
	1.f, 0.0f,   // top-right corner
	1.0f, 1.0f   // lower-right corner
};

std::vector<uint32_t> indices =
{
	0, 1, 2,
	2, 3, 0,

	1, 5, 6,
	6, 2, 1,

	7, 6, 5,
	5, 4, 7,

	4, 0, 3,
	3, 7, 4,

	4, 5, 1,
	1, 0, 4,

	3, 2, 6,
	6, 7, 3
};

std::vector<int32_t> textureCoordsIndices = { 2, 3, 0, 0, 1, 2 };

renderer::Skybox::Skybox()
{
	mVertexArray = renderer::VertexArray::Create();
	mVertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Position,
			renderer::VertexAttributeComponentType::Position_XYZ,
			renderer::VertexAttributeComponentTypeSize::Float32
		},
		renderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float))
	);
	mVertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Color,
			renderer::VertexAttributeComponentType::Color_RGBA,
			renderer::VertexAttributeComponentTypeSize::RGBA8
		},
		renderer::VertexBuffer::Create(mAmbientColor.Data(), sizeof(renderer::ColorRGBA))
	);
	mVertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Texture,
			renderer::VertexAttributeComponentType::Texture_ST,
			renderer::VertexAttributeComponentTypeSize::Float32
		},
		renderer::VertexBuffer::Create(textCoords.data(), textCoords.size() * sizeof(float))
	);
	mIndexBuffer = renderer::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));
}

void renderer::Skybox::SetRight(std::shared_ptr<renderer::Image2D> image)
{
	mImages[renderer::CubemapSlots::Right] = image;
	mSkyBoxTextures[renderer::CubemapSlots::Right] = std::make_unique<renderer::Texture2D>(*image);
}

void renderer::Skybox::SetLeft(std::shared_ptr<renderer::Image2D> image)
{
	mImages[renderer::CubemapSlots::Left] = image;
	mSkyBoxTextures[renderer::CubemapSlots::Left] = std::make_unique<renderer::Texture2D>(*image);
}

void renderer::Skybox::SetTop(std::shared_ptr<renderer::Image2D> image)
{
	mImages[renderer::CubemapSlots::Top] = image;
	mSkyBoxTextures[renderer::CubemapSlots::Top] = std::make_unique<renderer::Texture2D>(*image);
}

void renderer::Skybox::SetBottom(std::shared_ptr<renderer::Image2D> image)
{
	mImages[renderer::CubemapSlots::Bottom] = image;
	mSkyBoxTextures[renderer::CubemapSlots::Bottom] = std::make_unique<renderer::Texture2D>(*image);
}
void renderer::Skybox::SetFront(std::shared_ptr<renderer::Image2D> image)
{
	mImages[renderer::CubemapSlots::Front] = image;
	mSkyBoxTextures[renderer::CubemapSlots::Front] = std::make_unique<renderer::Texture2D>(*image);

}
void renderer::Skybox::SetBack(std::shared_ptr<renderer::Image2D> image)
{
	mImages[renderer::CubemapSlots::Back] = image;
	mSkyBoxTextures[renderer::CubemapSlots::Back] = std::make_unique<renderer::Texture2D>(*image);
}

void renderer::Skybox::RenderSkyBox(renderer::Renderer& renderer)
{	
	//mDisplayList.Begin(2000);
	mVertexArray->Bind();	
	renderer.SetCullMode(CullMode::Back);

	constexpr int32_t faceCount = 6, vertexCountPerFace = 6;
	int32_t currentTextureSlotIndex = 0;
	
	for (uint32_t i = 0; i < faceCount; ++i, ++currentTextureSlotIndex)
	{
		mSkyBoxTextures[static_cast<renderer::CubemapSlots>(currentTextureSlotIndex)]->Bind();
		GX_Begin(GX_TRIANGLES, mVertexArray->GetVertexFormatIndex(), 6);
		for (uint32_t j = 0; j < vertexCountPerFace; ++j)
		{
			GX_Position1x16(indices[(i * vertexCountPerFace) + j]);
			GX_Color1x16(0);
			GX_TexCoord1x16(textureCoordsIndices[j]);
		}
		GX_End();
	}	
	//mDisplayList.End();
}

void renderer::Skybox::Render(Renderer& renderer)
{	
	math::Matrix4x4 skyBoxViewMatrix = renderer.GetViewMatrix();
	skyBoxViewMatrix[0][3] = 0;
	skyBoxViewMatrix[1][3] = 0;
	skyBoxViewMatrix[2][3] = 0;	
	renderer.LoadModelViewMatrix(skyBoxViewMatrix);
	RenderSkyBox(renderer);

	//if (mDisplayList.GetBufferSize() <= 0)
	//{
	//	RenderSkyBox(renderer);
	//}
	//
	//mDisplayList.Render();
	//CreateSkyBox(renderer);
}

void renderer::Skybox::SetAmbientColor(const renderer::ColorRGBA& color)
{
	mAmbientColor = color;
	std::shared_ptr<VertexBuffer> colorVertexBuffer = mVertexArray->GetVertexBufferByAttribute(renderer::VertexAttribute::Color);
	ASSERT(colorVertexBuffer->GetBufferSize() >= sizeof(mAmbientColor));
	std::memcpy(colorVertexBuffer->GetBuffer(), mAmbientColor.Data(), sizeof(mAmbientColor));
	DCFlushRange(colorVertexBuffer->GetBuffer(), colorVertexBuffer->GetBufferSize());
}
