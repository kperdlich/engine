#pragma once

#include <vector>
#include "aabb.h"
#include "vector3f.h"
#include "renderer.h"

namespace core {

struct RayHitResult
{
    float Distance;
    core::AABB Entity; // Todo use real entity
    math::Vector3f HitLocation;
    math::Vector3f Normal;
};

bool Raycast(std::vector<AABB> &entites, const math::Vector3f &origin, math::Vector3f direction, const float maxDistance, RayHitResult& hitResult);
math::Vector3f GetAABBIntersectionPointSurfaceNormal(const math::Vector3f& intersectionPoint, const core::AABB& aabb);

}
