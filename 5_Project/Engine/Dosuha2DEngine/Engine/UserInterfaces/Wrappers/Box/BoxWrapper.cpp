#include "pch.h"
#include "BoxWrapper.h"

Engine::UI::Wrapper::Box::Box(const Math::Vector2& size, const D2D1_COLOR_F color)
    : Base(size), Colored(color)
{
}

void Engine::UI::Wrapper::Box::Render(const Manager::Render::Renderer renderer, const Math::Rect baseRect)
{
    const Math::Rect childRect = GetChildRect(baseRect);
    renderer->FillRectangle(childRect, _color);
    if (_child != nullptr) _child->Render(renderer, childRect);
}
