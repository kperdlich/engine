#include "core.h"
#include "wii_defines.h"
#include "renderer.h"
#include "wii_renderdata.h"
#include "vertexarray.h"

renderer::VertexArray::VertexArray(VertexFormat *vertexFormat)
    : mVertexFormat(vertexFormat)
{
}

void renderer::VertexArray::AddVertexBuffer(uint32_t vertexAttribute, VertexBuffer* vertexBuffer)
{
    ASSERT(vertexBuffer != nullptr);
    ASSERT(mVertexBufferMap.find(vertexAttribute) == mVertexBufferMap.end());
    mVertexBufferMap[vertexAttribute] = vertexBuffer;
}

void renderer::VertexArray::Bind()
{
    mVertexFormat->Bind();

    for (auto& vertexBuffer : mVertexBufferMap)
    {        
        GX_SetArray(vertexBuffer.first, vertexBuffer.second->GetBuffer(), vertexBuffer.second->GetStride());
    }
}


