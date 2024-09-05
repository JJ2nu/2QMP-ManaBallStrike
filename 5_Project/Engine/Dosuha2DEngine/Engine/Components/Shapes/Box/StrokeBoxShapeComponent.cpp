#include "pch.h"
#include "StrokeBoxShapeComponent.h"

Engine::Component::Shape::StrokeBox::StrokeBox(const Math::Vector2& size, D2D1_COLOR_F color, float strokeWidth)
    : Box(size, color), Stroked(strokeWidth)
{
}

void Engine::Component::Shape::StrokeBox::Render(const Manager::Render::Renderer renderer,
                                                 const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
    renderer->DrawRectangle(D2D1::RectF(0, 0, _size.x, _size.y), _color, _strokeWidth);
}
