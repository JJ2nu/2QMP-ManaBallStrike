#include "pch.h"
#include "BoxShapeComponent.h"

Engine::Component::Shape::Box::Box(const Math::Vector2& size, const D2D1_COLOR_F color)
    : Rect(size), Colored(color)
{
}

void Engine::Component::Shape::Box::Update(float deltaMetaTime, float deltaGameTime)
{
    UpdateTransform();
}

void Engine::Component::Shape::Box::Render(const Manager::Render::Renderer renderer,
                                           const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
    renderer->FillRectangle(Math::Rect{Math::Vector2::Zero(), _size}, _color);
}
