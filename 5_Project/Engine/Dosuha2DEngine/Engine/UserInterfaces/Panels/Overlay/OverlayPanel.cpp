#include "pch.h"
#include "OverlayPanel.h"

Engine::UI::Panel::Overlay::Overlay(const Math::Vector2& size)
    : Base(size)
{
}

void Engine::UI::Panel::Overlay::Initialize(Manager::Resource::Loader loader)
{
    std::ranges::for_each(_children, [&loader](const std::shared_ptr<OverlayChild>& child)
    {
        child->Initialize(loader);
    });
}

void Engine::UI::Panel::Overlay::Update(float deltaMetaTime, float deltaGameTime)
{
    std::ranges::for_each(_children, [deltaMetaTime, deltaGameTime](const std::shared_ptr<OverlayChild>& child)
    {
        child->Update(deltaMetaTime, deltaGameTime);
    });
}

void Engine::UI::Panel::Overlay::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
    std::ranges::for_each(_children, [deltaMetaTime, deltaGameTime](const std::shared_ptr<OverlayChild>& child)
    {
        child->LazyUpdate(deltaMetaTime, deltaGameTime);
    });
}

void Engine::UI::Panel::Overlay::Render(Manager::Render::Renderer renderer, Math::Rect baseRect)
{
    const Math::Rect childRect = GetChildRect(baseRect);
    std::ranges::for_each(_children, [renderer, childRect](const std::shared_ptr<OverlayChild>& child)
    {
        child->Render(renderer, childRect);
    });
}

void Engine::UI::Panel::Overlay::Finalize()
{
    std::ranges::for_each(_children, [](const std::shared_ptr<OverlayChild>& child)
    {
        child->Finalize();
    });
}

void Engine::UI::Panel::Overlay::AddChild(const std::shared_ptr<OverlayChild>& child)
{
    _children.push_back(child);
}

Engine::UI::Panel::Overlay::OverlayChild::OverlayChild(const std::shared_ptr<Base>& child)
    : _child(child)
{
}

void Engine::UI::Panel::Overlay::OverlayChild::Initialize(const Manager::Resource::Loader& loader) const
{
    _child->Initialize(loader);
}

void Engine::UI::Panel::Overlay::OverlayChild::Update(const float deltaMetaTime, const float deltaGameTime) const
{
    _child->Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Panel::Overlay::OverlayChild::LazyUpdate(const float deltaMetaTime, const float deltaGameTime) const
{
    _child->LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Panel::Overlay::OverlayChild::Render(const Manager::Render::Renderer& renderer,
                                                      const Math::Rect baseRect) const
{
    _child->Render(renderer, baseRect);
}

void Engine::UI::Panel::Overlay::OverlayChild::Finalize() const
{
    _child->Finalize();
}
