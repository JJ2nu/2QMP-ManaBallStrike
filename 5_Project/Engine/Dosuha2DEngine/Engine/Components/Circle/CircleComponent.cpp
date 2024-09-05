#include "pch.h"
#include "CircleComponent.h"

Engine::Component::Circle::Circle(const float radius)
    : _radius(radius)
{
}

void Engine::Component::Circle::SetRadius(const float radius)
{
    _radius = radius;
}

void Engine::Component::Circle::UpdateCenterTransform()
{
    _centerTransform = D2D1::Matrix3x2F::Translation(-1 * Math::Vector2::SplitProduct(Math::Vector2(_radius, _radius) * 2, _center - Math::Vector2::Half()));
}
