#include "pch.h"
#include "UIComponent.h"

Engine::Component::UI::UI(const Math::Vector2& size)
    : Rect(size), _rootPanel(std::make_shared<Engine::UI::Panel::Anchor>(size))
{
}

void Engine::Component::UI::Initialize(const Manager::Resource::Loader loader)
{
    _rootPanel->Initialize(loader);
}

void Engine::Component::UI::Update(const float deltaMetaTime, const float deltaGameTime)
{
    UpdateTransform();
    _rootPanel->Update(deltaMetaTime, deltaGameTime);
}

void Engine::Component::UI::LazyUpdate(const float deltaMetaTime, const float deltaGameTime)
{
    _rootPanel->LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Engine::Component::UI::Render(const Manager::Render::Renderer renderer, const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
    _rootPanel->Render(renderer, Math::Rect{Math::Vector2::Zero(), _size});
}

void Engine::Component::UI::Finalize()
{
    _rootPanel->Finalize();
}

std::shared_ptr<Engine::UI::Panel::Anchor> Engine::Component::UI::GetRootPanel() const
{
    return _rootPanel;
}

void Engine::Component::UI::UpdateWorldTransform()
{
    _scaleMatrix = D2D1::Matrix3x2F::Scale(_scale);
    _rotationMatrix = D2D1::Matrix3x2F::Rotation(_rotation);
    _translationMatrix = D2D1::Matrix3x2F::Translation(_location);
    _transform = _scaleMatrix * _rotationMatrix * _translationMatrix;
    if (_parentScene.expired()) _worldTransform = _transform;
    else _worldTransform = _transform * _parentScene.lock()->GetTranslationMatrix();
}
