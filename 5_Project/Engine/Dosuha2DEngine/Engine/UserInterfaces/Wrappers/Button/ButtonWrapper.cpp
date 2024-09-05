#include "pch.h"
#include "ButtonWrapper.h"

Engine::UI::Wrapper::Button::Button(const Math::Vector2& size)
    : Base(size), _onHoverBegin(nullptr), _onHoverEnd(nullptr), _isHover(false)
{
}

void Engine::UI::Wrapper::Button::Update(const float deltaMetaTime, const float deltaGameTime)
{
    HoverCheck();
    ClickCheck();
    Base::Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Wrapper::Button::Render(Manager::Render::Renderer renderer, Math::Rect baseRect)
{
    _bound = GetChildRect(baseRect);
    Base::Render(renderer, baseRect);
}

void Engine::UI::Wrapper::Button::BindOnHoverBegin(const Event& event)
{
    _onHoverBegin = event;
}

void Engine::UI::Wrapper::Button::BindOnHoverEnd(const Event& event)
{
    _onHoverEnd = event;
}

void Engine::UI::Wrapper::Button::BindOnClick(const Event& event)
{
    _onClick = event;
}

void Engine::UI::Wrapper::Button::HoverCheck()
{
    const Math::Vector2 mousePosition = Manager::Input::GetMouse().GetPosition();
    if (_bound.Contains(mousePosition) && _onHoverBegin && !_isHover)
    {
        _onHoverBegin();
        _isHover = true;
    }
    else if (!_bound.Contains(mousePosition) && _onHoverEnd && _isHover)
    {
        _onHoverEnd();
        _isHover = false;
    }
}

void Engine::UI::Wrapper::Button::ClickCheck() const
{
    if (const Math::Vector2 mousePosition = Manager::Input::GetMouse().GetPosition();
        Manager::Input::GetMouse().GetComponent(Input::Device::IMouse::Button::Left)->GetValue() && _bound.Contains(mousePosition) && _onClick)
    {
        _onClick();
    }
}
