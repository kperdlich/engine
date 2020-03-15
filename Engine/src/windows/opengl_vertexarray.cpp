#include "vertexarray.h"

renderer::VertexArray::VertexArray(std::shared_ptr<VertexFormat> vertexFormat)
	: mVertexFormat(vertexFormat) 
{
	glGenVertexArrays(1, &mVertexArrayId);
}

void renderer::VertexArray::AddVertexBuffer(VertexFormatAttribute vertexFormatAttribute, std::shared_ptr<VertexBuffer> vertexBuffer)
{
	glBindVertexArray(mVertexArrayId);

	ASSERT(vertexBuffer != nullptr);
	ASSERT(mVertexBufferMap.find(vertexFormatAttribute.Attribute) == mVertexBufferMap.end());
	mVertexBufferMap[vertexFormatAttribute.Attribute] = vertexBuffer;
	vertexBuffer->Bind();
	mVertexFormat->AddAttribute(vertexFormatAttribute);
}

void renderer::VertexArray::Bind()
{
	glBindVertexArray(mVertexArrayId);
	for (auto& [attributteName, vertexBuffer] : mVertexBufferMap)
	{
		vertexBuffer->Bind();		
	}
	mIndexBuffer->Bind();
}

std::shared_ptr<renderer::VertexArray> renderer::VertexArray::Create(std::shared_ptr<renderer::VertexFormat> vertexFormat)
{	
	return std::shared_ptr<renderer::VertexArray>(new renderer::VertexArray(vertexFormat 
		? vertexFormat 
		: renderer::VertexFormat::Create()));
}



