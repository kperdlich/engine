#include "mesh.h"

renderer::Mesh::Mesh(std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VertexArray> vertexArray)
    : mVertexArray(vertexArray),
      mIndexBuffer(indexBuffer),
      mMaterial(nullptr) {}

