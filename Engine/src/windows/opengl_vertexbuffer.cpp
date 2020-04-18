#include "opengl_vertexbuffer.h"
#include "windows_defines.h"

renderer::VertexBuffer::VertexBuffer(const void* data, size_t size)
	: mBufferSize(size)
{
	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, mBufferSize, data, GL_STATIC_DRAW);
}

renderer::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &mVertexBufferId);
}

void renderer::VertexBuffer::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
}

std::shared_ptr<renderer::VertexBuffer> renderer::VertexBuffer::Create(const void* data, size_t size)
{
	return std::shared_ptr<renderer::VertexBuffer>(new renderer::VertexBuffer(data, size));
}

