#include "pch.h"
#include "SystemManager.h"

void Engine::Manager::System::Initialize(const HWND windowHandle, const Math::Vector2 size)
{
    ::Render::COMInitialize();
    CreateSystem(&GetInstance()->_renderSystem);
    GetInstance()->_renderSystem->Initialize(windowHandle, size);
    CreateSystem(&GetInstance()->_animationSystem);



}

void Engine::Manager::System::Finalize()
{
    GetInstance()->_renderSystem = nullptr;
    GetInstance()->_animationSystem = nullptr;
    ::Render::COMUninitialize();
}

Microsoft::WRL::ComPtr<Render::ISystem> Engine::Manager::System::GetRenderSystem()
{
    return GetInstance()->_renderSystem;
}

Dosuha::Pointer <::Animation::ISystem> Engine::Manager::System::GetAnimationSystem()
{
    return GetInstance()->_animationSystem;
}

Engine::Manager::System::System()
    : _renderSystem(nullptr), _animationSystem(nullptr)
{
}
