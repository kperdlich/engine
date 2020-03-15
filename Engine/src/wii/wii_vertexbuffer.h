#pragma once

#include "wii_defines.h"

namespace renderer {

class VertexBuffer
{
public:
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    static std::shared_ptr<VertexBuffer> Create(const void* data, size_t size);

    inline size_t GetBufferSize() const;
    inline uint8_t* GetBuffer();

    void Bind();

private:
    VertexBuffer(const void* data, size_t size);
    size_t mBufferSize;
    uint8_t* mBuffer;
};

size_t VertexBuffer::GetBufferSize() const
{
    return mBufferSize;
}

inline uint8_t* VertexBuffer::GetBuffer()
{
    return mBuffer;
}
}
