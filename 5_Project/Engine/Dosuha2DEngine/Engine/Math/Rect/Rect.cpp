#include "pch.h"
#include "Rect.h"

Engine::Math::Rect Engine::Math::Rect::Zero()
{
    return {0, 0, 0, 0};
}

Engine::Math::Rect::Rect()
    : D2D1_RECT_F{0, 0, 0, 0}
{
}

Engine::Math::Rect::Rect(const float left, const float top, const float right, const float bottom)
    : D2D1_RECT_F{left, top, right, bottom}
{
}

Engine::Math::Rect::Rect(const D2D1_RECT_F rect)
    : D2D1_RECT_F{rect}
{
}

Engine::Math::Rect::Rect(const Vector2& point, const Vector2& size)
    : D2D1_RECT_F{point.x, point.y, point.x + size.x, point.y + size.y}
{
}

Engine::Math::Rect::Rect(const Animation::SourceRect& sourceRect)
    : D2D1_RECT_F{sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom}
{
}

Engine::Math::Vector2 Engine::Math::Rect::GetPoint() const
{
    return {left, top};
}

Engine::Math::Vector2 Engine::Math::Rect::GetSize() const
{
    return GetMax() - GetMin();
}

Engine::Math::Vector2 Engine::Math::Rect::GetCenter() const
{
    return (GetMin() + GetMax()) * 0.5f;
}

Engine::Math::Vector2 Engine::Math::Rect::GetExtent() const
{
    return GetSize() * 0.5f;
}

Engine::Math::Vector2 Engine::Math::Rect::GetMin() const
{
    return {left, top};
}

Engine::Math::Vector2 Engine::Math::Rect::GetMax() const
{
    return {right, bottom};
}

Engine::Math::Vector2 Engine::Math::Rect::GetLeftTop() const
{
    return {left, top};
}

Engine::Math::Vector2 Engine::Math::Rect::GetRightTop() const
{
    return {right, top};
}

Engine::Math::Vector2 Engine::Math::Rect::GetLeftBottom() const
{
    return {left, bottom};
}

Engine::Math::Vector2 Engine::Math::Rect::GetRightBottom() const
{
    return {right, bottom};
}

float Engine::Math::Rect::Width() const
{
    return  right - left;
}

float Engine::Math::Rect::Height() const
{
    return bottom - top;
}

void Engine::Math::Rect::Move(const Vector2& offset)
{
    MoveX(offset.x);
    MoveY(offset.y);
}

void Engine::Math::Rect::MoveX(const float offset)
{
    left += offset;
    right += offset;
}

void Engine::Math::Rect::MoveY(const float offset)
{
    top += offset;
    bottom += offset;
}

bool Engine::Math::Rect::Contains(const Vector2& point) const
{
    return left <= point.x && point.x <= right && top <= point.y && point.y <= bottom;
}

bool Engine::Math::Rect::operator==(const Rect& rhs) const
{
    return left == rhs.left && top == rhs.top && right == rhs.right && bottom == rhs.bottom;
}

Engine::Math::Rect Engine::Math::Rect::operator+(const Rect& rhs) const
{
    return {left + rhs.left, top + rhs.top, right + rhs.right, bottom + rhs.bottom};
}
