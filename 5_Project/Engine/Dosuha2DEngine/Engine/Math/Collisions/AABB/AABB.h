#pragma once

namespace Engine::Math::Collision
{
    struct AABB
    {
        bool operator()(const Rect& lhs, const Rect& rhs) const;
    };
}
