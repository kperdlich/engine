#include "wii_vertexbuffer.h"

renderer::VertexBuffer::VertexBuffer(const void *data, size_t size)
{
    mBufferSize = size;
    mBuffer = (uint8_t*) memalign(32, size);
    memcpy(mBuffer, data, mBufferSize);
    DCFlushRange(mBuffer, mBufferSize);
}

renderer::VertexBuffer::~VertexBuffer()
{
    free(mBuffer);
}


void renderer::VertexBuffer::Bind()
{
}

std::shared_ptr<renderer::VertexBuffer> renderer::VertexBuffer::Create(const void* data, size_t size)
{
    return std::shared_ptr<renderer::VertexBuffer>(new renderer::VertexBuffer(data, size));
}
