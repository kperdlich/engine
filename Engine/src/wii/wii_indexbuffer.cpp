#include "indexbuffer.h"


renderer::IndexBuffer::IndexBuffer(uint32_t* indecies, size_t size)
    : mSize(size),
      mIndecies(indecies)
{
}


renderer::IndexBuffer::~IndexBuffer()
{
}

std::shared_ptr<renderer::IndexBuffer> renderer::IndexBuffer::Create(uint32_t* indecies, size_t size)
{
    return std::shared_ptr<IndexBuffer>(new IndexBuffer(indecies, size));
}

void renderer::IndexBuffer::Draw()
{

}

void renderer::IndexBuffer::Bind()
{
}
