#pragma once

namespace Engine::Math
{
    // D2D1�� ROUNDRECT�� Ÿ���� ROUND�� radiusX, radiusY�� ���� -> �浹���� �����
    // radiusX = radiusY�� ���� ROUND�� �͸� ���
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