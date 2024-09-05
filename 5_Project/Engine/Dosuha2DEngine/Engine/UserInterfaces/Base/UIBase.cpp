#include "pch.h"
#include "UIBase.h"

Engine::UI::Base::Base(const Math::Vector2& size)
    : _padding(Math::Rect::Zero()), _margin(Math::Rect::Zero()), _size(size)
{
}

void Engine::UI::Base::Initialize(Manager::Resource::Loader loader)
{
}

void Engine::UI::Base::Update(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::UI::Base::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
}

void Engine::UI::Base::Render(Manager::Render::Renderer renderer, Math::Rect baseRect)
{
}

void Engine::UI::Base::Finalize()
{
}

void Engine::UI::Base::SetPadding(const Math::Rect& padding)
{
    _padding = padding;
}

void Engine::UI::Base::SetMargin(const Math::Rect& margin)
{
    _margin = margin;
}

Engine::Math::Vector2 Engine::UI::Base::GetSize() const
{
    return _size;
}

void Engine::UI::Base::SetSize(const Math::Vector2& size)
{
    _size = size;
}

Engine::Math::Rect Engine::UI::Base::GetChildRect(const Math::Rect& baseRect) const
{
    Math::Rect childRect{0, 0, _size.x, _size.y};
    const Math::Rect paddingAndMargin = _padding + _margin;
    childRect.Move(paddingAndMargin.GetMin() + baseRect.GetMin());
    const Math::Vector2 rightBottom = baseRect.GetMax() - paddingAndMargin.GetMax();
    childRect.right = Math::Helper::Min()(childRect.right, rightBottom.x);
    childRect.bottom = Math::Helper::Min()(childRect.bottom, rightBottom.y);
    return childRect;
}
