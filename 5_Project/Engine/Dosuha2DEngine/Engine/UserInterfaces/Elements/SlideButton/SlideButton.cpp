#include "pch.h"
#include "SlideButton.h"

Engine::UI::Element::SlideButton::SlideButton(const Math::Vector2& size)
    : Base(size), _bound(Math::Rect::Zero()), _onSlide(nullptr)
{
}

void Engine::UI::Element::SlideButton::Update(float deltaMetaTime, float deltaGameTime)
{
    if (const Math::Vector2 mousePosition = Manager::Input::GetMouse().GetPosition(); Manager::Input::GetMouse().
        GetComponent(Input::Device::IMouse::Button::Left)->GetValue() && _onSlide && _bound.Contains(mousePosition))
        _onSlide((mousePosition.x - _bound.left) / _bound.Width());
}

void Engine::UI::Element::SlideButton::Render(const Manager::Render::Renderer renderer, const Math::Rect baseRect)
{
    _bound = GetChildRect(baseRect);
}

void Engine::UI::Element::SlideButton::BindOnSlide(const Event& event)
{
    _onSlide = event;
}
