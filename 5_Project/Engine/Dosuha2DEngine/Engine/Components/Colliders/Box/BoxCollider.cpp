#include "pch.h"
#include "BoxCollider.h"


Engine::Component::Collider::Box::Box(const Type type)
    : Box(type, Math::Vector2::Zero())
{
}

Engine::Component::Collider::Box::Box(const Type type, const Math::Vector2& size)
    : Rect(size), Base(type), _isRender(false), _collider(Math::Rect::Zero())
{
}

void Engine::Component::Collider::Box::Update(const float deltaMetaTime, const float deltaGameTime)
{
    UpdateTransform();
    UpdateCollider();
}

void Engine::Component::Collider::Box::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
    if (_isRender)
    {
        renderer->SetTransform(cameraMatrix);
        renderer->DrawRectangle(_collider, D2D1::ColorF(D2D1::ColorF::Red));
        renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
        renderer->DrawRectangle(Math::Rect{Math::Vector2::Zero(), _size}, D2D1::ColorF(D2D1::ColorF::Red));
    }
}

void Engine::Component::Collider::Box::DrawCollider(bool isRender)
{
    _isRender = isRender;
}

Engine::Component::Collider::Base::ColliderShape Engine::Component::Collider::Box::GetShape()
{
    return _collider;
}

Engine::Math::Vector2 Engine::Component::Collider::Box::GetShapeCenter()
{
    return _collider.GetCenter();
}

const Engine::Math::Rect& Engine::Component::Collider::Box::GetBound()
{
    UpdateCollider();
    return _collider;
}


void Engine::Component::Collider::Box::UpdateCollider()
{
    const D2D1::Matrix3x2F transform = _centerTransform * _worldTransform;
    const Math::Rect preCollider{Math::Vector2::Zero(), _size};
    const Math::Vector2 lt = transform.TransformPoint(preCollider.GetLeftTop());
    const Math::Vector2 rt = transform.TransformPoint(preCollider.GetRightTop());
    const Math::Vector2 rb = transform.TransformPoint(preCollider.GetMax());
    const Math::Vector2 lb = transform.TransformPoint(preCollider.GetLeftBottom());
    _collider = {
        Math::Helper::Min()(lt.x, rt.x, rb.x, lb.x), Math::Helper::Min()(lt.y, rt.y, rb.y, lb.y),
        Math::Helper::Max()(lt.x, rt.x, rb.x, lb.x), Math::Helper::Max()(lt.y, rt.y, rb.y, lb.y)
    };
    // TODO It must be progressed.
}
