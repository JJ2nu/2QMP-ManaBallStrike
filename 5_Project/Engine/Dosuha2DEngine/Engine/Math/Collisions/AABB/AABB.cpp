#include "pch.h"
#include "AABB.h"

bool Engine::Math::Collision::AABB::operator()(const Rect& lhs, const Rect& rhs) const
{
    return !(lhs.GetMax().x < rhs.GetMin().x ||
        lhs.GetMin().x > rhs.GetMax().x ||
        lhs.GetMax().y < rhs.GetMin().y ||
        lhs.GetMin().y > rhs.GetMax().y);
}
