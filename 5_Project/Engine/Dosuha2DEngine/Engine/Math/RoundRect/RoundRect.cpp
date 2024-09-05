#include "pch.h"
#include "RoundRect.h"

Engine::Math::RoundRect Engine::Math::RoundRect::Zero()
{
    return { {0, 0, 0, 0}, 0, 0};
}

Engine::Math::RoundRect::RoundRect()
    : D2D1_ROUNDED_RECT{ { 0, 0, 0, 0 }, 0.f, 0.f }
{
}

Engine::Math::RoundRect::RoundRect(const float left, const float top, const float right, const float bottom, const float radius)
    : D2D1_ROUNDED_RECT{ {left, top, right, bottom }, radius, radius}
{
}

Engine::Math::RoundRect::RoundRect(const Animation::SourceRect& sourceRect, const float radius)
    : D2D1_ROUNDED_RECT{ { sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom }, radius, radius }
{
}

Engine::Math::RoundRect::RoundRect(Rect rect, const float radiusX, const float radiusY)
    :D2D1_ROUNDED_RECT{rect, radiusX, radiusY}
{
}

Engine::Math::Rect Engine::Math::RoundRect::GetOuterRect() const
{
    return { rect.left, rect.top, rect.right, rect.bottom };
}

Engine::Math::Rect Engine::Math::RoundRect::GetInnerRect() const
{
    return { rect.left + radiusX, rect.top + radiusY, rect.right - radiusX, rect.bottom - radiusY };
}

float Engine::Math::RoundRect::GetRadius() const
{
    return radiusX;
}

Engine::Math::Vector2 Engine::Math::RoundRect::GetCenter() const
{
    return Rect{rect}.GetCenter();
}

bool Engine::Math::RoundRect::operator==(const RoundRect& rhs) const
{
    return rect.left == rhs.rect.left && rect.top == rhs.rect.top && rect.right == rhs.rect.right && rect.bottom == rhs.rect.bottom && radiusX == rhs.radiusX;
}
