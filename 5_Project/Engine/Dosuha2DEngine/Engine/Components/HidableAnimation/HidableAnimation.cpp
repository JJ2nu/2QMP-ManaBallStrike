#include "pch.h"
#include "HidableAnimation.h"

Engine::Component::HidableAnimation::HidableAnimation(const std::wstring& bitmapPath, const std::wstring& animationPath)
    : Animation(bitmapPath, animationPath), _isShown(false)
{
}

void Engine::Component::HidableAnimation::Update(float deltaMetaTime, float deltaGameTime)
{
    if (_isShown) Animation::Update(deltaMetaTime, deltaGameTime);
}

void Engine::Component::HidableAnimation::Render(Manager::Render::Renderer renderer,
                                                 D2D1_MATRIX_3X2_F cameraMatrix) const
{
    if (_isShown) Animation::Render(renderer, cameraMatrix);
}

void Engine::Component::HidableAnimation::Show()
{
    _isShown = true;
}

void Engine::Component::HidableAnimation::Hide()
{
    _isShown = false;
}
