#include "pch.h"
#include "WrapperBase.h"

Engine::UI::Wrapper::Base::Base(const Math::Vector2& size)
    : UI::Base(size)
{
}

void Engine::UI::Wrapper::Base::Initialize(const Manager::Resource::Loader loader)
{
    if (_child != nullptr) _child->Initialize(loader);
}

void Engine::UI::Wrapper::Base::Update(const float deltaMetaTime, const float deltaGameTime)
{
    if (_child != nullptr) _child->Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Wrapper::Base::LazyUpdate(const float deltaMetaTime, const float deltaGameTime)
{
    if (_child != nullptr) _child->LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Wrapper::Base::Render(const Manager::Render::Renderer renderer, const Math::Rect baseRect)
{
    if (_child == nullptr) return;
    _child->Render(renderer, GetChildRect(baseRect));
}

void Engine::UI::Wrapper::Base::Finalize()
{
    if (_child != nullptr) _child->Finalize();
}

void Engine::UI::Wrapper::Base::SetChild(const std::shared_ptr<UI::Base>& child)
{
    _child = child;
}
