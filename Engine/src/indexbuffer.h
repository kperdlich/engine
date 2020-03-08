#pragma once

#include <memory>

namespace renderer {

class IndexBuffer
{
public:
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) = delete;

	static std::shared_ptr<IndexBuffer> Create(const void* indecies, size_t size);
	void Draw();

	void Bind();

private:    
	IndexBuffer(const void* indecies, size_t size);
    size_t mSize;
	uint32_t mBufferId;
};
}
