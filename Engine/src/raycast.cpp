#include <float.h>
#include <limits>
#include "raycast.h"
#include <cmath>
#include "mathhelper.h"
#include <sstream>
#include <algorithm>

bool core::Raycast(std::vector<core::AABB>& entites, const math::Vector3f& origin, math::Vector3f direction, const float maxDistance, RayHitResult& hitResult)
{    
    direction.Normalize();

    std::sort(entites.begin(), entites.end(), [&origin](const core::AABB& a, const core::AABB& b)
    {
        const float aDistance  = (a.GetCenter() - origin).Length();
        const float bDistance  = (b.GetCenter() - origin).Length();
        return aDistance < bDistance;
    });

    for (auto& entity : entites)
    {
        const float t1 = (entity.GetMin().X() - origin.X()) / direction.X();
        const float t2 = (entity.GetMax().X() - origin.X()) / direction.X();
        const float t3 = (entity.GetMin().Y() - origin.Y()) / direction.Y();
        const float t4 = (entity.GetMax().Y() - origin.Y()) / direction.Y();
        const float t5 = (entity.GetMin().Z() - origin.Z()) / direction.Z();
        const float t6 = (entity.GetMax().Z() - origin.Z()) / direction.Z();

        const float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        const float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

        if (tmin > maxDistance)
        {
            return false;
        }

        if (tmax < 0)
        {
            continue; //return false;
        }

        if (tmin > tmax)
        {
            continue; //return false;
        }

        hitResult.Entity = entity;
        hitResult.Distance = tmin;
        hitResult.HitLocation = (origin + direction * tmin);
        hitResult.Normal = GetAABBIntersectionPointSurfaceNormal(hitResult.HitLocation, entity);
        return true;
    }

    return false;
}

math::Vector3f core::GetAABBIntersectionPointSurfaceNormal(const math::Vector3f &intersectionPoint, const core::AABB &aabb)
{
    const math::Vector3f relativeInternPoint = intersectionPoint - aabb.GetCenter();
    const math::Vector3f distance = {std::abs(aabb.GetHalfWidth().X() - std::abs(relativeInternPoint.X())),
                                    std::abs(aabb.GetHalfWidth().Y() -  std::abs(relativeInternPoint.Y())),
                                    std::abs(aabb.GetHalfWidth().Z() - std::abs(relativeInternPoint.Z()))};
    math::Vector3f normal;
    float min = std::numeric_limits<float>::max();
    if (distance.X() < min)
    {
        min = distance.X();
        normal = math::Vector3f::Left * math::Sign(relativeInternPoint.X() * -1.0f);
    }
    if (distance.Y() < min)
    {
        min = distance.Y();
        normal = math::Vector3f::Up * math::Sign(relativeInternPoint.Y());
    }
    if (distance.Z() < min)
    {
        min = distance.Z();
        normal = math::Vector3f::Forward * math::Sign(relativeInternPoint.Z() * -1.0f);
    }

    return normal;
}
