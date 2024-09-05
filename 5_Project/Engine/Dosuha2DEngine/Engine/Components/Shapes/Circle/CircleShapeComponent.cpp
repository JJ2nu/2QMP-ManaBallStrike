#include "pch.h"
#include "CircleShapeComponent.h"

Engine::Component::Shape::Circle::Circle(float radius, D2D1_COLOR_F color)
    : Component::Circle(radius), Colored(color)
{
}

void Engine::Component::Shape::Circle::Update(float deltaMetaTime, float deltaGameTime)
{
    UpdateTransform();
}

void Engine::Component::Shape::Circle::Render(const Manager::Render::Renderer renderer,
                                              const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
    renderer->FillEllipse(D2D1::Ellipse(D2D1::Point2F(0, 0), _radius, _radius), _color);
}
