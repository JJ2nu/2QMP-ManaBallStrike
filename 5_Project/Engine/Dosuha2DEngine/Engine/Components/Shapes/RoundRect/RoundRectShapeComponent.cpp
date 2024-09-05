#include "pch.h"
#include "RoundRectShapeComponent.h"

Engine::Component::Shape::RoundRect::RoundRect(const Math::Vector2& size, const float radius, const D2D1_COLOR_F color)
    : Component::RoundRect(size, radius), Colored(color)
{
}

void Engine::Component::Shape::RoundRect::Update(float deltaMetaTime, float deltaGameTime)
{
    UpdateTransform();
}

void Engine::Component::Shape::RoundRect::Render(const Manager::Render::Renderer renderer,
    const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
    renderer->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(0, 0, _size.x, _size.y), _radius, _radius), _color);
}
