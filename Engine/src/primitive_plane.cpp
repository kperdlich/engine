#include "primitive_plane.h"
#include "platform.h"
#include "indexbuffer.h"
#include "vertexarray.h"

renderer::Plane::Plane()
{
	static std::vector<float> planeVertices = {
		0.0f, 0.0f, -0.5f, // lower-left
		0.0f, 1.0f, -0.5f, // top-left
		1.0f, 1.0f, -0.5f, // top right
		1.0f, 0.0f, -0.5f // lower-right
	};

	static std::vector<float> planeTexCoords = {
		0.0f, 1.0f,  // lower-left corner  
		0.0f, 0.0f,  // top-left corner
		1.f, 0.0f,   // top-right corner
		1.0f, 1.0f   // lower-right corner
	};

	static std::vector<uint8_t> planeColors = {
		255, 255, 255, 255,
		255, 255, 255, 255,
		255, 255, 255, 255,
		255, 255, 255, 255,
	};

	static std::vector<uint32_t> planeIndices = {
		0,
		1,
		2,
		2,
		3,
		0
	};

	std::shared_ptr<renderer::VertexArray> vertexArray = renderer::VertexArray::Create();
	vertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Position,
			renderer::VertexAttributeComponentType::Position_XYZ,
			renderer::VertexAttributeComponentTypeSize::Float32
		},
		renderer::VertexBuffer::Create(planeVertices.data(), planeVertices.size() * sizeof(float))
	);
	vertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Color,
			renderer::VertexAttributeComponentType::Color_RGBA,
			renderer::VertexAttributeComponentTypeSize::RGBA8
		},
		renderer::VertexBuffer::Create(planeColors.data(), planeColors.size() * sizeof(uint8_t))
	);
	vertexArray->AddVertexBuffer(
		renderer::VertexFormatAttribute
		{
			renderer::VertexDataInputType::Index,
			renderer::VertexAttribute::Texture,
			renderer::VertexAttributeComponentType::Texture_ST,
			renderer::VertexAttributeComponentTypeSize::Float32
		},
		renderer::VertexBuffer::Create(planeTexCoords.data(), planeTexCoords.size() * sizeof(float))
	);
	std::shared_ptr<renderer::IndexBuffer> indexBuffer = renderer::IndexBuffer::Create(planeIndices.data(), planeIndices.size() * sizeof(uint32_t));
	mMesh = std::make_unique<renderer::Mesh>(indexBuffer, vertexArray);
}
