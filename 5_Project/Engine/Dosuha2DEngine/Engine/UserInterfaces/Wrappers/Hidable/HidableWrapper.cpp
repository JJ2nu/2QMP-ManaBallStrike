#include "pch.h"
#include "HidableWrapper.h"

Engine::UI::Wrapper::Hidable::Hidable(const Math::Vector2& size)
    : Hidable(size, true)
{
}

Engine::UI::Wrapper::Hidable::Hidable(const Math::Vector2& size, const bool isVisible)
    : Base(size), _isVisible(isVisible), _onShow(nullptr), _onHide(nullptr)
{
}

void Engine::UI::Wrapper::Hidable::Update(const float deltaMetaTime, const float deltaGameTime)
{
    if (_isVisible && _child != nullptr) _child->Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Wrapper::Hidable::LazyUpdate(const float deltaMetaTime, const float deltaGameTime)
{
    if (_isVisible && _child != nullptr) _child->LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Wrapper::Hidable::Render(const Manager::Render::Renderer renderer, const Math::Rect baseRect)
{
    if (_isVisible && _child != nullptr)
    {
        const Math::Rect childRect = GetChildRect(baseRect);
        _child->Render(renderer, childRect);
    }
}

void Engine::UI::Wrapper::Hidable::Show()
{
    _isVisible = true;
    if (_onShow != nullptr) _onShow();
}

void Engine::UI::Wrapper::Hidable::Hide()
{
    _isVisible = false;
    if (_onHide != nullptr) _onHide();
}

void Engine::UI::Wrapper::Hidable::BindOnShow(Event event)
{
    _onShow = std::move(event);
}

void Engine::UI::Wrapper::Hidable::BindOnHide(Event event)
{
    _onHide = std::move(event);
}
