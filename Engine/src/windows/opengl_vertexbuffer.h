#pragma once

#include <memory>
#include <vector>
#include <stdint.h>
#include <stddef.h>

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

	void Bind();

private:
	VertexBuffer(const void* data, size_t size);
    size_t mBufferSize;
	uint32_t mVertexBufferId;
};

size_t VertexBuffer::GetBufferSize() const
{
    return mBufferSize;
}
}
