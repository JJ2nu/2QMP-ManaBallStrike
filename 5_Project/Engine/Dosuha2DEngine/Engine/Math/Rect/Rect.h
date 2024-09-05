#pragma once

namespace Engine::Math
{
    struct Rect : D2D1_RECT_F
    {
        static Rect Zero();

        Rect();
        Rect(float left, float top, float right, float bottom);
        Rect(D2D1_RECT_F rect);
        Rect(const Vector2& point, const Vector2& size);
        Rect(const Animation::SourceRect& sourceRect);

        [[nodiscard]] Vector2 GetPoint() const;
        [[nodiscard]] Vector2 GetSize() const;
        [[nodiscard]] Vector2 GetCenter() const;
        [[nodiscard]] Vector2 GetExtent() const;
        [[nodiscard]] Vector2 GetMin() const;
        [[nodiscard]] Vector2 GetMax() const;
        [[nodiscard]] Vector2 GetLeftTop() const;
        [[nodiscard]] Vector2 GetRightTop() const;
        [[nodiscard]] Vector2 GetLeftBottom() const;
        [[nodiscard]] Vector2 GetRightBottom() const;

        float Width() const;
        float Height() const;

        void Move(const Vector2& offset);
        void MoveX(float offset);
        void MoveY(float offset);

        bool Contains(const Vector2& point) const;

        bool operator==(const Rect& rhs) const;
        Rect operator+(const Rect& rhs) const;
    };
}
