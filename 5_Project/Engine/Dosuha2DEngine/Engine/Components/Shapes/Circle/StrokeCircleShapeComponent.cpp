#include "pch.h"
#include "StrokeCircleShapeComponent.h"

Engine::Component::Shape::StrokeCircle::StrokeCircle(float radius, D2D1_COLOR_F color, float strokeWidth)
    : Circle(radius, color), Stroked(strokeWidth)
{
}

void Engine::Component::Shape::StrokeCircle::Render(const Manager::Render::Renderer renderer,
                                                    const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
    renderer->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(0, 0), _radius, _radius), _color, _strokeWidth);
}
