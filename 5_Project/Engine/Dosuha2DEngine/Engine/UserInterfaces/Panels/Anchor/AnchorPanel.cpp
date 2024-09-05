#include "pch.h"
#include "AnchorPanel.h"

Engine::UI::Panel::Anchor::Anchor(const Math::Vector2& size)
    : Base(size)
{
}

void Engine::UI::Panel::Anchor::Initialize(Manager::Resource::Loader loader)
{
    std::ranges::for_each(_children, [&loader](const std::shared_ptr<AnchorChild>& child)
    {
        child->Initialize(loader);
    });
}

void Engine::UI::Panel::Anchor::Update(float deltaMetaTime, float deltaGameTime)
{
    std::ranges::for_each(_children, [deltaMetaTime, deltaGameTime](const std::shared_ptr<AnchorChild>& child)
    {
        child->Update(deltaMetaTime, deltaGameTime);
    });
}

void Engine::UI::Panel::Anchor::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
    std::ranges::for_each(_children, [deltaMetaTime, deltaGameTime](const std::shared_ptr<AnchorChild>& child)
    {
        child->LazyUpdate(deltaMetaTime, deltaGameTime);
    });
}

void Engine::UI::Panel::Anchor::Render(Manager::Render::Renderer renderer, Math::Rect baseRect)
{
    const Math::Rect childRect = GetChildRect(baseRect);
    std::ranges::for_each(_children, [renderer, childRect](const std::shared_ptr<AnchorChild>& child)
    {
        child->Render(renderer, childRect);
    });
}

void Engine::UI::Panel::Anchor::Finalize()
{
    std::ranges::for_each(_children, [](const std::shared_ptr<AnchorChild>& child)
    {
        child->Finalize();
    });
}

void Engine::UI::Panel::Anchor::AddChild(const std::shared_ptr<AnchorChild>& child)
{
    _children.push_back(child);
}

Engine::UI::Panel::Anchor::AnchorChild::AnchorChild(const std::shared_ptr<UI::Base>& child)
    : _child(child), _horizontal(HorizontalAnchoring::Left), _vertical(VerticalAnchoring::Top)

{
}

void Engine::UI::Panel::Anchor::AnchorChild::Initialize(const Manager::Resource::Loader& loader) const
{
    _child->Initialize(loader);
}

void Engine::UI::Panel::Anchor::AnchorChild::Update(const float deltaMetaTime, const float deltaGameTime) const
{
    _child->Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Panel::Anchor::AnchorChild::LazyUpdate(const float deltaMetaTime, const float deltaGameTime) const
{
    _child->LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Panel::Anchor::AnchorChild::Render(const Manager::Render::Renderer& renderer,
                                                    Math::Rect baseRect) const
{
    const Math::Vector2 targetSize = _child->GetSize();
    const Math::Vector2 delta = baseRect.GetSize() - targetSize;
    Math::Rect newRect{baseRect.GetMin(), targetSize};
    switch (_horizontal)
    {
    case HorizontalAnchoring::Left:
        break;
    case HorizontalAnchoring::Center:
        newRect.MoveX(delta.x * 0.5f);
        break;
    case HorizontalAnchoring::Right:
        newRect.MoveX(delta.x);
        break;
    }
    switch (_vertical)
    {
    case VerticalAnchoring::Top:
        break;
    case VerticalAnchoring::Center:
        newRect.MoveY(delta.y * 0.5f);
        break;
    case VerticalAnchoring::Bottom:
        newRect.MoveY(delta.y);
        break;
    }

    _child->Render(renderer, newRect);
}

void Engine::UI::Panel::Anchor::AnchorChild::Finalize() const
{
    _child->Finalize();
}

std::pair<Engine::UI::Panel::Anchor::AnchorChild::HorizontalAnchoring, Engine::UI::Panel::Anchor::AnchorChild::
          VerticalAnchoring> Engine::UI::Panel::Anchor::AnchorChild::GetAnchoring() const
{
    return {_horizontal, _vertical};
}

void Engine::UI::Panel::Anchor::AnchorChild::SetAnchoring(HorizontalAnchoring horizontal, VerticalAnchoring vertical)
{
    _horizontal = horizontal;
    _vertical = vertical;
}
