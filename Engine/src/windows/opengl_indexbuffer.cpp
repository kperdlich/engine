#include "windows_defines.h"
#include "indexbuffer.h"

renderer::IndexBuffer::IndexBuffer(uint32_t* indecies, size_t size)
    : mSize(size),
      mIndecies(indecies)
{
	glGenBuffers(1, &mBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indecies, GL_STATIC_DRAW);
}

renderer::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mBufferId);
}

void renderer::IndexBuffer::Bind() 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
}

std::shared_ptr<renderer::IndexBuffer> renderer::IndexBuffer::Create(uint32_t* indecies, size_t size)
{
	return std::shared_ptr<IndexBuffer>(new IndexBuffer(indecies, size));
}

void renderer::IndexBuffer::Draw()
{
	glDrawElements(GL_TRIANGLES, mSize / sizeof(GLint), GL_UNSIGNED_INT, 0);
}

