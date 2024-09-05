#include "pch.h"
#include "StackPanel.h"

Engine::UI::Panel::Stack::Stack(const Math::Vector2& size)
    : Base(size), _orientation(Orientation::Horizontal)
{
}

void Engine::UI::Panel::Stack::Initialize(Manager::Resource::Loader loader)
{
    std::ranges::for_each(_children, [&loader](const std::shared_ptr<StackChild>& child)
    {
        child->Initialize(loader);
    });
}

void Engine::UI::Panel::Stack::Update(float deltaMetaTime, float deltaGameTime)
{
    std::ranges::for_each(_children, [deltaMetaTime, deltaGameTime](const std::shared_ptr<StackChild>& child)
    {
        child->Update(deltaMetaTime, deltaGameTime);
    });
}

void Engine::UI::Panel::Stack::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
    std::ranges::for_each(_children, [deltaMetaTime, deltaGameTime](const std::shared_ptr<StackChild>& child)
    {
        child->LazyUpdate(deltaMetaTime, deltaGameTime);
    });
}

void Engine::UI::Panel::Stack::Render(Manager::Render::Renderer renderer, Math::Rect baseRect)
{
    const Math::Rect childRect = GetChildRect(baseRect);
    
    auto _ = std::accumulate(_children.begin(), _children.end(), childRect.GetMin(), [this, renderer, childRect](const Math::Vector2& startPoint, const std::shared_ptr<StackChild>& child)
    {
        Math::Vector2 size = child->Render(renderer, Math::Rect{startPoint, childRect.GetSize()});
        if (_orientation == Orientation::Horizontal) return Math::Vector2{startPoint.x + size.x, startPoint.y};
        else return Math::Vector2{startPoint.x, startPoint.y + size.y};
    });
}

void Engine::UI::Panel::Stack::Finalize()
{
    std::ranges::for_each(_children, [](const std::shared_ptr<StackChild>& child)
    {
        child->Finalize();
    });
}

void Engine::UI::Panel::Stack::AddChild(const std::shared_ptr<StackChild>& child)
{
    _children.push_back(child);
}

void Engine::UI::Panel::Stack::SetOrientation(Orientation orientation)
{
    _orientation = orientation;
}

Engine::UI::Panel::Stack::StackChild::StackChild(const std::shared_ptr<Base>& child)
    : _child(child)
{
}

void Engine::UI::Panel::Stack::StackChild::Initialize(const Manager::Resource::Loader& loader) const
{
    _child->Initialize(loader);
}

void Engine::UI::Panel::Stack::StackChild::Update(const float deltaMetaTime, const float deltaGameTime) const
{
    _child->Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Panel::Stack::StackChild::LazyUpdate(const float deltaMetaTime, const float deltaGameTime) const
{
    _child->LazyUpdate(deltaMetaTime, deltaGameTime);
}

Engine::Math::Vector2 Engine::UI::Panel::Stack::StackChild::Render(const Manager::Render::Renderer& renderer,
                                                  const Math::Rect baseRect) const
{
    _child->Render(renderer, Math::Rect{baseRect.GetMin(), _child->GetSize()});
    return _child->GetSize();
}

void Engine::UI::Panel::Stack::StackChild::Finalize() const
{
    _child->Finalize();
}
