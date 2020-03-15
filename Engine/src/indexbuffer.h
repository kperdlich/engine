#pragma once

#include <memory>
#include "core.h"

namespace renderer {

class IndexBuffer
{
public:
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) = delete;

    static std::shared_ptr<IndexBuffer> Create(uint32_t* indecies, size_t size);
	void Draw();
	void Bind();

    inline uint32_t operator [](uint32_t index) const;
    inline uint32_t GetIndexAt(uint32_t index) const;
    inline size_t GetIndexCount() const;

private:    
    IndexBuffer(uint32_t* indecies, size_t size);
    size_t mSize;
    uint32_t* mIndecies;
	uint32_t mBufferId;
};

inline uint32_t IndexBuffer::operator [](uint32_t index) const
{
    ASSERT(index >= 0 && index < mSize / sizeof(int32_t));
    return mIndecies[index];
}

inline uint32_t IndexBuffer::GetIndexAt(uint32_t index) const
{
    ASSERT(index >= 0 && index < mSize / sizeof(int32_t));
    return mIndecies[index];
}

inline size_t IndexBuffer::GetIndexCount() const
{
    return mSize / sizeof(int32_t);
}
}
