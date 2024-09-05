#pragma once

namespace Engine::Math
{
    struct Line
    {
        Line();
        Line(float startX, float startY, float endX, float endY, float thickness = 1.f);
        Line(const Vector2& start, const Vector2& end, float thickness = 1.f);

        [[nodiscard]] float GetLength() const;
        [[nodiscard]] float GetSquareLength() const;
        [[nodiscard]] Vector2 GetDirection() const;
        
        Vector2 start;
        Vector2 end;
        float thickness;
    };
}
