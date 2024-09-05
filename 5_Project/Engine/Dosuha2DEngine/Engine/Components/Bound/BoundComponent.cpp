#include "pch.h"
#include "BoundComponent.h"

Engine::Component::Bound::Bound()
    : Bound(Math::Vector2::Zero())
{
}

Engine::Component::Bound::Bound(Math::Vector2 size)
    : Rect(size), _bound(Math::Rect::Zero())
{
}

void Engine::Component::Bound::Update(const float deltaMetaTime, const float deltaGameTime)
{
    UpdateTransform();
    UpdateBound();
}

void Engine::Component::Bound::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
    if (_isRender)
    {
        renderer->SetTransform(cameraMatrix);
        renderer->DrawRectangle(_bound, D2D1::ColorF(D2D1::ColorF::Red));
        renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
        renderer->DrawRectangle(Math::Rect{ Math::Vector2::Zero(), _size }, D2D1::ColorF(D2D1::ColorF::Yellow));
    }

}

void Engine::Component::Bound::DrawBound(bool isRender)
{
    _isRender = isRender;

}

const Engine::Math::Rect& Engine::Component::Bound::GetBound() const
{
    return _bound;
}

void Engine::Component::Bound::UpdateBound()
{
    const D2D1::Matrix3x2F transform = _centerTransform * _worldTransform;
    Math::Vector2 min{0, 0};
    Math::Vector2 max = _size;
    min = transform.TransformPoint(min);
    max = transform.TransformPoint(max);
    _bound = Math::Rect{min.x, min.y, max.x, max.y};
}
