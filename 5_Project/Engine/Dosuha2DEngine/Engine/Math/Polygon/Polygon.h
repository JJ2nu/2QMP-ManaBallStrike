#pragma once

namespace Engine::Math
{
    struct Polygon
    {
        Polygon(const std::vector<Vector2>& vertices);

        [[nodiscard]] float GetArea() const;
        
        std::vector<Vector2> vertices;
    };
}
