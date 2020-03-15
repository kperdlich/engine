#include "core.h"
#include "wii_defines.h"
#include "renderer.h"
#include "wii_renderdata.h"
#include "vertexarray.h"

renderer::VertexArray::VertexArray(std::shared_ptr<VertexFormat> vertexFormat)
    : mVertexFormat(vertexFormat)
{
}

void renderer::VertexArray::AddVertexBuffer(VertexFormatAttribute vertexFormatAttribute, std::shared_ptr<VertexBuffer> vertexBuffer)
{
    ASSERT(vertexBuffer != nullptr);
    ASSERT(mVertexBufferMap.find(vertexFormatAttribute.Attribute) == mVertexBufferMap.end());
    mVertexBufferMap[vertexFormatAttribute.Attribute] = vertexBuffer;
    mVertexFormat->AddAttribute(vertexFormatAttribute);
}

void renderer::VertexArray::Bind()
{
    ASSERT_TEXT(mVertexFormat->VertexAttributeCount() == mVertexBufferMap.size(),
                "Amount of vertex format attributes does not match with vertex buffers!");

    mVertexFormat->Bind();

    const auto& vertexFormattAttributes = mVertexFormat->GetVertexFormatAttributes();
    for (const auto& attribute : vertexFormattAttributes)
    {
        const auto& buffer = mVertexBufferMap.at(attribute.Attribute);
        const uint8_t stride = static_cast<uint8_t>(mVertexFormat->GetStrideSize(attribute.ComponentType, attribute.ComponentSizeType));
        const uint32_t vertexAttributeIndex = static_cast<uint32_t>(mVertexFormat->GetVertexAttributeId(attribute.Attribute));
        GX_SetArray(vertexAttributeIndex, buffer->GetBuffer(), stride);
    }
}

std::shared_ptr<renderer::VertexArray> renderer::VertexArray::Create(std::shared_ptr<renderer::VertexFormat> vertexFormat)
{
    return std::shared_ptr<renderer::VertexArray>(new renderer::VertexArray(vertexFormat
        ? vertexFormat
        : renderer::VertexFormat::Create()));
}

