#include "pch.h"
#include "RoundRectCollider.h"

Engine::Component::Collider::RoundRect::RoundRect(const Type type)
    : RoundRect(type, Math::Vector2::Zero(), 0.f)
{
}

Engine::Component::Collider::RoundRect::RoundRect(const Type type, const Math::Vector2& size, const float radius)
    : Component::RoundRect(size, radius), Base(type), _isRender(false), _collider(Math::RoundRect::Zero())
{
}

void Engine::Component::Collider::RoundRect::Update(const float deltaMetaTime, const float deltaGameTime)
{
    UpdateTransform();
    UpdateCollider();
}

void Engine::Component::Collider::RoundRect::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
    if (_isRender)
    {
        renderer->SetTransform(cameraMatrix);
        renderer->DrawRoundedRectangle(_collider, D2D1::ColorF(D2D1::ColorF::Red));
    }
}

void Engine::Component::Collider::RoundRect::DrawCollider(bool isRender)
{
    _isRender = isRender;
}

Engine::Component::Collider::Base::ColliderShape Engine::Component::Collider::RoundRect::GetShape()
{
    return _collider;
}

Engine::Math::Vector2 Engine::Component::Collider::RoundRect::GetShapeCenter()
{
    return _collider.GetCenter();
}

void Engine::Component::Collider::RoundRect::UpdateCollider()
{
    const D2D1::Matrix3x2F transform = _centerTransform * _worldTransform;
    Math::Vector2 min{ 0, 0 };
    Math::Vector2 max = _size;
    min = transform.TransformPoint(min);
    max = transform.TransformPoint(max);
    _collider = Math::RoundRect{ min.x, min.y, max.x, max.y, _radius };
}
