#pragma once

#include <memory>
#include "core.h"
#include <unordered_map>
#include "vertexformat.h"
#include "indexbuffer.h"
#include "platform.h"

namespace renderer {

using VertexBufferMap = std::map<renderer::VertexAttribute, std::shared_ptr<VertexBuffer>>;

class Renderer;

class VertexArray
{
    friend class Renderer;

public:
    ~VertexArray() = default;
    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexBuffer&&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;

    void AddVertexBuffer(VertexFormatAttribute vertexFormatAttribute, std::shared_ptr<VertexBuffer> vertexBuffer);
	
	static std::shared_ptr<VertexArray> Create(std::shared_ptr<VertexFormat> vertexFormat = nullptr);

	inline void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);
    inline void SetVertexFormat(std::shared_ptr<VertexFormat> vertexFormat);
    inline uint8_t GetVertexFormatIndex() const;
    inline std::shared_ptr<IndexBuffer> GetIndexBuffer();

    inline const VertexBufferMap& GetVertexBufferMap() const;
	void Bind();

private:
    VertexArray(std::shared_ptr<VertexFormat> vertexFormat);
    std::shared_ptr<VertexFormat> mVertexFormat;
	std::shared_ptr<IndexBuffer> mIndexBuffer;
	VertexBufferMap mVertexBufferMap;
	uint32_t mVertexArrayId;
};

inline std::shared_ptr<IndexBuffer> VertexArray::GetIndexBuffer()
{
    return mIndexBuffer;
}


inline void VertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) 
{
	mIndexBuffer = indexBuffer;
}

inline void VertexArray::SetVertexFormat(std::shared_ptr<VertexFormat> vertexFormat)
{
    mVertexFormat = vertexFormat;
}

inline uint8_t VertexArray::GetVertexFormatIndex() const
{
    ASSERT(mVertexFormat != nullptr);
    return mVertexFormat->GetFormatIndex();
}

inline const VertexBufferMap &VertexArray::GetVertexBufferMap() const
{
    return mVertexBufferMap;
}

}
