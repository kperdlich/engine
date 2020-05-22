#pragma once

#include <memory>
#include "vertexarray.h"

namespace renderer {

class IndexBuffer;
class VertexBuffer;
class Texture2D;
class Renderer;
class Material;

class Mesh
{
public:
    Mesh(std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VertexArray> vertexArray);
    ~Mesh() = default;
    Mesh(const Mesh&) = delete;
    Mesh& operator = (const Mesh&) = delete;
    Mesh(Mesh&&) = delete;
    Mesh& operator = (Mesh&&) = delete;    

    inline void SetMaterial(std::shared_ptr<Material> material);
    inline std::shared_ptr<IndexBuffer> GetIndexBuffer();
    inline std::shared_ptr<VertexArray> GetVertexArray();
	inline std::shared_ptr<Material> GetMaterial();

    inline std::shared_ptr<const IndexBuffer> GetIndexBuffer() const;
    inline std::shared_ptr<const VertexArray> GetVertexArray() const;
    inline std::shared_ptr<const Material> GetMaterial() const;

    inline uint8_t GetVertexFormatIndex() const;
private:
    std::shared_ptr<VertexArray> mVertexArray;
    std::shared_ptr<IndexBuffer> mIndexBuffer;
    std::shared_ptr<Material> mMaterial;
};

inline void Mesh::SetMaterial(std::shared_ptr<renderer::Material> material)
{
    mMaterial = material;
}

inline std::shared_ptr<IndexBuffer> Mesh::GetIndexBuffer()
{
    return mIndexBuffer;
}

inline std::shared_ptr<VertexArray> Mesh::GetVertexArray()
{
    return mVertexArray;
}

inline std::shared_ptr<Material> Mesh::GetMaterial()
{
    return mMaterial;
}

inline std::shared_ptr<const IndexBuffer> Mesh::GetIndexBuffer() const
{
    return mIndexBuffer;
}

inline std::shared_ptr<const VertexArray> Mesh::GetVertexArray() const
{
    return mVertexArray;
}

inline std::shared_ptr<const Material> Mesh::GetMaterial() const
{
    return mMaterial;
}

inline uint8_t Mesh::GetVertexFormatIndex() const
{
    return mVertexArray->GetVertexFormatIndex();
}

}
