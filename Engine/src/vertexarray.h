#pragma once

#include <memory>
#include "core.h"
#include <map>
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

    inline void SetVertexFormat(std::shared_ptr<VertexFormat> vertexFormat);
    inline uint8_t GetVertexFormatIndex() const;

    inline const VertexBufferMap& GetVertexBufferMap() const;
	inline std::shared_ptr<VertexBuffer> GetVertexBufferByAttribute(VertexAttribute attribute);
	void Bind();

private:
    VertexArray(std::shared_ptr<VertexFormat> vertexFormat);
    std::shared_ptr<VertexFormat> mVertexFormat;
	VertexBufferMap mVertexBufferMap;
	uint32_t mVertexArrayId;
};

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

inline std::shared_ptr<VertexBuffer> VertexArray::GetVertexBufferByAttribute(VertexAttribute attribute)
{
	ASSERT(mVertexBufferMap.find(attribute) != mVertexBufferMap.end());
	return mVertexBufferMap.at(attribute);
}

}
