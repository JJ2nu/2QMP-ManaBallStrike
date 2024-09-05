#include "pch.h"
#include "Canvas.h"

Engine::Canvas::Canvas(const Math::Vector2& viewportSize)
    : _rootPanel(std::make_shared<UI::Panel::Anchor>(viewportSize))
{
}

void Engine::Canvas::Initialize(const Manager::Resource::Loader& loader)
{
    OnCreateUserInterface();
    _rootPanel->Initialize(loader);
    OnSetup();
}

void Engine::Canvas::Update(const float deltaMetaTime, const float deltaGameTime) const
{
    _rootPanel->Update(deltaMetaTime, deltaGameTime);
}

void Engine::Canvas::LazyUpdate(const float deltaMetaTime, const float deltaGameTime) const
{
    _rootPanel->LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::Canvas::Render(const Manager::Render::Renderer& renderer, const Math::Rect baseRect) const
{
    renderer->SetTransform(D2D1::Matrix3x2F::Identity());
    _rootPanel->Render(renderer, baseRect);
}

void Engine::Canvas::Finalize() const
{
    _rootPanel->Finalize();
}

std::shared_ptr<Engine::UI::Panel::Anchor> Engine::Canvas::GetRootPanel() const
{
    return _rootPanel;
}

void Engine::Canvas::OnCreateUserInterface()
{
}

void Engine::Canvas::OnSetup()
{
}
