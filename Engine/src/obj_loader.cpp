#include "obj_loader.h"
#include "tiny_obj_loader.h"
#include "vertexarray.h"
#include "vertexformat.h"
#include "indexbuffer.h"
#include "core.h"
#include "environment.h"
#include "material.h"

std::vector<std::shared_ptr<renderer::Mesh>> core::LoadMeshesFromObj(const std::string& file, const std::string& mtlBaseDir)
{
	std::vector<std::shared_ptr<renderer::Mesh>> meshes;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file.c_str(), mtlBaseDir.c_str());

	if (!warn.empty()) {
		std::cout << warn << std::endl;		
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
		ASSERT_TEXT(false, "Failed to load %s", file.c_str());
	}

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++)
	{
		std::vector<float> vertices;
		std::vector<float> texCoords;
		std::vector<uint8_t> colors;
		std::vector<uint32_t> indices;
		std::shared_ptr<renderer::VertexArray> vertexArray = renderer::VertexArray::Create();

		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			int fv = shapes[s].mesh.num_face_vertices[f];
			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++)
			{
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

				if (idx.texcoord_index != -1)
				{
					tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

					texCoords.push_back(tx);
					texCoords.push_back(1.0f - ty);
				}
				else
				{
					texCoords.push_back(1.0f);
					texCoords.push_back(1.0f);
				}

				vertices.push_back(vx);
				vertices.push_back(vy);
				vertices.push_back(vz);

				colors.push_back(attrib.colors[3 * idx.vertex_index + 0] * 255);
				colors.push_back(attrib.colors[3 * idx.vertex_index + 1] * 255);
				colors.push_back(attrib.colors[3 * idx.vertex_index + 2] * 255);
				colors.push_back(255);

				indices.push_back(index_offset + v);
			}
			index_offset += fv;			
		}

		std::shared_ptr<renderer::IndexBuffer> indexBuffer = renderer::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));

		std::shared_ptr<renderer::Mesh> mesh = std::make_shared<renderer::Mesh>(indexBuffer, vertexArray);
		meshes.emplace_back(mesh);

		// Load material per mesh
		if (shapes[s].mesh.material_ids.size() > 0)
		{
			const tinyobj::material_t& meshMaterial = materials[shapes[s].mesh.material_ids[0]];
			std::shared_ptr<renderer::Material> material = std::make_shared<renderer::Material>();			

			if (!meshMaterial.ambient_texname.empty())
			{
				const std::string fullImagePath = mtlBaseDir + "/" + meshMaterial.ambient_texname;
				material->SetAmbient(std::make_shared<renderer::Texture2D>(*gEnv->ResourceManager->LoadImage(fullImagePath)));
			}

			if (!meshMaterial.diffuse_texname.empty())
			{
				const std::string fullImagePath = mtlBaseDir + "/" + meshMaterial.diffuse_texname;
				material->SetDiffuse(std::make_shared<renderer::Texture2D>(*gEnv->ResourceManager->LoadImage(fullImagePath)));
			}

			if (!meshMaterial.specular_texname.empty())
			{
				const std::string fullImagePath = mtlBaseDir + "/" + meshMaterial.specular_texname;
				material->SetSpecular(std::make_shared<renderer::Texture2D>(*gEnv->ResourceManager->LoadImage(fullImagePath)));
			}

			if (!meshMaterial.bump_texname.empty())
			{
				const std::string fullImagePath = mtlBaseDir + "/" + meshMaterial.bump_texname;
				material->SetNormal(std::make_shared<renderer::Texture2D>(*gEnv->ResourceManager->LoadImage(fullImagePath)));
			}

			mesh->SetMaterial(material);
		}

		vertexArray->AddVertexBuffer(
			renderer::VertexFormatAttribute
			{
				renderer::VertexDataInputType::Index,
				renderer::VertexAttribute::Position,
				renderer::VertexAttributeComponentType::Position_XYZ,
				renderer::VertexAttributeComponentTypeSize::Float32
			},
			renderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float))
		);

		vertexArray->AddVertexBuffer(
			renderer::VertexFormatAttribute
			{
				renderer::VertexDataInputType::Index,
				renderer::VertexAttribute::Color,
				renderer::VertexAttributeComponentType::Color_RGBA,
				renderer::VertexAttributeComponentTypeSize::RGBA8
			},
			renderer::VertexBuffer::Create(colors.data(), colors.size() * sizeof(int8_t))
		);

		vertexArray->AddVertexBuffer(
			renderer::VertexFormatAttribute
			{
				renderer::VertexDataInputType::Index,
				renderer::VertexAttribute::Texture,
				renderer::VertexAttributeComponentType::Texture_ST,
				renderer::VertexAttributeComponentTypeSize::Float32
			},
			renderer::VertexBuffer::Create(texCoords.data(), texCoords.size() * sizeof(float))
		);

	}

	return meshes;
}
