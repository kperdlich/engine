#include <unordered_map>
#include "vertexformat.h"
#include "windows_defines.h"

static const std::unordered_map<renderer::VertexAttribute, int32_t> VertexAttributesOpenGLMapping = {
	{ renderer::VertexAttribute::Position, 0 },
	{ renderer::VertexAttribute::Color, 1 },
	{ renderer::VertexAttribute::Texture, 2 },
	{ renderer::VertexAttribute::Normal, 3 },
};

static const std::unordered_map<renderer::VertexAttributeComponentType, int32_t> VertexAttributesComponentTypeOpenGLMapping = {
	{ renderer::VertexAttributeComponentType::Position_XY, 2 },
	{ renderer::VertexAttributeComponentType::Position_XYZ, 3 },
	{ renderer::VertexAttributeComponentType::Normal_XYZ, 3 },
	{ renderer::VertexAttributeComponentType::Color_RGB, 3 },
	{ renderer::VertexAttributeComponentType::Color_RGBA, 4 },
	{ renderer::VertexAttributeComponentType::Texture_ST, 2 }
};

static const std::unordered_map<renderer::VertexAttributeComponentTypeSize, std::pair<int32_t, size_t>> VertexAttributesComponentTypeSizeOpenGLMapping = {
	{ renderer::VertexAttributeComponentTypeSize::Integer8, {GL_BYTE, sizeof(GLbyte)} },
	{ renderer::VertexAttributeComponentTypeSize::Integer16, {GL_SHORT, sizeof(GLshort)}  },
	{ renderer::VertexAttributeComponentTypeSize::Integer32, {GL_INT, sizeof(GLint)}  },
	{ renderer::VertexAttributeComponentTypeSize::Float32, {GL_FLOAT, sizeof(GLfloat)}  },
	{ renderer::VertexAttributeComponentTypeSize::RGA8, {GL_FLOAT, sizeof(GLfloat)} },
	{ renderer::VertexAttributeComponentTypeSize::RGBA8, {GL_FLOAT, sizeof(GLfloat)} }
};


void renderer::VertexFormat::AddAttribute(const renderer::VertexFormatAttribute& attribute)
{
	mAttributes.emplace_back(attribute);	

	const int32_t attributeSlotIndex = VertexAttributesOpenGLMapping.at(attribute.Attribute);
	const int32_t attributeComponentSize = VertexAttributesComponentTypeOpenGLMapping.at(attribute.ComponentType);
	const auto [attributeType, attributeSize] = VertexAttributesComponentTypeSizeOpenGLMapping.at(attribute.ComponentSizeType);

	glEnableVertexAttribArray(attributeSlotIndex);		
	glVertexAttribPointer(attributeSlotIndex, attributeComponentSize, attributeType, GL_FALSE, 0, nullptr);
}

std::shared_ptr<renderer::VertexFormat> renderer::VertexFormat::Create()
{
	return std::shared_ptr<renderer::VertexFormat>(new renderer::VertexFormat());
}
