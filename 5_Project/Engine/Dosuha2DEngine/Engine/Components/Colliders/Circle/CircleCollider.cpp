#include "pch.h"
#include "CircleCollider.h"

Engine::Component::Collider::Circle::Circle(const Type type)
    : Circle(type, 0)
{
}

Engine::Component::Collider::Circle::Circle(const Type type, const float radius)
    : Component::Circle(radius), Collider::Base(type), _isRender(false), _collider(Math::Circle::Zero())
{
}

void Engine::Component::Collider::Circle::Update(const float deltaMetaTime, const float deltaGameTime)
{
    UpdateTransform();
    UpdateCollider();
}

void Engine::Component::Collider::Circle::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
    if (_isRender)
    {
        renderer->SetTransform(cameraMatrix);
        renderer->DrawEllipse(_collider, D2D1::ColorF(D2D1::ColorF::Red));
    }
}

void Engine::Component::Collider::Circle::DrawCollider(bool isRender)
{
    _isRender = isRender;
}

Engine::Component::Collider::Base::ColliderShape Engine::Component::Collider::Circle::GetShape()
{
    return _collider;
}

Engine::Math::Vector2 Engine::Component::Collider::Circle::GetShapeCenter()
{
    return _collider.center;
}

void Engine::Component::Collider::Circle::UpdateCollider()
{
    const D2D1::Matrix3x2F transform = _centerTransform * _worldTransform;
    Math::Vector2 center{ 0, 0 };
    Math::Vector2 radiusExtent{ _radius, 0};
    center = transform.TransformPoint(center);
    radiusExtent = transform.TransformPoint(radiusExtent);
    radiusExtent -= center;
    _collider = Math::Circle{ center, radiusExtent.Magnitude()};
}
