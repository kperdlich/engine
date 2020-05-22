#pragma once

#include <vector>
#include "mesh.h"
#include "platform.h"

namespace renderer {

class Plane 
{
public:
	Plane();
	~Plane() = default;
	Plane(const Plane&) = default;
	Plane& operator = (const Plane&) = default;
	Plane(Plane&&) = default;
	Plane& operator = (Plane&&) = default;

	//inline void SetMaterial(const std::shared_ptr<renderer::Material>& material);
	//inline std::shared_ptr<renderer::Material> GetMaterial();
	//inline const std::shared_ptr<renderer::Material> GetMaterial() const;

	inline renderer::Mesh& GetMesh();
	inline const renderer::Mesh& GetMesh() const;

private:
	//std::shared_ptr<renderer::Material> mMaterial;
	std::unique_ptr<renderer::Mesh> mMesh;
};

//inline void Plane::SetMaterial(const std::shared_ptr<renderer::Material>& material)
//{
//	mMaterial = material;
//}
//
//inline std::shared_ptr<renderer::Material> Plane::GetMaterial()
//{
//	return mMaterial;
//}
//
//inline const std::shared_ptr<renderer::Material> Plane::GetMaterial() const
//{
//	return mMaterial;
//}

inline renderer::Mesh& Plane::GetMesh()
{
	return *mMesh;
}

inline const renderer::Mesh& Plane::GetMesh() const
{
	return *mMesh;
}

}