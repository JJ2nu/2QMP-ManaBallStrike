#pragma once

namespace Engine::Math
{
    struct Circle
    {
        static Circle UnitCircle();
        static Circle Zero();

        Circle();
        Circle(float radius);
        Circle(float x, float y, float radius);
        Circle(const Vector2& center, float radius);

        operator D2D1_ELLIPSE() const;
        
        Vector2 center;
        float radius;
    };
}
