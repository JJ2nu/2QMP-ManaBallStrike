#include "pch.h"
#include "RoundRectComponent.h"

Engine::Component::RoundRect::RoundRect(const Math::Vector2& size, const float radius)
    : _size(size), _radius(radius)
{
}

void Engine::Component::RoundRect::SetSize(const Math::Vector2& size)
{
    _size = size;
}

void Engine::Component::RoundRect::SetRadius(float radius)
{
    _radius = radius;
}


void Engine::Component::RoundRect::UpdateCenterTransform()
{
    _centerTransform = D2D1::Matrix3x2F::Translation(-1 * Math::Vector2::SplitProduct(_size, _center));
}
