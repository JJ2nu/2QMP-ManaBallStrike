#include "pch.h"
#include "RectComponent.h"

Engine::Component::Rect::Rect(const Math::Vector2& size)
    : _size(size)
{
}

void Engine::Component::Rect::SetSize(const Math::Vector2& size)
{
    _size = size;
}


void Engine::Component::Rect::UpdateCenterTransform()
{
    _centerTransform = D2D1::Matrix3x2F::Translation(-1 * Math::Vector2::SplitProduct(_size, _center));
}
