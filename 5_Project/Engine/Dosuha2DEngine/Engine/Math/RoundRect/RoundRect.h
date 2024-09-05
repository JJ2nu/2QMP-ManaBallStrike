#pragma once

namespace Engine::Math
{
    // D2D1의 ROUNDRECT는 타원형 ROUND라 radiusX, radiusY가 존재 -> 충돌판정 어려움
    // radiusX = radiusY인 원형 ROUND인 것만 취급
	struct RoundRect : D2D1_ROUNDED_RECT
	{
        static RoundRect Zero();

        RoundRect();
        RoundRect(float left, float top, float right, float bottom, float radius);
        RoundRect(const Animation::SourceRect& sourceRect, float radius);
        RoundRect(Rect rect, float radiusX, float radiusY);

        [[nodiscard]] Rect GetOuterRect() const;
        [[nodiscard]] Rect GetInnerRect() const;
        [[nodiscard]] float GetRadius() const;
		[[nodiscard]] Vector2 GetCenter() const;

        bool operator==(const RoundRect& rhs) const;
	};
}